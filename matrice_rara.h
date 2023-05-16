#pragma once

#include <iostream>
#include <vector>

class matrice_rara
{
private:
	struct date;

	std::vector<date> element;

	int nrLinii, nrColoane;
	int maximVal, minimVal;

public:
	struct date { int linie, coloana, val;};

	matrice_rara();

	matrice_rara(matrice_rara& copy);

	~matrice_rara();

	inline int nr_linii() { return this->nrLinii; };
	inline int nr_coloane() { return this->nrColoane;  };
	int maxim();
	int minim();
	int find_element(int Linie, int Coloana);
	int find_min();
	int find_max();

	friend std::istream& operator>>(std::istream& in, matrice_rara& unde);
	friend std::ostream& operator<<(std::ostream& out, matrice_rara& unde);
	
	matrice_rara operator+(const matrice_rara& mat) ;
	void operator+=(matrice_rara& mat);
	};

