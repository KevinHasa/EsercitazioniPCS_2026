#pragma once
#include <iostream>
#include <concepts>

template<typename I> requires std::integral<I>
class rational
{
	I num_;
	I den_;
	
public:

	/* Costruttore di default */
	rational()
	: num_(I{0}), den_(I{1})
		{}
		
	/* Costruttore user-defined */
	rational(const I& pnum, const I& pden)
	: num_(pnum), den_(pden)
	{}
	
	/* Definisco NaN e Inf */
	bool NaN() const {
	return (den_ == 0 && num_ == 0);
	}
	
	bool Inf() const {
		return (den_ == 0 && num_ != 0);
	}
	
	/* Restituisco i valori del numeratore e denominatore */
	I num() const { 
		
		/* Definisco il massimo comune divisore */
		if (den_ != 0) {
			int a = abs(num_);
			int b = abs(den_);
			int mcd = 0;
			if (a > b) {
					
				while (b > 0) {
					int r = a%b;
					a = b;
					b = r;
				}
				mcd = a;
			}	
					
			else {
						
				while (a > 0) {
					int r = b%a;
					b = a;
					a = r;
				}
				
				mcd = b;
			}	
			
			int num = num_ / mcd;
			int den = den_ / mcd;
			
			return num;
		}
		
		else {
			return num_;
		}
	} 
	
	I den() const {
		
		/* Definisco il massimo comune divisore */
		if (den_ != 0) {
			int a = abs(num_);
			int b = abs(den_);
			int mcd = 0;
			if (a > b) {
					
				while (b > 0) {
					int r = a%b;
					a = b;
					b = r;
				}
				mcd = a;
			}	
					
			else {
						
				while (a > 0) {
					int r = b%a;
					b = a;
					a = r;
				}
				
				mcd = b;
			}	
			
			int num = num_ / mcd;
			int den = den_ / mcd;
			
			return den;
		}
		
		else {
			return den_; 
		}
	}
	
	/* Implementazione canonica dell'incremento */
	rational& operator+=(const rational& other) {
		num_ += other.num_ * den_ + num_ * (other.den_ -1)  ; /* Nell'incremento devo sommare l'altro numeratore per il denominatore e il numeratore per l'altro denominatore, quindi devo togliere il numeratore iniziale */
		den_ *= other.den_;
		return *this;
	}
	
	/* Implementazione canonica della somma */
	rational operator+(const rational& other) const {
		rational ret = *this;
		ret += other;
		return ret;
	}
	
	/* Implementazione canonica del decremento */
	rational& operator-=(const rational& other) {
		num_ -= other.num_ * den_ - num_ * (other.den_ - 1); /* Nel decremento devo sottrarre l'altro numeratore per il denominatore e il numeratore per l'altro denominatore, quindi devo togliere il numeratore iniziale */
		den_ *= other.den_;
		return *this;
	}
	
	/* Implementazione canonica della differenza */
	rational operator-(const rational& other) const {
		rational ret = *this;
		ret -= other;
		return ret;
	}
	
	/* Allo stesso modo implemento prodotto */
	rational operator*=(const rational& other) {
		num_ *= other.num_ ;
		den_ *= other.den_;
		return *this;
	}
	
	rational operator*(const rational& other) const {
		rational ret = *this;
		ret *= other;
		return ret;
	}
	/* E divisione  */
	rational operator/=(const rational& other) {
		num_ *= other.den_ ;
		den_ *= other.num_ ;
		return *this;
	}
	
	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
		return ret;
	}
	
};

template<typename I> requires std::integral<I>
std::ostream& 
operator<<(std::ostream& os, const rational<I>& r)
{
	if (r.den() == 0) {
		if (r.num() == 0) {
			os << "NaN";
		}
		
		else if (r.num() > 0) {
			os << "+Inf";
		}
		else {
			os << "-Inf";
		}
	}
	
	else if (abs(r.den()) == 1)  {
		if (r.den() == 1) {
			os << r.num();
		}
		
		else {
			os << -r.num();
		}
	}
	
	else {
		if (r.num()>0 && r.den()<0) {
			os << "-" << r.num() << "/" << -r.den();
		}
	
		else if (r.num()<0 && r.den()<0) {
			os << -r.num() << "/" << -r.den();
		}
	
		else {
			os << r.num() << "/" << r.den();
		}
	}
	
	return os;
}
