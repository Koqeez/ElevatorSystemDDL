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
	int CzasO; // Czas Oczekiwania na przysz�o��;
	int CzasP; // Czas Podr�y na przysz�o��
	bool IsInCar = false;
	Zapytanie(bool m);  // Konstruktor to r�cznego tworzenia zapyta� w menu. Przeka� jaki� oboj�tny argument.
	Zapytanie(int x, int y);
};