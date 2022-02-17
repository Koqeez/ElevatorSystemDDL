#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class Zapytanie {
public:
	int ID;
	int MiejsceP;
	int MiejsceD;
	int CzasO; // Czas Oczekiwania na przysz³oœæ;
	int CzasP; // Czas Podró¿y na przysz³oœæ
	bool IsInCar = false;
	Zapytanie(bool m);  // Konstruktor to rêcznego tworzenia zapytañ w menu. Przeka¿ jakiœ obojêtny argument.
	Zapytanie(int x, int y);
};