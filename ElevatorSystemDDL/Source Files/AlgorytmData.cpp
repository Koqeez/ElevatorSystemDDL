#include "AlgorytmData.h"
extern int DNALength;
void transferDNAToFile(std::vector<Osobnik> vec, std::string fileName);
void generateDNAToFile(int amount, std::string fileName) { // Przekazujesz iloœæ Osobników dla ilu ma byæ wygenerowane DNA(amount) fileName to nazwa pliku jaki ma byæ utworzony, albo append do jakiego.
	std::vector<Osobnik> x(amount);
	for (int i = 0; i < amount; i++) {
		x[i].GenerateRandomDNA();
	}
	transferDNAToFile(x,fileName);
}
void transferDNAToFile(std::vector<Osobnik> vec, std::string fileName) {
	std::fstream MyFile;
	MyFile.open(fileName, std::ios::app);
	if (MyFile.is_open()) {
		MyFile << DNALength << std::endl;
		MyFile << vec.size() << std::endl;
		for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < DNALength; j++) {
				MyFile << vec[i].DNA[j];
			}
			MyFile << std::endl;
		}
		MyFile.close();
		std::cout << "Wygenerowano i dodano dane" << std::endl;
	}
	else std::cout << "Nie udalo sie wykonac polecenia" << std::endl;
}
void deleteFile(std::string text) { // Funkcja do usuwania pliku, nale¿y przekazaæ nazwê i rozszerzenie
	if (std::remove(text.c_str())!=0) {
		std::cout << "Nie usunieto lub taki plik juz nie istnial \n";
	}
	else {
		std::cout << "Usunieto pomyslnie \n";
	}
}
std::vector<Osobnik> readDNAFromFile(std::string fileName, int amount) { // Nale¿y przekazaæ nazwê pliku oraz iloœæ osobników dla ilu ma byæ pobrane DNA. D³ugoœæ DNA pobierana jest z DNALength
	std::vector<Osobnik> x;
	std::fstream MyFile;
	MyFile.open(fileName, std::ios::in);
	if (MyFile.is_open()) {
		std::string temp;
		getline(MyFile, temp);
		int maxDNALength = atoi(temp.c_str());
		getline(MyFile, temp);
		int maxAmount = atoi(temp.c_str());
		if (amount > maxAmount) {
			std::cout << "W pliku jest zbyt malo danych aby pobrac taka ilosc DNA osobnikow";
		}
		else if (DNALength > maxDNALength) {
			std::cout << "W pliku DNA jest zbyt krotkie zeby pobrac taka dlugosc";
		}
		else {

		}
		MyFile.close();
	}
	return x;
}
void algorythmDataTest() {
	readDNAFromFile("DNASample.csv", 1);
	// deleteFile("DNASample.csv");
}
// Pierwsze dwie linijki w wygenerowanym pliku to w kolejnoœci d³ugoœæ wygenerowanego DNA a nastêpnie iloœæ wygenerowanych.