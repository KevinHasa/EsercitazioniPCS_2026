#include <iostream>

int main()
{
        static const int N = 10;
        double arr[N] = {70.0, 13.72, 1.05, 25.68, 17.32, 68.4, 42.3, 67.69, 105.6, 102.6};

	/* Riordino l'array */
        for (int cicli = 0; cicli < (N+1); cicli++) { 
/* CosÃ¬ mi assicuro che si ripeta N volte il ciclo for in modo che per esempio un elemento all'inizio dell'array abbia modo di arrivare alla fine (anche se non Ã un metodo ottimizzato)*/
                for (int i = 0; i < N-1; i++) {

                        if (arr[i] > arr[i+1]) {
                                double t = arr[i];
                                arr[i] = arr[i+1];
                                arr[i+1] = t;
                        }

                        continue;
                }
        }
	
	/* Ora stampo l'array riordinato */
	std::cout << "L'array riordinato ora è {";
	for (int i = 0; i < N; i++) {
		if (i == N-1) {
			std::cout << arr[i] << "}" << "\n";
		}

		std::cout << arr[i] << ",";
	}
}
