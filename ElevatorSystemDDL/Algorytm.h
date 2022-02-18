#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Zapytania.h"
#include <algorithm>

// ZMIANA ZAMYS£U NA JEDN¥ D£UG¥ WEKTOR ZAMIAST 2 Wymiarowej mapy
// ZMIENNE GLOBALNE
const int DNALength = 200;  // Sta³a d³ugoœæ ³añcucha DNA

extern const int MutationRate; // Czêstotliwoœæ mutacji im wiêksza tym mniejsza szansa na mutacje
extern const int PopulationStartSize; // Wielkoœæ pocz¹tkowa populacji
extern int PopulationSize; // Obecna wielkoœæ populacji
extern int FloorMoveTime;// Wyra¿ony w sekundach czas podró¿y miêdzy jednym piêtrem
extern int FloorWaitTime; // Wyra¿ony w sekundach czas otwarcia i oczekiwania windy na piêtrze
extern int ZapytanieCounter;  // Zmienna przedstawiaj¹ca ile zosta³o jeszcze zapytañ

class Osobnik { // Zbiór wszystkich osobników zostanie zapisany jako vector
public:
	int DNA[DNALength];
	int Fitness=10000;  // Im mniejszy fitness tym lepszy 
	int CurrentFloor=0;
	void GenerateRandomDNA();
	void Mutate();
	bool IsDone(int index);
};
extern Osobnik BestOsobnik;
void CrossoverView();
std::vector<int> TranslateDNA(Osobnik);