#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include "unidirected_graph.hpp"

// funzione dfs per creare il primo albero
unidirected_graph<int> dfs(const unidirected_graph<int>& G, const int& s)
{
	unidirected_graph<int> albero; // creo l'albero a cui aggiungo nodi e archi 
	std::stack<int> stack;
	std::set<int> nodi = G.all_nodes();
	std::map<int, int> pred;

	// creo una mappa le cui chiavi sono i nodi e i cui valori sono 0 se non ci sono passato e 1 altrimenti 
	std::map<int, int> reached; 
	
	for(const int& nodo : nodi) {
		reached[nodo] = 0;
		pred[nodo] = -1;
	}
	
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

// funzione bfs che trova il cammino tra due nodi (mi serve per il cammino tra v+ e v-)
std::vector<int> cammino_bfs(const unidirected_graph<int>& G, const int& u, const int& v)
{
	std::queue<int> queue;
	std::set<int> nodi = G.all_nodes();
	std::vector<int> cammino;

	// creo una mappa le cui chiavi sono i nodi e i cui valori sono 0 se non ci sono passato e 1 altrimenti 
	std::map<int, int> reached; 
	
	// inizializzo la mappa con i predecessori in modo da ricostruire poi il cammino
	std::map<int, int> pred; 
	
	for(const int& nodo : nodi) {
		reached[nodo] = 0;
		pred[nodo] = -1;
	}
	
	bool trovato = false;
	queue.push(u);
	
	while(!queue.empty()) {
		int a = queue.front();
		queue.pop();
		reached[a] = 1;
		std::set<int> LA = G.neighbours(a);
		
		for(const int& nodo : LA) {
			if(reached[nodo] == 0) {
				reached[nodo] = 1;
				pred[nodo] = a;
				queue.push(nodo);
			}
			if (nodo == v) {
				trovato = true;
				break;
			}
		}
		
		if (trovato == true) {
			break;
		}
	}
	
	if (!trovato &&  u != v) {
		return{};
	}
	
	// ora aggiungo i nodi da v a u risalendo i predecessori e poi inverto il vettore
	cammino.push_back(v);
	int nodo = v;
	
	while (nodo != u) {
		cammino.push_back(pred[nodo]);
		nodo = pred[nodo];
	}
	
	std::reverse(cammino.begin(), cammino.end());
	
	return cammino;
}

// prodotto scalare modulo 2
int dot_mod2(const std::vector<bool>& a, const std::vector<bool>& b) {
    int res = 0;
    for (size_t i = 0; i < a.size(); ++i) {
		res ^= (a[i] & b[i]);
	}
    return res;
}

// differenza simmetrica
std::vector<bool> sym_diff(const std::vector<bool>& a, const std::vector<bool>& b) {
    std::vector<bool> res(a.size());
	for (size_t i = 0; i < a.size(); ++i) {
		res[i] = a[i] ^ b[i];
	}
    return res;
}

// funzione per creare un vettore con gli indici degli archi del coalbero
std::vector<int> indici_coalbero(const unidirected_graph<int>& G, const unidirected_graph<int>& T)
{
	if (G.all_nodes().empty() || G.all_edges().empty()) return {};

	unidirected_graph<int> C = G - T; // coalbero
	std::vector<int> indici; // vettore che conterrà gli indici degli archi contenuti nel coalbero
	
	for (auto& arco : G.all_edges()) {
		int i = C.edge_number(arco);
		if (i != -1) { // controllo se l'arco appartiene al coalbero
			int i_G = G.edge_number(arco);
			indici.push_back(i_G); // aggiungo al vettore l'enumerazione dell'arco che ha in G
		}
	}
	return indici;
}

std::vector<std::vector<int>> de_pina(const unidirected_graph<int>& G) 
{
	if (G.all_nodes().empty()) return {};
	
	// prendo il primo nodo, costruisco l'albero dalla visita DFS e il vettore con gli indici del coalbero
	int s = *G.all_nodes().begin(); 
	unidirected_graph<int> T = dfs(G, s); 
	std::vector<int> archi_coalbero = indici_coalbero(G, T);
	
	size_t m = G.all_edges().size();
	size_t n = G.all_nodes().size();
	size_t k = archi_coalbero.size();
	std::vector<std::vector<bool>> S(k, std::vector<bool>(m, false)); // inizializzo un vettore di k vettori S_i con m volte false
	std::vector<std::vector<bool>> C;
	std::vector<std::vector<int>> cicli_finali;
	
	for (size_t i = 0; i < k; i++) {
		int indice_arco = archi_coalbero[i];
		S[i][indice_arco] = true; // ogni S_i contiene 1 nelle posizioni che corrispondono agli archi del coalbero e 0 sul resto
	}
	
	for (size_t i = 0; i < k; i++) {
		unidirected_graph<int> G_lift; // inizializzo il grafo G' in cui avrò i nodi u+, u-, v+, v- a partire da u e v
		
		for (size_t indice_arco = 0; indice_arco < G.all_edges().size(); indice_arco++) {
			unidirected_edge<int> arco = G.edge_at(indice_arco);
			int u1 = arco.from(); // u+
			int v1 = arco.to();   // v+
			int u2 = u1 + n;      // u-
			int v2 = v1 + n;      // v-
			// un cammino da v- a v+ in G' corrisponde a un ciclo in G
			
			if (S[i][indice_arco] == true) {
				G_lift.add_edge(unidirected_edge<int>(u1, v2));
				G_lift.add_edge(unidirected_edge<int>(u2, v1));
			}
			
			else {
				G_lift.add_edge(unidirected_edge<int>(u1, v1));
				G_lift.add_edge(unidirected_edge<int>(u2, v2));
			}
		}
		
		std::vector<bool> C_i(m, false); // vettori che andranno a riempire C in ogni ciclo e in cui ci saranno i cicli migliori per l'iterazione corrente
		size_t minl = m + 1; // per tenere traccia del numero di archi e lo inizializzo a un numero grande impossibile per questa variabile
		
		// per ogni nodo cerco, cerco il cammino minimo tra v- e v+ in G'
		for (const auto& v1 : G.all_nodes()) {    // prendo tutti i nodi come nodi+
			int v2 = v1 + n;    // prendo i nodi v- in questo modo, motivo per cui itero sui nodi di G e non di G_lift
			std::vector<int> cammino = cammino_bfs(G_lift, v2, v1);  // calcolo il percorso tra v- e v+
			if (cammino.empty()) {
				continue;
			}
			
			std::vector<bool> C_candidato(m, false); // inizializzo dei vettori di bool candidati per indicare il ciclo minimo, che poi salvero in C_i
			
			for (size_t t = 0; t < cammino.size()-1; t++) {
				
				int u = cammino[t];
				int v = cammino[t+1];
				
				if (cammino[t] > static_cast<int>(n)) { // static_cast per trasformare n da size_t a int nel confronto con cammino[t] che è un int (per aggirare il warning)
					u = cammino[t] - n;
				}
				if (cammino[t+1] > static_cast<int>(n)) {
					v = cammino[t+1] - n;
				}
				unidirected_edge<int> e(u, v); // creo l'arco tra i due nodi consecutivi
				int num = G.edge_number(e); //trovo l'enumerazione dell'arco
				if (num != -1) {
					C_candidato[num] = !C_candidato[num];
				}
			}
			
			size_t ind = 0; // inizializzo un indice che tiene conto del numero degli archi
			
			for (const bool& j : C_candidato) {
				if (j == true) {
					ind++;
				}
			}
			
			if (ind < minl) {
				minl = ind;
				C_i = C_candidato;
			}
		}
		
		// mi assicuro che i cicli futuri siano linearmente indipendenti da quelli già trovati
		for (size_t j = i+1; j < k; j++) {
			if (dot_mod2(C_i, S[j]) == 1) {
				S[j] = sym_diff(S[j], S[i]);  // rendo S[j] ortogonali a S[i] anche se in origine non lo era
			}
		}
		
		C.push_back(C_i);
	}
	
	// ogni vettore C_i (che chiamiamo Ci per evitare variable shadowing) che appartiene a C, rappresenta un ciclo, avendo 1 nella posizione che corrisponde all'enumerazione in G dell'arco presente. Ora bisogna trasformalo in un vettore di interi che riporti il ciclo in modo leggibile
	for (const auto& Ci : C) {
		unidirected_graph<int> sottografo; // creo un sottografo a cui aggiungo gli archi che corrispondono a 1 nel vettore C_i (sarà un ciclo)
		size_t idx = 0;
		for (const bool& j : Ci) {
			if (j == true) {
				sottografo.add_edge(G.edge_at(idx));
			}
			idx++;
		}
		
		int nodo_start = *sottografo.all_nodes().begin();  // prendo un nodo dal sottografo da cui inziare
		std::vector<int> ciclo; // vettore in cui metteremo idx nodi nell'ordine in cui li visitiamo
		int curr = nodo_start;  // nodo corrente
		int prev = -1;  // nodo precedente da cui arriviamo
		
		while (true) {  // cammino lungo il ciclo finchè non torno al nodo di partenza 
			ciclo.push_back(curr); // riempio il vettore che rappresenta il ciclo
			int next = -1;  // nodo successivo
			
			for (int v : sottografo.neighbours(curr)) {
				if (v != prev) {  // ogni nodo ha due vicini e se v non è il prev, allora è il next
					next = v;
					break;
				}
			}
			
			if (next == -1) {
				break;
			}
			
			if (next == nodo_start) {
				ciclo.push_back(nodo_start); // chiudo il ciclo quando ritorno all'inizio
				break;
			}
			
			prev = curr;
			curr = next;
		}
		
		cicli_finali.push_back(ciclo);
	}
	
	return cicli_finali;
}