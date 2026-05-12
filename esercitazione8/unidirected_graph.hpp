#pragma once 
#include<iostream>
#include<set>

template<typename T>
class unidirected_edge
{
	T nodo_from;
	T nodo_to;
	
public:
	
	/* Costruttore user-defined */
	unidirected_edge(const T& nodo1, const T& nodo2)
	{
		if (nodo1 <= nodo2) {
			nodo_from = nodo1;
			nodo_to = nodo2;
		}
		
		else {
			nodo_from = nodo2;
			nodo_to = nodo1;
		}
	}
	
	/* Metodo from() per il nodo di partenza */
	T from() const {
		return nodo_from;
	}
	
	/* Metodo to() per il nodo di arrivo */
	T to() const {
		return nodo_to;
	}
	
	bool operator<(const unidirected_edge& other) const {
		if (nodo_from == other.nodo_from) {
			return (nodo_to < other.nodo_to);
		}
		
		return (nodo_from < other.nodo_from);
	}
	
	bool operator==(const unidirected_edge& other) const {
		return (nodo_from == other.nodo_from && nodo_to == other.nodo_to);
	}
	
};

template<typename T>
std::ostream&
operator<<(std::ostream& os, const unidirected_edge<T>& a) {
	os << "(" << a.from() << "," << a.to() << ")";
	return os;
}



template<typename T>
class unidirected_graph 
{
	std::set<T> nodi;
	std::set<unidirected_edge<T>> archi;

public:
	
	/* Costruttore di default */
	unidirected_graph()
	: nodi(), archi()
	{}
	
	/* Costruttore di copia */
	unidirected_graph(const unidirected_graph& other)
	: nodi(other.nodi), archi(other.archi)
	{}
	
	/* Costruttore user-defined */
	unidirected_graph(const std::set<T>& nodi_, const std::set<unidirected_edge<T>>& archi_)
	: nodi(nodi_), archi(archi_)
	{}
	
	/* metodo che dato un nodo e restituisce i nodi adiacenti */
	std::set<T> neighours(const T& nodo) const {
		std::set<T> adiacenti;
		for (auto& arco : archi) {
				
			if (nodo == arco.from()) {
				adiacenti.insert(arco.to());
			}
			
			if  (nodo == arco.to()) {
				adiacenti.insert(arco.from());
			}
		}
		return adiacenti;
	}
	
	/* metodo che aggiunge archi al grafo */
	void add_edge(const unidirected_edge<T>& arco) {
		
		archi.insert(arco);
		
		/* posso aggiungere i nodi in modo da evitare una funzione add_node in più e in ogni caso, nel caso ci fossero già, non verrebbero duplicati perchè non ci sono duplicati nei set  */
		T nodo1 = arco.from();
		T nodo2 = arco.to();
		nodi.insert(nodo1);
		nodi.insert(nodo2);
	}
	
	/* metodo che restituisce tutti gli archi */
	std::set<unidirected_edge<T>> all_edges() const {
		return archi;
	}
	
	/* metodo che restituisce tutti i nodi */
	std::set<T> all_nodes() const {
		return nodi;
	}
	
	/* metodo che, dato un arco, ne restituisce la sua numerazione all'interno del grafo */
	size_t edge_number(const unidirected_edge<T>& arco) const {
		size_t i = 0;
		
		for (auto& edge : archi) {
			if (edge == arco){
				break;
			}
			i++;
		}
		return i;
	}
	
	/* metodo che, dato un numero d'arco, restituisce il corrispondente oggetto arco all'interno del grafo */
	unidirected_edge<T> edge_at(size_t edge_number) const{
		
		if(edge_number >= archi.size()) {
			std::cerr <<"\nERRORE: chiamato edge_at con numero non ammissibile" << "\n";
		}
		
		size_t i = 0;
		for (auto& edge : archi) {
			
			if (i == edge_number) {
				unidirected_edge arco = edge;
				return arco;
			}
			i++;
		}
		return unidirected_edge<T>(T{}, T{}); /* Ci metto un arco vuoto che serve solo per evitare un comportamento indefinito del metodo nel caso di errore */
	}
	
	/* operatore che calcola G-G' come gli archi presenti in G e non in G' */
	unidirected_graph operator-(const unidirected_graph<T>& other) const {
		
		unidirected_graph<T> grafo_diff;
		
		for (auto& arco : archi) {
			auto it = other.archi.find(arco);
			if (it == other.archi.end()) {
				grafo_diff.add_edge(arco);
			}
		}
		
		return grafo_diff;
	}
};