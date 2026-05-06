#include "timecounter.h"
#include "randfiller.h"
#include "sort.hpp"
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <algorithm>
#include "sort.hpp"

int main(void) {
	
	timecounter tc; /* Creo l'istanza del timecounter */
	randfiller rf;  /* Creo l'istanza del randfiller */
	
	std::vector<std::vector<int>> vettori(100); /* Creo il vettore che conterrà i 100 vettori */
	
	for (int dim = 0; dim < 31; dim++) 
	{
		int dimensione = 10*dim; /* I vettori li creo di dimensioni 0,5,10,15,20,...,100 */
		
		for (int i = 0; i < 100; i++)
		{
			vettori[i].resize(dimensione);
			rf.fill(vettori[i], -10000, 10000); /* Riempio i vettori con numeri casuali */		
		}
	
		/* Ora copio il vettore di vettori in altri 5 in modo da applicare tutti gli algoritmi */
		std::vector<std::vector<int>> vettoriSTD = vettori;
		std::vector<std::vector<int>> vettoriB = vettori;
		std::vector<std::vector<int>> vettoriI = vettori;
		std::vector<std::vector<int>> vettoriS = vettori;
		std::vector<std::vector<int>> vettoriQ = vettori;
		std::vector<std::vector<int>> vettoriM = vettori;
		std::vector<std::vector<int>> vettoriQ2 = vettori;
		
		/* bubblesort */
		tc.tic();
		for (int i = 0; i < 100; i++)
		{
			bubblesort(vettoriB[i]);
		}
		double time_bubble = tc.toc()/100.0;	
		
		/* insertionsort */
		tc.tic();
		for (int i = 0; i < 100; i++)
		{
			insertionsort(vettoriI[i]);
		}
		double time_insertion = tc.toc()/100.0;	
		
		/* selectionsort */
		tc.tic();
		for (int i = 0; i < 100; i++)
		{
			selectionsort(vettoriS[i]);
		}
		double time_selection = tc.toc()/100.0;
		
		/* quicksort */
		tc.tic();
		for (int i = 0; i < 100; i++)
		{
			quicksort(vettoriQ[i], 0, vettoriQ[i].size()-1);
		}
		double time_quick = tc.toc()/100.0;
		
		/* mergesort */
		tc.tic();
		for (int i = 0; i < 100; i++)
		{
			mergesort(vettoriM[i], 0, vettoriM[i].size()-1);
		}
		double time_merge = tc.toc()/100.0;
		
		/* std::sort */
		tc.tic();
		for (int i = 0; i < 100; i++)
		{
			std::sort(vettoriSTD[i].begin(), vettoriSTD[i].end());
		}
		double time_std = tc.toc()/100.0;
		
		
		/* modified_quicksort */
		tc.tic();
		for (int i = 0; i < 100; i++)
		{
			modified_quicksort(vettoriQ2[i], 0, vettoriQ2[i].size()-1);
		}
		double time_modified = tc.toc()/100.0;
		
		
		std::cout << "Dimensione dei vettori: " << dimensione << "\n";
		std::cout << "Il tempo medio di Bubble-Sort è " << time_bubble << " sec" << "\n";
		std::cout << "Il tempo medio di Selection-Sort è " << time_selection << " sec" << "\n";
		std::cout << "Il tempo medio di Insertion-Sort è " << time_insertion << " sec" << "\n";
		std::cout << "Il tempo medio di Merge-Sort è " << time_merge << " sec" << "\n";
		std::cout << "Il tempo medio di Quick-Sort è " << time_quick << " sec" << "\n";
		std::cout << "Il tempo medio di std::sort è " << time_std << " sec" << "\n";
		std::cout << "Il tempo medio di Quick-sort modificato è " << time_modified << " sec" << "\n";
		std::cout << "--------------------------------------------------------" << "\n";
	}
	
	/*
	Si nota che tra gli algoritmi che hanno complessità in tempo O(n^2), il più veloce è quasi sempre insertionsort, 
	mentre tra quelli con complessità in tempo O(nlogn) il più veloce è quicksort.
	Si nota inoltre che la compilazione in modo Debug e in modo Release influisce sui risultati, infatti:
		- in Debug abbiamo che il quicksort supera l'insertionsort in maniera regolare dalle dimensioni 50-60 in poi;
		- In Release invece l'insertionsort viene superato solo intorno alle dimensioni 210-220(motivo per cui ho messo 
		  le dimensioni di 10 in 10 fino a 300).
	Prendo per buona la la soglia del Release e introduco il modified_quicksort per confrontare con i tempi degli altri algoritmi.
	*/
	
	return 0;
}