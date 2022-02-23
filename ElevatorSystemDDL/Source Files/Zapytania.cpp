#include "Zapytania.h"
#include "Floor.h"
#include "Algorytm.h"

using namespace std;
//----------------------------------------------------------------------------------
extern int minFloor;
extern int maxFloor;
extern int Floors;
extern int GlobalID = 0;
//extern int DNALength;
//----------------------------------------------------------------------------------
Zapytanie::Zapytanie() {
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

Zapytanie::Zapytanie(int x) {

}


Zapytanie::Zapytanie(int x, int y) {
	if (x == y) {
		if (x == maxFloor) {
			y--;
		}
		else y++;
	}
	MiejsceP = x;
	MiejsceD = y;
	ID = GlobalID;
	GlobalID++;
}
int Zapytanie::getID() const{
	return ID;
}
int Zapytanie::getMiejsceD() const {
	return MiejsceD;
}
int Zapytanie::getMiejsceP() const {
	return MiejsceP;
}

void Zapytanie::setMiejsceP(const int number) {
	this->MiejsceP = number;	
}
void Zapytanie::setMiejsceD(const int number) {
	this->MiejsceD = number;
}
void Zapytanie::setID(const int number) {
	this->ID = number;
}

void fillEnquiryVector(std::vector<Zapytanie>& newEnquiryVector) {	
	if (floorZeroCheck(Floors)) {
		return;
	}
	int temp;
	cout << "Podaj ilosc zapytan: ";
	cin >> temp;	
	for (int i = 0; i < temp; i++) {
		Zapytanie Enquiry(rand() % Floors, rand() % Floors);
		newEnquiryVector.push_back(Enquiry);
	}
}
void printVector(const std::vector<Zapytanie>& newEnquiryVector) {
	unsigned int size = newEnquiryVector.size();
	if (size == 0) {
		cout << "Brak zapytan" << endl;
		return;
	}
	for (unsigned int i = 0; i < size; i++) {
		cout << "Zapytanie nr: " << i << ", o ID: " << newEnquiryVector[i].getID() << endl;
		cout << "Miejsce poczatkowe: " << newEnquiryVector[i].getMiejsceP() << " -> Miejsce koncowe: " << newEnquiryVector[i].getMiejsceD() << endl;
	}
}
void addEnquiry(std::vector<Zapytanie>& newEnquiryVector) {
	if (floorZeroCheck(Floors)) {
		return;
	}
	Zapytanie Enquiry;
	newEnquiryVector.push_back(Enquiry);
}
void eraseEnquiryByIndex(std::vector<Zapytanie>& newEnquiryVector, int enquiryIndex_a) {
	if (enquiryIndex_a < newEnquiryVector.size() && enquiryIndex_a >= 0) {
		newEnquiryVector.erase(newEnquiryVector.begin() + enquiryIndex_a);
		std::cout << "Zapytanie zostalo usuniete" << std::endl;
	}
	else {
		std::cout << "Zly index. Zapytanie nie zostalo usuniete" << std::endl;
	}
}
/*
vector<Zapytanie> gerenateEnquiry(int amount_a) {
	vector<Zapytanie> Enquiries(amount_a);
	for (int i = 0; i < amount_a; i++) {
		Zapytanie(rand() % IloscPieter, rand() % IloscPieter);
	}
	return Enquiries;
}*/