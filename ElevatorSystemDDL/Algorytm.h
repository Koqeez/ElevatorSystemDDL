#pragma once
#ifndef ALGORYTM_H
#define ALGORYTM_H

#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Zapytania.h"
#include <algorithm>

// ZMIANA ZAMYS£U NA JEDN¥ D£UG¥ WEKTOR ZAMIAST 2 Wymiarowej mapy
// ZMIENNE GLOBALNE
const int DNALength = 300;  // Sta³a d³ugoœæ ³añcucha DNA

extern const int MutationRate; // Czêstotliwoœæ mutacji im wiêksza tym mniejsza szansa na mutacje
extern const int PopulationStartSize; // Wielkoœæ pocz¹tkowa populacji
extern int PopulationSize; // Obecna wielkoœæ populacji

class Osobnik { // Zbiór wszystkich osobników zostanie zapisany jako vector
public:
	int DNA[DNALength];
	int Fitness=10000;  // Im mniejszy fitness tym lepszy 
	int CurrentFloor=0;
	void GenerateRandomDNA();
	void Mutate();
	void IsDone(int index);
};

#endif

extern Osobnik BestOsobnik;
void CrossoverView(std::vector<Zapytanie>,std::vector<int>&);
void Testowa();
std::vector<int> TranslateDNA(Osobnik);