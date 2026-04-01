#include <iostream>
#include "rational.hpp"

int main(void)
{
	rational<int> r(7,4);
	rational<int> s(3,-9);

	std::cout << "Il razionale r è " << r << "\n";
	std::cout << "Il razionale s è " << s << "\n";
	std::cout << "Il numeratore di r è " << r.num() << "\n";
	std::cout << "Il denominatore di r è " << r.den() << "\n";
	std::cout << "Il numeratore di s è " << s.num() << "\n";
	std::cout << "Il denominatore di s è " << s.den() << "\n";
	std::cout << "La somma è " << r+s << "\n";
	std::cout << "La differenza è " << r-s << "\n";
	std::cout << "La moltiplicazione è " << r*s << "\n";
	std::cout << "La divisione è " << r/s << "\n";

	return 0;
}