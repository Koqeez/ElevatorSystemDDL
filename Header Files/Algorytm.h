#pragma once
#ifndef ALGORYTM_H
#define ALGORYTM_H

#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Zapytania.h"
#include "DataManagement.h"
#include <algorithm>
#include <fstream>
#include <string>

// ZMIANA ZAMYS£U NA JEDN¥ D£UG¥ WEKTOR ZAMIAST 2 Wymiarowej mapy
// ZMIENNE GLOBALNE

class Osobnik { // Zbiór wszystkich osobników zostanie zapisany jako vector
public:
	std::vector<int> DNA;
	double Fitness= 0;  // Im mniejszy fitness tym lepszy 
	int MovesAmount = 10000000;
	int CurrentFloor=0;
	void GenerateRandomDNA();
	void Mutate();
	void IsDone(int index);

	std::vector<int> getDNA();
};

#endif

extern Osobnik BestOsobnik;
extern Osobnik BestOsobnik2;
void PrintRandomDNAForPopulation(int);
void CrossoverView(std::vector<Zapytanie>,std::vector<int>&);
void AlgorithmConfiguration();
int  AlgorithmPopulationSize();
void AlgorithmObliczania(std::vector<Zapytanie>, std::vector<int>&, int);
void FitnessSimulationWithElevator(Osobnik&, std::vector<Zapytanie>, int);
std::vector<int> TranslateDNA(Osobnik);
void ClearData();
void SymulationFromFile(std::vector<Zapytanie> , std::vector<int>& , int);