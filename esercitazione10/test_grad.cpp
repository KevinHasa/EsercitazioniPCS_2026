#include "gradiente_coniugato.hpp"
#include<iostream>

using namespace Eigen;

int main() 
{
	const double tol = 1e-13;

	for (size_t n = 2; n < 51; n++) {
		
		MatrixXd B = MatrixXd::Random(n,n);
		MatrixXd A = B.transpose()*B; // Creo una matrice simmetrica def. positiva
		VectorXd x_true = VectorXd::Random(n);
		VectorXd b = A*x_true;
		
		VectorXd x_grad = grad_coniugato(A, b);
		VectorXd r = b - A*x_grad;
			if (r.norm() > tol) {
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}