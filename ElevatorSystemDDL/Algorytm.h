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
const int MutationRate = 100; // Czêstotliwoœæ mutacji im wiêksza tym mniejsza szansa na mutacje
const int PopulationStartSize = 100; // Wielkoœæ pocz¹tkowa populacji
int PopulationSize = 0; // Obecna wielkoœæ populacji

int GenerationCounter = 0; // Liczy iloœæ generacji
int FloorMoveTime = 5; // Wyra¿ony w sekundach czas podró¿y miêdzy jednym piêtrem
int FloorWaitTime = 2; // Wyra¿ony w sekundach czas otwarcia i oczekiwania windy na piêtrze
int ZapytanieCounter;  // Zmienna przedstawiaj¹ca ile zosta³o jeszcze zapytañ

class Osobnik { // Zbiór wszystkich osobników zostanie zapisany jako vector
public:
	int DNA[DNALength];
	int Fitness = 0;  // Im mniejszy fitness tym lepszy 
	void GenerateRandomDNA();
	void Mutate();
	bool IsDone(int index);
};