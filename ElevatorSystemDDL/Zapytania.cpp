#include "Zapytania.h"

using namespace std;
//----------------------------------------------------------------------------------
int MinPietro = 0;
int MaxPietro = 9;
int IloscPieter = 10;
int GlobalID = 0;
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
Zapytanie::Zapytanie(int x, int y) {
	if (x == y) {
		if (x == MaxPietro) {
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

void fillEnquiryVector(std::vector<Zapytanie>& newEnquiryVector) {
	int temp;
	cout << "Podaj ilosc zapytan: ";
	cin >> temp;	
	for (int i = 0; i < temp; i++) {
		Zapytanie Enquiry(rand() % IloscPieter, rand() % IloscPieter);
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
	Zapytanie Enquiry;
	newEnquiryVector.push_back(Enquiry);
}
/*
vector<Zapytanie> gerenateEnquiry(int amount_a) {
	vector<Zapytanie> Enquiries(amount_a);
	for (int i = 0; i < amount_a; i++) {
		Zapytanie(rand() % IloscPieter, rand() % IloscPieter);
	}
	return Enquiries;
}*/