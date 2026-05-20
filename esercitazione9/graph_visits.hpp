#pragma once 
#include <queue>
#include <map>
#include "contenitori.hpp"
#include "unidirected_graph.hpp" /* Mi aggiunge anche tutto ciò che riguarda i set */

template<typename T, typename C> /* Rispettivamente tipo del nodo sorgente e tipo del contenitore */
unidirected_graph<T> graph_visit(const unidirected_graph<T>& G, const T& s, C& c)
{
	unidirected_graph<T> albero; /*Creo l'albero a cui aggiungo nodi e archi */
	
	std::set<T> nodi = G.all_nodes();

	/* Creo una mappa le cui chiavi sono i nodi e i cui valori sono 0 se non ci sono passato e 1 altrimenti */
	std::map<T, int> reached; 
	
	for(const T& nodo : nodi) {
		reached[nodo] = 0;
	}
	
	c.put(s);
	
	while(!c.empty()) {
		T v = c.get();
		reached[v] = 1;
		std::set<T> LA = G.neighbours(v);
		
		for(const T& nodo : LA) {
			if(reached[nodo] == 0) {
				c.put(nodo);
				reached[nodo] = 1;
				albero.add_edge(unidirected_edge(v, nodo));
			}
		}
	}
	
	return albero;
}

/* Funzione che svolge la parte ricorsiva in recursive_dfs */
template<typename T>
void recursive(const unidirected_graph<T>& G, const T& v, std::map<T, int>& reached, unidirected_graph<T>& albero)
{
	reached[v] = 1;
	std::set<T> LA = G.neighbours(v);
	for(const T& nodo : LA) {
		if(reached[nodo] == 0) {
			albero.add_edge(unidirected_edge(v, nodo));
			recursive(G, nodo, reached, albero);
		}
	}
}

template<typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& G, const T& s)
{
	unidirected_graph<T> albero;
	std::map<T, int> reached;
	
	recursive(G, s, reached, albero);
	
	return albero;
}


template<typename T>
unidirected_graph<T> dijkstra(const unidirected_graph<T>& G, const T& s)
{
	std::map<T, int> dist;	/* Mappa che associa a ogni nodo la distanza da s */
	std::map<T, T> pred;	/* Mappa che associa a ogni nodo, il suo predecessore e che servirà per l'albero */
	unidirected_graph<T> albero;
	std::set<T> nodi = G.all_nodes();
	std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> pq;		/* priority queue */
	
	for(const T& nodo : nodi) {
		dist[nodo] = 1e9;	/* Inizializzo tutte le distanze a un numero molto grande */
		pred[nodo] = T{};	/* Inizializzo i predecessori come nodi "vuoti" */
	}
	
	dist[s] = 0;

	for(const T& nodo : nodi) {
		pq.push({dist[nodo], nodo});
	}
		
	while(!pq.empty()) {
		auto [d, v] = pq.top();		/* leggo il primo elemento della coda(quello più vicino), dove v è il nodo e d è la distanza con s */
		pq.pop();
		std::set<T> LA = G.neighbours(v);
		
		if (d != dist[v]) {
			continue;	/* In modo da considerare ogni nodo una singola volta*/
		}
		
		for(const T& nodo : LA) {
			if(dist[nodo] > dist[v] + 1) {		/*+1 per il peso considerato uguale sempre a 1 */
				dist[nodo] = dist[v] + 1;
				pred[nodo] = v;
				pq.push({dist[nodo], nodo});
			}
		}
	}
	
	for(const auto& [figlio, padre] : pred) {
		if(padre != T{}) {
			albero.add_edge(unidirected_edge<T>(figlio, padre));
		}
	}
	
	return albero;
}
	