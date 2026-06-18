#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
class unidirected_edge {
private:
	T node_from;
	T node_to;
	
public:
	// costruttore garantisce from < to
	unidirected_edge(const T& u, const T& v) {
		node_from = std::min(u, v);
		node_to = std::max(u, v);
	}
	
	T from() const {return node_from;}
	T to() const {return node_to;}
	
	// operatore di uguaglianza
	bool operator==(const unidirected_edge& other) const {
		return (node_from == other.node_from && node_to == other.node_to);
	}
	
	// operatore di ordinamento
	bool operator<(const unidirected_edge& other) const {
		if (node_from != other.node_from) {
			return node_from < other.node_from;
		}
		return node_to < other.node_to;
	}
	
};

// operatore di stampa
template <typename T>
std::ostream& operator<<(std::ostream& os, const unidirected_edge<T>& e) {
	os << "(" << e.from() << ", " << e.to() << ")";
	return os;
}
	

