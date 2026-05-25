#pragma once

#include <Eigen/Eigen>

using namespace Eigen;

VectorXd grad_coniugato(const MatrixXd& A,const VectorXd& b) 
{
	size_t n = b.size(); // è la stessa della matrice A
	VectorXd x = VectorXd::Ones(n);
	VectorXd r = b - A*x;
	VectorXd p = r;
	double tol = 1e-13; //con tolleranze più piccole impiega troppo tempo per il test
	double normr = r.norm();
	
	while (normr > tol) {
		double alfa = ((p.transpose()*r)/(p.transpose()*A*p)).value();
		x += alfa*p;
		r = b - A*x;
		normr = r.norm();
		double beta = ((p.transpose()*A*r)/(p.transpose()*A*p)).value();
		p = r - beta*p;
	}
	return x;
}