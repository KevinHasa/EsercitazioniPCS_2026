#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Component {
    string name;
    char type;        // 'R' o 'V'
    double value;     // Valore in Ohm o Volt
    int node1;        // Nodo di partenza 
    int node2;        // Nodo di arrivo 
};

vector<Component> read_netlist(const string& filename) {
    ifstream file(filename);
    vector<Component> components;

    if (!file.is_open()) {
        cerr << "Errore: impossibile aprire " << filename << endl;
        return components;
    }

    string nome;
    double valore;
    int n1, n2;

    while (file >> nome >> valore >> n1 >> n2) {
        Component c;
        c.name = nome;
        c.value = valore;
        c.node1 = n1;
        c.node2 = n2;
        c.type = nome[0]; 
        components.push_back(c);
    }

    file.close();
    return components;
}

