#include <iostream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include "unidirected_graph.hpp"

struct Component {
    std::string name;
    char type;        // 'R' o 'V'
    double value;     // Valore in Ohm o Volt
    int node1;        // Nodo di partenza 
    int node2;        // Nodo di arrivo 
};

// Dichiarazione funzioni
std::vector<Component> read_netlist(const std::string& filename);

std::vector<std::vector<int>> estrai_cicli_dfs(const unidirected_graph<int>& G);

std::vector<std::vector<int>> de_pina(const unidirected_graph<int>& G);

void genera_matrici_circuito(const unidirected_graph<int>& G, 
                             const std::vector<Component>& netlist, 
                             const std::vector<std::vector<int>>& cicli,
                             Eigen::MatrixXd& B,
                             Eigen::MatrixXd& R,
                             std::vector<Component>& resistori_ordinati);

Eigen::VectorXd calcola_vettore_termini_noti(const std::vector<Component>& netlist, 
                                             const std::vector<std::vector<int>>& cicli);

Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A, 
                                    const Eigen::VectorXd& b, 
                                    const Eigen::VectorXd& x0, 
                                    const double res_tol = 1.0e-12, 
                                    const unsigned int it_max = 10000);


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        std::cerr << "Errore: Manca il file di input" << std::endl;
        return -1;
    }

    std::string filename = argv[1];
    
    auto components = read_netlist(filename);
    
    if (components.empty()) {
        return -1;
    }

    // Costruzione del grafo 
    unidirected_graph<int> G;
    for (const auto& comp : components) {
        G.add_edge(unidirected_edge<int>(comp.node1, comp.node2));
    }

    // --- CON DFS ---
    std::vector<std::vector<int>> cicli_dfs = estrai_cicli_dfs(G);
    
    std::cout << "--- RISULTATI CON METODO DFS ---" << std::endl;

    Eigen::MatrixXd B_dfs;
    Eigen::MatrixXd R_dfs;
    std::vector<Component> resistori_ordinati_dfs;

    genera_matrici_circuito(G, components, cicli_dfs, B_dfs, R_dfs, resistori_ordinati_dfs);
    Eigen::VectorXd v_dfs = calcola_vettore_termini_noti(components, cicli_dfs);

    Eigen::MatrixXd A_dfs = B_dfs.transpose() * R_dfs * B_dfs;
    Eigen::VectorXd x0_dfs = Eigen::VectorXd::Zero(cicli_dfs.size());

    Eigen::VectorXd i_maglia_dfs = gradiente_coniugato(A_dfs, v_dfs, x0_dfs);
    Eigen::VectorXd t_tensioni_dfs = R_dfs * B_dfs * i_maglia_dfs;

    for (size_t idx = 0; idx < resistori_ordinati_dfs.size(); ++idx) {
        std::cout << resistori_ordinati_dfs[idx].name << " " << t_tensioni_dfs(idx) << std::endl;
    }
    std::cout << std::endl;


    // --- CON DE PINA ---
    std::vector<std::vector<int>> cicli_de_pina = de_pina(G);

    std::cout << "--- RISULTATI CON METODO DE PINA ---" << std::endl;

    Eigen::MatrixXd B_depina;
    Eigen::MatrixXd R_depina;
    std::vector<Component> resistori_ordinati_depina;

    genera_matrici_circuito(G, components, cicli_de_pina, B_depina, R_depina, resistori_ordinati_depina);
    Eigen::VectorXd v_depina = calcola_vettore_termini_noti(components, cicli_de_pina);

    Eigen::MatrixXd A_depina = B_depina.transpose() * R_depina * B_depina;
    Eigen::VectorXd x0_depina = Eigen::VectorXd::Zero(cicli_de_pina.size());

    Eigen::VectorXd i_maglia_depina = gradiente_coniugato(A_depina, v_depina, x0_depina);
    Eigen::VectorXd t_tensioni_depina = R_depina * B_depina * i_maglia_depina;

    for (size_t idx = 0; idx < resistori_ordinati_depina.size(); ++idx) {
        std::cout << resistori_ordinati_depina[idx].name << " " << t_tensioni_depina(idx) << std::endl;
    }

    return 0;
}