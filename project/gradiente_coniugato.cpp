#include <Eigen/Dense>
#include <iostream>

Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, const double res_tol = 1.0e-12, const unsigned int it_max = 10000) {
	
	Eigen::VectorXd x = x0;
	Eigen::VectorXd res = b - A * x;
	Eigen::VectorXd p = res;
	
	double res_norm_0 = res.norm();
	unsigned int it = 0;
	
	while (it < it_max && res.norm() > res_tol * res_norm_0) {
		const double alpha_k = ((p.transpose() * res) / (p.transpose() * A * p)).value();
		x = x + alpha_k * p;
		Eigen::VectorXd res_next = b - A * x;
		const double beta_k = ((p.transpose() * A * res_next) / (p.transpose() * A * p)).value();
		p = res_next - beta_k * p;
		res = res_next;
		it++;
	}
	
	std::cout << "Gradiente coniugato - iterazioni effettuate: " << it << std::endl;
	std::cout << "Gradiente coniugato - Norma residuo: " << res.norm() << std::endl;
	return x;
}
