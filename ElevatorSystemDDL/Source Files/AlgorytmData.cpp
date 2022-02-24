#include "AlgorytmData.h"

// IMPORTANT - je¿eli jako argument wpiszesz "er" to domyœlnie zostanie to zamienione na "DNASample.csv" jest to forma skrótu do testów
extern int DNALength;
void transferDNAToFile(std::vector<Osobnik> vec, std::string fileName);
void generateDNAToFile(int amount, std::string fileName) { // Przekazujesz iloœæ Osobników dla ilu ma byæ wygenerowane DNA(amount) fileName to nazwa pliku jaki ma byæ utworzony, albo append do jakiego.
	std::vector<Osobnik> x(amount);
	for (int i = 0; i < amount; i++) {
		x[i].GenerateRandomDNA();
	}
	transferDNAToFile(x,fileName);
}
void transferDNAToFile(std::vector<Osobnik> vec, std::string fileName) { // Nie wywo³uj tej funkcji samej. Wywo³aj generateDNAToFile. 
	// Funkcja jest stworzona tak ¿e je¿eli istnieje ju¿ plik z danymi o takiej samej nazwie to usuwa jego zawartoœci i generuje nowe DNA
	// Pierwsze dwie linijki w wygenerowanym pliku to w kolejnoœci d³ugoœæ wygenerowanego DNA a nastêpnie iloœæ wygenerowanych.
	std::fstream MyFile;  
	if (fileName == "er") {
		fileName = "DNASample.csv";
	}
	MyFile.open(fileName, std::ios::out);
	if (MyFile.is_open()) {
		MyFile << DNALength << std::endl;
		MyFile << vec.size() << std::endl;
		for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < DNALength; j++) {
				MyFile << vec[i].DNA[j];
			}
			if (i == vec.size() - 1);
			else MyFile << std::endl;
		}
		MyFile.close();
		std::cout << "Wygenerowano i dodano dane" << std::endl;
	}
	else std::cout << "Nie udalo sie wykonac polecenia" << std::endl;
}
void deleteFile(std::string fileName) { // Funkcja do usuwania pliku, nale¿y przekazaæ nazwê i rozszerzenie
	if (fileName == "er") {
		fileName = "DNASample.csv";
	}
	if (std::remove(fileName.c_str())!=0) {
		std::cout << "Nie usunieto lub taki plik juz nie istnial \n";
	}
	else {
		std::cout << "Usunieto pomyslnie \n";
	}
}
std::vector<Osobnik> readDNAFromFile(int amount, std::string fileName) { // Nale¿y przekazaæ nazwê pliku oraz iloœæ osobników dla ilu ma byæ pobrane DNA. D³ugoœæ DNA pobierana jest z DNALength
	std::vector<Osobnik> x;  // Funckja zwróci vektor o odpowiedniej d³ugoœci(amount) i DNALenght takim jak w algorytm.cpp
	std::fstream MyFile;
	if (fileName == "er") {
		fileName = "DNASample.csv";
	}
	MyFile.open(fileName, std::ios::in);
	if (MyFile.is_open()) {
		std::string temp;
		getline(MyFile, temp);
		int maxDNALength = atoi(temp.c_str());
		getline(MyFile, temp);
		int maxAmount = atoi(temp.c_str());
		std::cout << maxDNALength << " " << maxAmount << std::endl;
		if (amount > maxAmount) {
			std::cout << "W pliku jest zbyt malo danych aby pobrac taka ilosc DNA osobnikow";
		}
		else if (DNALength > maxDNALength) {
			std::cout << "W pliku DNA jest zbyt krotkie zeby pobrac taka dlugosc";
		}
		else {
			for (int i = 0; i < 1; i++) {
				Osobnik p;
				getline(MyFile, temp);
				for (int j = 0; j < DNALength; j++) {
					p.DNA.push_back((temp[j]-48));
					std::cout << p.DNA[j] << " ";
				}
				x.push_back(p);
			}
		}
		MyFile.close();
	}
	return x;
}
void saveFitnessDataToFile(std::string fileName,int currGeneration, double currBestFitness, int currBestMovesAmount, double allTimeBestFitness, int allTimeBestMovesAmount,
	int DNAL, int popStartSize, int mutationChance,int genAmount, int maxFitness, int maxEnquiresInElevator,int enquiresAmount, int maxF, int minF, int fAmount) {

}
void algorythmDataTest() {
	generateDNAToFile(50, "er");
	//readDNAFromFile(10, "DNASample.csv");
	// deleteFile("DNASample.csv");
}