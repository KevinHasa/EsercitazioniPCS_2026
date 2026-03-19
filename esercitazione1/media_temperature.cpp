#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[]) 
{
	if ( argc < 2 ) {
		cerr << "Non è stato specificato il fie\n";
		return 1;
	}

	string filename = argv[1];
	ifstream file(filename);


	if ( file.is_open() ) {
			string citta;
			double temp00, temp06, temp12, temp18;
			while (file >> citta >> temp00 >> temp06 >> temp12 >> temp18) {
				double media_temp = (temp00 + temp06 + temp12 + temp18)/4.0;
				cout << citta << " " << media_temp << "\n";
			}
	}
	else {
		cerr << "Problema nell'aprire il file\n";
		return 1;
	}

	return 0;
}







