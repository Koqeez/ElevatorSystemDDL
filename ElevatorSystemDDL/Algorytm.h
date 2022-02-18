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
const int MutationRate = 100; // Cz�stotliwo�� mutacji im wi�ksza tym mniejsza szansa na mutacje
const int PopulationStartSize = 100; // Wielko�� pocz�tkowa populacji
int PopulationSize = 0; // Obecna wielko�� populacji

int GenerationCounter = 0; // Liczy ilo�� generacji
int FloorMoveTime = 5; // Wyra�ony w sekundach czas podr�y mi�dzy jednym pi�trem
int FloorWaitTime = 2; // Wyra�ony w sekundach czas otwarcia i oczekiwania windy na pi�trze
int ZapytanieCounter;  // Zmienna przedstawiaj�ca ile zosta�o jeszcze zapyta�

class Osobnik { // Zbi�r wszystkich osobnik�w zostanie zapisany jako vector
public:
	int DNA[DNALength];
	int Fitness = 0;  // Im mniejszy fitness tym lepszy 
	void GenerateRandomDNA();
	void Mutate();
	bool IsDone(int index);
};