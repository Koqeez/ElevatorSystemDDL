#ifndef ZAPYTANIA_H
#define ZAPYTANIA_H

#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//----------------------------------------------------------------------------------
//extern int minFloor;
//extern int maxFloor;
//extern int Floors;
//extern int GlobalID;
//----------------------------------------------------------------------------------

class Zapytanie {
public:
	int ID;
	int MiejsceP;
	int MiejsceD;
	//int CzasO; // Czas Oczekiwania na przysz³oœæ;
	//int CzasP; // Czas Podró¿y na przysz³oœæ
	bool IsInCar = false;



	Zapytanie();  // Konstruktor to rêcznego tworzenia zapytañ w menu. Przeka¿ jakiœ obojêtny argument.
	Zapytanie(int x , int y);

	int getMiejsceP() const;
	int getMiejsceD() const;
	int getID() const;
};

void fillEnquiryVector(std::vector<Zapytanie>&);
void printVector(const std::vector<Zapytanie>&);
void addEnquiry(std::vector<Zapytanie>&);
void eraseEnquiryByIndex(std::vector<Zapytanie>&, int);

#endif // !ZAPYTANIA_H