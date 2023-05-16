#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "matrice_rara.h"

using namespace std;

ifstream fin;

void meniu() {
	std::cout << "Alege o optiune:\n"
		"1. Citeste o matrice rara noua\n"
		"2. Maximul din matrice\n"
		"3. Minimul din matrice\n"
		"4. Elementul de pe linia L coloana C\n"
		"5. Aduna matricea existenta cu alta matrice\n"
		"6. Afisare matrice\n"
		"7. Iesire\n"
		"8. Clear screen\n"
		"Scrie numarul optiunii (1 - 8) : ";
}

int main() {
	
	matrice_rara matrice;
	matrice_rara matsec;
	matrice_rara suma;
	string sname;
	int option;
	int opf = 0;

	do {
		meniu();
		cin >> option;
		cout << '\n';

		if (option != 1 && option != 7 && option != 8 && matrice.nr_linii() == 0)
			std::cout << "Nicio matrice memorata\n";
		else {
			switch (option) {
			case 1:
				matrice = matrice_rara();
				std::cout << "Variante\n1. Citire de la tastatura\n2. Citire din fisier\nAlege optiunea: ";
				cin >> opf;
				if (opf == 1)
					cin >> matrice;
				else {
					cout << "Introdu numele fisierului: ";
					cin >> sname;
					fin.open(sname);
					fin >> matrice;
					fin.close();
					if(matrice.nr_linii() != 0)
						std::cout << "Matrice citita cu succes\n";
				}
				break;
			case 2:
				std::cout << "Maximul din matrice este " << matrice.maxim();
				break;
			case 3:
				std::cout << "Minimul din matrice este " << matrice.minim();
				break;
			case 4:
				int L, C;
				std::cout << "Introdu linia: ";
				cin >> L;
				std::cout << "Introdu coloana: ";
				cin >> C;
				std::cout << "Elementul de pe linia " << L << "coloana " << C << "este " << matrice.find_element(L, C);
				break;
			case 5:
				cin >> matsec;
				suma = matsec + matrice;
				std::cout << suma;
				break;
			case 6:
				std::cout << matrice;
				break;
			case 8:
				system("cls");
				break;
			}
		}
		std::cout << '\n';

	} while (option != 7);
}