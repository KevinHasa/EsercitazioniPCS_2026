#include <vector>
#include <string>
#include <iostream>
#include <Eigen/Dense> 
#include "unidirected_graph.hpp"

struct Component {
    std::string name;
    char type;        // 'R' o 'V'
    double value;     // Valore in Ohm o Volt
    int node1;        // Nodo di partenza 
    int node2;        // Nodo di arrivo 
};

// Costruisce matrici B e R 
void genera_matrici_circuito(const unidirected_graph<int>& G, 
                             const std::vector<Component>& netlist, 
                             const std::vector<std::vector<int>>& cicli,
                             Eigen::MatrixXd& B,
                             Eigen::MatrixXd& R,
                             std::vector<Component>& resistori_ordinati) 
{
    // Ordino i resistori secondo l'ordine lessicografico degli archi del grafo
    resistori_ordinati.clear();
    std::vector<unidirected_edge<int>> archi_grafo_ordinati = G.all_edges();

    for (const auto& arco : archi_grafo_ordinati) {
        for (const auto& comp : netlist) {
            if (comp.type == 'R') {
                unidirected_edge<int> arco_componente(comp.node1, comp.node2);
                if (arco_componente == arco) {
                    resistori_ordinati.push_back(comp);
                    break; 
                }
            }
        }
    }

    size_t m = resistori_ordinati.size(); // Numero di resistori (righe di B, righe/Colonne di R)
    size_t n = cicli.size();             // Numero di cicli (colonne di B)

    // Inizializzo le matrici con zeri
    B = Eigen::MatrixXd::Zero(m, n);
    R = Eigen::MatrixXd::Zero(m, m);

    // Riempio R
    for (size_t i = 0; i < m; i++) {
        R(i, i) = resistori_ordinati[i].value; 
    }

    // Riempio B
    for (size_t j = 0; j < n; j++) {
        const auto& ciclo = cicli[j];

        // Scorro i nodi del ciclo j-esimo a coppie consecutive (u -> v)
        for (size_t k = 0; k < ciclo.size() - 1; k++) {
            int u = ciclo[k];
            int v = ciclo[k + 1];

            // Cerco a quale resistore corrisponde la tratta (u -> v)
            for (size_t i = 0; i < m; i++) {
                unidirected_edge<int> edge_resistore(resistori_ordinati[i].node1, resistori_ordinati[i].node2);

                if (unidirected_edge<int>(u, v) == edge_resistore) {
                    // Se la maglia va dal nodo minore al maggiore -> +1
                    if (u == edge_resistore.from() && v == edge_resistore.to()) {
                        B(i, j) = 1.0;
                    } 
                    // Se va dal maggiore al minore -> -1
                    else {
                        B(i, j) = -1.0;
                    }
                    break;                // uso break perché una volta trovato il resistore associato all'arco è inutile continuare a scorrere gli altri resistori 
                }
            }
        }
    }
}

// Costruisce il vettore v  
Eigen::VectorXd calcola_vettore_termini_noti(const std::vector<Component>& netlist, 
                                             const std::vector<std::vector<int>>& cicli) 
{
    size_t n = cicli.size(); 
    // Inizializzo con zeri
    Eigen::VectorXd v_vector = Eigen::VectorXd::Zero(n);

    for (size_t j = 0; j < n; j++) {
        const auto& ciclo = cicli[j];
        double somma_generatori = 0.0;

        for (size_t k = 0; k < ciclo.size() - 1; k++) {
            int u = ciclo[k];
            int v = ciclo[k + 1];

            for (const auto& comp : netlist) {
                if (comp.type == 'V') {
                    // comp.node1 = POLO MENO (-), comp.node2 = POLO PIÙ (+)
                    if (u == comp.node1 && v == comp.node2) {
                        // Attraversato da MENO a PIÙ -> contributo positivo
                        somma_generatori += comp.value;
                    } 
                    else if (u == comp.node2 && v == comp.node1) {
                        // Attraversato da PIÙ a MENO -> contributo negativo
                        somma_generatori -= comp.value;
                    }
                }
            }
        }
        v_vector(j) = somma_generatori; 
    }

    return v_vector;
}