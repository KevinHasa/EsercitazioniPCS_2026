#include <vector>
#include <set>
#include <map>
#include <stack>
#include "unidirected_graph.hpp"

unidirected_graph<int> calcola_albero_dfs(const unidirected_graph<int>& G) 
{
	unidirected_graph<int> albero; /* Creo l'albero a cui aggiungo nodi e archi */
	std::stack<int> stack;
	std::set<int> nodi = G.all_nodes();
	std::map<int, int> pred;

	/* Creo una mappa le cui chiavi sono i nodi e i cui valori sono 0 se non ci sono passato e 1 altrimenti */
	std::map<int, int> reached; 
	
	for(const int& nodo : nodi) {
		reached[nodo] = 0;
		pred[nodo] = -1;
	}
	
	int s = *G.all_nodes().begin();
	stack.push(s);
	
	while(!stack.empty()) {
		int v = stack.top();
		stack.pop();
		if (reached[v]) continue;
		reached[v] = 1;
		
		if (pred[v] != -1) {
			albero.add_edge(unidirected_edge<int>(pred[v], v));
		}
		
		for(const int& u : G.neighbours(v)) {
			if(!reached[u]) {
				pred[u] = v;
				stack.push(u);
			}
		}
	}
	
	return albero;
}

// Trova ricorsivamente il cammino sull'albero tra due nodi int
bool findpath(const unidirected_graph<int>& T_tree, const int& u, const int& v, std::set<int>& visited, std::vector<int>& path) {
    visited.insert(u);
    path.push_back(u);

    if (u == v) return true;

    for (const int& n : T_tree.neighbours(u)) {
        if (visited.find(n) == visited.end()) {
            if (findpath(T_tree, n, v, visited, path)) return true;
        }
    }

    path.pop_back();
    return false;
}

std::vector<std::vector<int>> estrai_cicli_dfs(const unidirected_graph<int>& G) {
	if (G.all_nodes().empty()) return {};
	
    std::vector<std::vector<int>> cicli;
    
    unidirected_graph<int> T_tree = calcola_albero_dfs(G);
    
    unidirected_graph<int> C = G - T_tree;

    // Itero sugli archi del co-albero per chiudere i cicli fondamentali
    for (const auto& arco : C.all_edges()) {
        int u = arco.from();
        int v = arco.to();
        
        std::set<int> visited;
        std::vector<int> path;
        
        if (findpath(T_tree, u, v, visited, path)) {
            // Aggiungo u alla fine per chiudere la sequenza del ciclo
            path.push_back(u);
            cicli.push_back(path);
        }
    }
    return cicli;
}