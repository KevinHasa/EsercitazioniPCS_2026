#pragma once

#include <vector>       
#include <set>          
#include <map>          
#include <algorithm>    
#include <iterator>     // per std::distance e std::advance
#include <stdexcept>    // per std::out_of_range
#include "unidirected_edge.hpp"

template <typename T>
class unidirected_graph {
private:
	std::set<T> nodes;                                     // nodi univoci
	std::set<unidirected_edge<T>> edges;                   // archi ordinati automaticamente da set
	std::map<T, std::set<T>> adj_list;					   // per ogni nodo la lista dei vicini

public:
	// costruttori
	unidirected_graph() = default;  								// crea grafo vuoto
	unidirected_graph(const unidirected_graph& other) = default;    // copia i dati da other
	
	
	// trova vicini
	std::set<T> neighbours(const T& node) const {     
		if (adj_list.count(node)) {                    // se il nodo esiste nella mappa
			return adj_list.at(node);                  // restituisce il set dei vicini
		}
		return {};									   // restituisce set vuoto
	}
	
	
	// aggiunge arco
	void add_edge(const unidirected_edge<T>& e) {
		edges.insert(e);                                              // aggiunge arco in ordine ignorando duplicati
		
		nodes.insert(e.from());										 // aggiunge
		nodes.insert(e.to());                                        // i due nodi
		
		adj_list[e.from()].insert(e.to());							 // aggiungo nodi e vicini
		adj_list[e.to()].insert(e.from());
	}


	// restituisce tutti gli archi
	std::vector<unidirected_edge<T>> all_edges() const {
		return std::vector<unidirected_edge<T>>(edges.begin(), edges.end());    // converto il set in vector solo per il return
	}
	
	
	// restituisce tutti i nodi
	std::set<T> all_nodes() const {
		return nodes;
	}
	
	
	// restituisce numerazione arco
	int edge_number(const unidirected_edge<T>& e) const {
		auto it = edges.find(e);
		if (it == edges.end()) return -1;
		return std::distance(edges.begin(), it);             // distanza dall'inizio del set a it
	}
	
	
	// restituisce arco dato numero arco
	unidirected_edge<T> edge_at(int idx) const {
		if (idx < 0 || idx >= (int)edges.size()) {
			throw std::out_of_range("indice non valido");           
		}
		
		// sposta iteratore dall'inizio fino alla posizione richiesta 
		auto it = edges.begin();
		std::advance(it, idx);
		return *it;
	}
	
		
	// differenza tra grafi
	unidirected_graph operator-(const unidirected_graph& other) const {
		unidirected_graph result;                                             // crea grafo vuoto
		for (const auto& e : this->edges) {                                   // cicla su tutti gli archi del primo grafo
			if (other.edges.find(e) == other.edges.end()) {
				result.add_edge(e);                                           // se l'arco non esiste nel secondo lo aggiungo al risultato
			}
		}
		return result;
	}
	

	// aggiunge nodi isolati
	void add_node(const T& node) {                                 
		nodes.insert(node);                                // aggiunge nodo all'elenco generale
		if (adj_list.find(node) == adj_list.end()) {
			adj_list[node] = std::set<T>();                // crea lista vicini vuota
		}
	}
};


