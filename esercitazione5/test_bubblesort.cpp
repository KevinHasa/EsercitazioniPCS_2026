#include <iostream>
#include <vector>
#include "randfiller.h"
#include "sort.hpp"

int main(void)
{
	randfiller rf; /* Creo l'istanza per il randfiller */
	std::vector<int> dim(100); /* Vettore con le dimensioni  */
	rf.fill(dim, 0, 10000); /* Dimensioni casuali da applicare ai vettori */
	
	for (int i = 0; i < 50; i++) { /* Creo 50 vettori di int e 50 di float */
		
		/* Creo i vettori con le dimensioni casuali dal vettore dim*/
		std::vector<int> v_int(dim[i]);
		std::vector<float> v_float(dim[50+i]);
		
		/* Li riempio in maniera casuale */
		rf.fill(v_int, -10000, 10000);
		rf.fill(v_float, -10000.0f, 10000.0f);
		
		/* Li ordino */
		bubblesort(v_int);
		bubblesort(v_float);
		
		/* Controllo che siano ordinati e fermo il ciclo nel caso non lo siano */
		if (!is_sorted(v_int) || !is_sorted(v_float)){
			return EXIT_FAILURE;
		}
	}
	
	/* Creo anche un vettore di strnghe e uno nullo, li ordino e controllo che siano ordinati */
	std::vector<std::string> v_string = {"Torino", "Napoli", "Roma", "Milano", "Asti", "asti", "123", "122", "113", "11", "011"};
	std::vector<int> v_null = {};
	
	bubblesort(v_string);
	bubblesort(v_null);
		
	if (!is_sorted(v_string) || !is_sorted(v_null)) {
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}