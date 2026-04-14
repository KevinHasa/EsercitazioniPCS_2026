#include "timecounter.h"
#include "randfiller.h"
#include "sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "bubble_sort.hpp"
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <algorithm>

int main(void) {
	
	timecounter tc; /* Creo l'istanza del timecounter */
	randfiller rf;  /* Creo l'istanza del randfiller */
	
	/* Creo i vettori di dimensioni 4,8,...,8192 per poi riempirli con numeri interi casuali */
	for (int i = 2; i < 14; i++) {
		
		int dim = std::pow(2,i);
		std::vector<int> v(dim); 
		rf.fill(v, -10000, 10000);
		
		/* Ora creo 3 copie del vettore in modo da testare il tempo di di bubblesort,insertionsort,selectionsort e std::sort sul vettore e sulle sue copie */
		std::vector<int> copia1 = v; /* Per il bubblesort */
		std::vector<int> copia2 = v; /* Per il insertionsort */
		std::vector<int> copia3 = v; /* Per il selectionsort */
		
		/* Ora calcolo il tempo di ogni algortimo */
		tc.tic(); /* Faccio partire il tempo */
		std::sort( v.begin(), v.end() );
		double time_std = tc.toc(); /* Fermo il tempo */
		
		tc.tic();
		bubble_sort(copia1);
		double time_bubble = tc.toc();
		
		tc.tic();
		insertion_sort(copia2);
		double time_insertion = tc.toc();
		
		tc.tic();
		selection_sort(copia3);
		double time_selection = tc.toc();
		
		
		std::cout << "La dimensione del vettore è " << dim << "\n";
		std::cout << "Il tempo di std::sort è " << time_std << " sec" << "\n";
		std::cout << "Il tempo di Bubble-Sort è " << time_bubble << " sec" << "\n";
		std::cout << "Il tempo di Insertion-Sort è " << time_insertion << " sec" << "\n";
		std::cout << "Il tempo di Selection-Sort è " << time_selection << " sec" << "\n";
		std::cout << "---------------------------------------" << "\n";
	}
	return 0;
}