#include <iostream>
#include <cmath>

int main()
{
	static const int N = 10;
	double arr[N] = {122.5, 13.72, 1.05, 25.68, 17.32, 68.4, 42.3, 67.69, 105.6, 0.5};

/* Riordino l'array (riscrivendo l'algoritmo bubblesort che ho provato aimplementare nell'altro file) e richiamo il primo e l'ultimo elemento rispettivamente come minimo e massimo dell'array*/

	for (int cicli = 0; cicli < (N+1); cicli++) {
		for (int i = 0; i < N; i++) {
			if (arr[i] > arr[i+1]) {
				double t = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = t;	
			}

			continue;
		}
	}
	
	std::cout << "Il minimo dell'array è " << arr[0] << "\n";
	std::cout << "Il massimo dell'array è " << arr[N-1] << "\n";
	
/* Ora calcolo la media e la deviazione standard*/

	double sum = 0;
	for (int i = 0; i < N; i++) {
		sum += arr[i];
	}
	double media = sum/N;

	double var = 0;

	for (int i = 0; i < N; i++) {
		var += ((arr[i] - media)*(arr[i] - media))/N;
	}

	std::cout << "La media è " << media << "\n";
	std::cout << "La deviazione standard è "<< std::sqrt(var) << "\n";

	return 0;
}
