#include "matrice_rara.h"
#define o0 out<<0<<' '

matrice_rara::matrice_rara() 
	: nrLinii(0), nrColoane(0), element({}) {

}

matrice_rara::matrice_rara(matrice_rara& copy) {
	this->element = copy.element;
	this->nrColoane = copy.nrColoane;
	this->nrLinii = copy.nrLinii;
}

matrice_rara::~matrice_rara() {
	std::cout << "Matrice stearsa\n";
	delete &this->element;
}

int matrice_rara::maxim() {
	return this->maximVal;
}
int matrice_rara::minim() {
	return this->minimVal;
}

int matrice_rara::find_element(int Linie, int Coloana) {
	int primul, ultimul;
	int left = 0, right = this->element.size() - 1, mid = 0;
	bool ok = 0;

	while (!ok && left != right) {
		if (this->element[right].linie < Linie || left > right) {
			ok = 1;
			break;
		}

		mid = (left + right) / 2;
		//std::cout << left << " " << right << ' ' << mid << ' ' << this->element[mid].val << "\n";

		if (this->element[mid].linie >= Linie) {
			right = mid;
			if (this->element[mid].linie == Linie)
				primul = mid;
		}
		else {
			left  = mid + 1;
		}

	}
	if (this->element[primul].linie != Linie)
		return 0;
	
	if (Linie > nrLinii || Linie < 0 || Coloana > nrColoane || Coloana < 0)
		return 0;

	left = primul, right = this->element.size() - 1, mid = 0;
	ok = 0;
	while (!ok && left != right) {
		if (this->element[right].linie < Linie || left > right) {
			ok = 1;
			break;
		}

		mid = (left + right) / 2;
		//std::cout << left << " " << right << ' ' << mid << ' ' << this->element[mid].val << "\n";

		if (this->element[mid].linie <= Linie) {
			left = mid + 1;
			if (this->element[mid].linie == Linie)
				ultimul = mid;
		}
		else {
			right = mid;
		}
	}

	left = primul, right = ultimul;

	if (this->element[left].coloana == Coloana)
		return this->element[left].val;

	while (left <= right) {
		mid = (left + right) / 2;

		if (this->element[mid].coloana == Coloana)
			return this->element[mid].val;
		
		if (this->element[mid].coloana > Coloana)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return 0;
}

int matrice_rara::find_min()
{
	int min = INT32_MAX;
	for (auto x : element)
	{
		if (x.val < min)
			min = x.val;
	}
	return min;
}

int matrice_rara::find_max()
{
	int _max = 0;
	for (auto x : element)
	{
		if (x.val > _max)
			_max = x.val;
	}
	return _max;
}

matrice_rara matrice_rara::operator+(const matrice_rara& mat) {
	matrice_rara ret;
	ret.nrColoane = nrColoane;
	ret.nrLinii = nrLinii;
	int aux1 = 0, aux2 = 0;

	while (aux1 != element.size() && aux2 != mat.element.size()) {
		if (element[aux1].linie < mat.element[aux2].linie) {
			ret.element.push_back(element[aux1++]);
		}
		else if (element[aux1].linie == mat.element[aux2].linie) {
			if (element[aux1].coloana < mat.element[aux2].coloana)
				ret.element.push_back(element[aux1++]);
			else if (element[aux1].coloana == mat.element[aux2].coloana) {
				date _n = { element[aux1].linie, element[aux1].coloana, element[aux1].val + mat.element[aux2].val };
				ret.element.push_back(_n);
				aux1++;
				aux2++;
			}
			else {
				ret.element.push_back(mat.element[aux2++]);
			}
		}
		else {
			ret.element.push_back(mat.element[aux2++]);
		}
	}
	while (aux1 != element.size()) {
		ret.element.push_back(element[aux1++]);
	}
	while (aux2 != mat.element.size()) {
		ret.element.push_back(mat.element[aux2++]);
	}

	ret.minimVal = ret.find_min();
	ret.maximVal = ret.find_max();

	return ret;
}

void matrice_rara::operator+=(matrice_rara& mat) {
	matrice_rara noua;
	
	noua.nrColoane = nrColoane;
	noua.nrLinii = nrLinii;

	int i = 0, j = 0;
	while (i < this->element.size() && j < mat.element.size())
	{
		if (element[i].linie < mat.element[j].linie)
			noua.element.push_back(element[i++]);
		else if (element[i].linie == mat.element[j].linie)
		{
			if (element[i].coloana < mat.element[j].coloana)
				noua.element.push_back(element[i++]);
			else if (element[i].coloana == mat.element[j].coloana)
			{
				date ceva = { element[i].linie, element[i].coloana, element[i].val + mat.element[j].val };
				noua.element.push_back(ceva);
				i++;
				j++;
			}
			else
				noua.element.push_back(mat.element[j++]);
		}
		else {
			noua.element.push_back(mat.element[j++]);
		}
	}

	while (i != element.size()) {
		noua.element.push_back(element[i++]);
	}
	while (j != mat.element.size()) {
		noua.element.push_back(mat.element[j++]);
	}
	element = noua.element;
	maximVal = noua.find_max();
	minimVal = noua.find_min();

}

std::istream& operator >>(std::istream& in, matrice_rara& unde)
{
	int a, b, c, n;
	if(&in == &std::cin)
		std::cout << "Introdu nr linii, nr coloane si cate elemente diferite de 0 sa aiba matricea: ";
	in >> unde.nrLinii >> unde.nrColoane >> n;
	if (&in == &std::cin) std::cout << '\n';
	for (int i = 1; i <= n; i++) {
		if (&in == &std::cin)
			std::cout << "Introdu linia, coloana si valoarea: ";
		in >> a >> b >> c;
		unde.element.push_back({ a, b, c });
		if (&in == &std::cin) std::cout << '\n';
	}

	unde.maximVal = unde.find_max();
	unde.minimVal = unde.find_min();
	
	return in;
}

std::ostream& operator <<(std::ostream& out, matrice_rara& unde) {
	//std::cout << unde.element.size() << '\n';

	int ind = 0, linCur = 1, colCur = 0;
	
	while (ind < unde.element.size()) {
		if (unde.element[ind].linie == linCur) {
			for (int i = colCur + 1; i < unde.element[ind].coloana; i++)
				o0, colCur++;
		}
		else {
			for (int i = colCur; i < unde.nrColoane; i++)
				o0;
			out << '\n';

			for (int i = linCur + 1; i <= unde.element[ind].linie - 1; i++, out << '\n') {
				for (int j = 0; j < unde.nrColoane; j++)
					o0;
			}

			for (int i = 1; i <= unde.element[ind].coloana - 1; i++)
				o0;
			colCur = unde.element[ind].coloana - 1;
			linCur = unde.element[ind].linie;
		}
		out << unde.element[ind].val << ' ';
		colCur++;
		ind++;
	}

	for (int i = colCur; i < unde.nrColoane; i++)
		o0;
	out << '\n';

	for (int i = linCur; i < unde.nrLinii; i++) {
		for (int j = 0; j < unde.nrColoane; j++)
			o0;
		std::cout << '\n';
	}

	return out;
}