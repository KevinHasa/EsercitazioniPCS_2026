#include "unidirected_graph.hpp"
#include<iostream>

int main() 
{
	unidirected_edge<int> e1(2,1);
	unidirected_edge<int> e2(3,2);
	unidirected_edge<int> e3(4,3);
	unidirected_edge<int> e4(4,5);
	unidirected_edge<int> e5(5,1);
	unidirected_edge<int> e6(7,1);
	unidirected_edge<int> e7(9,1);
	unidirected_edge<int> e8(4,1);
	unidirected_edge<int> e9(1,2);
	
	/* Verifico il funzionamento di from(), to() e degli opratori < e == */
	std::cout << "L'arco " << e1 << " parte dal nodo " << e1.from() << " e arriva al nodo " << e1.to() << "\n";
	bool confronto1 = e1 < e2;
	bool confronto2 = e8 < e2;
	bool confronto3 = e4 < e3;
	bool confronto4 = e9 == e1;
	bool confronto5 = e2 == e3;
	std::cout << confronto1 << "\n";
	std::cout << confronto2 << "\n";
	std::cout << confronto3 << "\n";
	std::cout << confronto4 << "\n";
	std::cout << confronto5 << "\n";
	
	/* Verifico la classe unidirected_graph e i metodi add_edge(), all_edges(), all_nodes(), edge_number(), edge_at()*/
	unidirected_graph<int> grafo1;
	grafo1.add_edge(e1); /* da notare che il grafo inizialmente è vuoto e l'operazione di aggiungere archi aggiunge automaticamente anche i nodi (evitando comunque i duplicati essendo aggiunti a un set) */
	grafo1.add_edge(e2);
	grafo1.add_edge(e3);
	grafo1.add_edge(e4);
	grafo1.add_edge(e5);
	grafo1.add_edge(e6);
	
	std::set<unidirected_edge<int>> archi = grafo1.all_edges();
	std::set<int> nodi = grafo1.all_nodes();
	
	std::cout << "Gli archi del grafo1 sono: ";
	for (auto& arco : archi) {
		std::cout << arco << " ";
	}
		
	std::cout << "\n";
	
	for (auto& arco : archi) {
		std::cout << "Il numero dell'arco " << arco << " è " << grafo1.edge_number(arco) << "\n";
	}
	
	for (size_t i = 0; i < archi.size(); i++) {
		std::cout << "Dato il numero d'arco: " << i << ", l'arco corrispondente è " << grafo1.edge_at(i) << "\n";
	}
	
	std::cout << "\n";
	
	for (auto& nodo : nodi) {
		std::cout << "Gli adiacenti del nodo " << nodo << " sono:" << "\n";
		std::set<int> adiacenti = grafo1.neighours(nodo);
		for (auto& vicino : adiacenti) {
			std::cout << "il nodo " << vicino << "\n";
		}
	}
	
	/* Creo un secondo grafo */
	unidirected_graph<int> grafo2;
	grafo2.add_edge(e1);
	grafo2.add_edge(e2);
	grafo2.add_edge(e3);
	grafo2.add_edge(e7);
	grafo2.add_edge(e8);
	
	/* Creo i grafi differenza */
	unidirected_graph<int> g1 = grafo1 - grafo2;
	unidirected_graph<int> g2 = grafo2 - grafo1;
	
	std::cout << "\n";
	
	/* Verifico che i grafi differenza funzionino secondo la definizione data e controllo che a livello di nodi e archi funzioni tutto attraverso il metodo neighours che mi permette di controllare sia gli archi che i nodi e che tutto funzioni */
	std::set<unidirected_edge<int>> a1 = g1.all_edges();
	std::set<int> n1 = g1.all_nodes();
	std::cout << "Gli archi del grafo g1 (grafo1 - grafo2) sono: ";
	
	for (auto& arco : a1) {
		std::cout << arco << " ";
	}
		
	std::cout << "\n";
	
	for (auto& nodo : n1) {
		std::cout << "Gli adiacenti del nodo " << nodo << " sono:" << "\n";
		std::set<int> adiacenti = g1.neighours(nodo);
		for (auto& vicino : adiacenti) {
			std::cout << "il nodo " << vicino << "\n";
		}
	}
	
	std::cout << "\n";
	
	std::set<unidirected_edge<int>> a2 = g2.all_edges();
	std::set<int> n2 = g2.all_nodes();
	std::cout << "Gli archi del grafo g2 (grafo2 - grafo1) sono: ";
	
	for (auto& arco : a2) {
		std::cout << arco << " ";
	}
		
	std::cout << "\n";
	
	for (auto& nodo : n2) {
		std::cout << "Gli adiacenti del nodo " << nodo << " sono:" << "\n";
		std::set<int> adiacenti = g2.neighours(nodo);
		for (auto& vicino : adiacenti) {
			std::cout << "il nodo " << vicino << "\n";
		}
	}
	
	return 0;
}