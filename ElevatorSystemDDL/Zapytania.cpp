#include "Zapytania.h"
using namespace std;
int MinPietro = 0;
int MaxPietro = 9;
int IloscPieter = 10;
int GlobalID = 0;
Zapytanie::Zapytanie(bool m) {
	int x, y;
	cout << "Wpisz miejsce poczatkowe: " << endl;
	cin >> x;
	cout << "Wpisz miejsce docelowe: " << endl;
	cin >> y;
	while (x == y) {
		cout << "Miejsce docelowe nie moze byc takie samo jak poczatkowe" << endl << "Wpisz miejsce docelowe: " << endl;
		cin >> y;
	}
	MiejsceP = x;
	MiejsceD = y;
	ID = GlobalID;
	GlobalID++;
}
Zapytanie::Zapytanie(int x = 0, int y = 1) {
	if (x == y) {
		if (x == MaxPietro) {
			y--;
		}
		else y++;
	}
	MiejsceP = x;
	MiejsceD = y;
	ID = GlobalID;
	GlobalID++;
}
vector<Zapytanie> GenerateZapytanie(int n) {
	vector<Zapytanie> z(n);
	for (int i = 0; i < n; i++) {
		Zapytanie(rand() % IloscPieter, rand() % IloscPieter);
	}
	return z;
}