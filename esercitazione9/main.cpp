#include "graph_visits.hpp"
/*iostream, contenitori.hpp e unidirected_graph,hpp incluso con graph_visits */

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
	unidirected_graph<int> grafo;
	grafo.add_edge(e1); 
	grafo.add_edge(e2);
	grafo.add_edge(e3);
	grafo.add_edge(e4);
	grafo.add_edge(e5);
	grafo.add_edge(e6);
	grafo.add_edge(e7);
	grafo.add_edge(e8);
	grafo.add_edge(e9);
	fifo<int> q;
	lifo<int> s;
	auto albero_bfs = graph_visit(grafo, 4, q);
	auto albero_dfs = recursive_dfs(grafo, 4);
	auto albero_dijkstra = dijkstra(grafo, 4);
	
	std::cout << "Albero BFS: ";
	for(const auto& arco : albero_bfs.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;	
	
	std::cout << "-----------------------------------------------------------------------------------------" << "\n";
	
	std::cout << "Albero DFS: ";
	for(const auto& arco : albero_dfs.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;	
	
	std::cout << "-----------------------------------------------------------------------------------------" << "\n";
	
	std::cout << "Albero DIJKSTRA: ";
	for(const auto& arco : albero_dijkstra.all_edges()) {
		std::cout << arco << " ";
	}
	std::cout << std::endl;
	
	return 0;
}