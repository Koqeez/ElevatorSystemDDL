#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Zapytania.h"
#include <algorithm>

// ZMIANA ZAMYS�U NA JEDN� D�UG� WEKTOR ZAMIAST 2 Wymiarowej mapy
// ZMIENNE GLOBALNE
const int DNALength = 200;  // Sta�a d�ugo�� �a�cucha DNA

extern const int MutationRate; // Cz�stotliwo�� mutacji im wi�ksza tym mniejsza szansa na mutacje
extern const int PopulationStartSize; // Wielko�� pocz�tkowa populacji
extern int PopulationSize; // Obecna wielko�� populacji
extern int FloorMoveTime;// Wyra�ony w sekundach czas podr�y mi�dzy jednym pi�trem
extern int FloorWaitTime; // Wyra�ony w sekundach czas otwarcia i oczekiwania windy na pi�trze
extern int ZapytanieCounter;  // Zmienna przedstawiaj�ca ile zosta�o jeszcze zapyta�

class Osobnik { // Zbi�r wszystkich osobnik�w zostanie zapisany jako vector
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