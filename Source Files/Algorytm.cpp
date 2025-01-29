#include "Algorytm.h"
#include "GlobalVariables.h"
#include "PlatformUtils.h"  // Dodajemy dla ClearScreen i Sleep
#include <iomanip>  // Dodajemy dla std::setw
#include <iostream>
#include <vector>

int DNALength = 100;  // Zwiększamy długość DNA dla większej elastyczności
int GenerationAmount = 500;  // Więcej generacji dla lepszej optymalizacji
int MutationRate = 10; // Zwiększamy szansę mutacji (1/10)
int PopulationStartSize = 200; // Większa populacja dla lepszej różnorodności
int PopulationSize = 0; // Obecna wielkość populacji
int MaxZapytan = 10;
int FitnessScaleMax = 1;
int FitnessScaleMin = 0;
double PENALTY_WRONG_FLOOR = 0.3; // Kara za złe piętro

Osobnik BestOsobnik;
Osobnik BestOsobnik2;
void generateDNAToFile(int amount, std::string fileName);
void transferDNAToFile(std::vector<Osobnik> vec, std::string fileName);
void deleteFile(std::string fileName);
std::vector<Osobnik> readDNAFromFile(int amount, std::string fileName);
void saveAlgorithmDataToFile(std::string fileName, std::string enquiriesFileName, int currGeneration, Osobnik x, Osobnik Best, int DNAL, int popStartSize, int mutationChance, int genAmount,
	int minFitness, int maxFitness, int maxEnquiriesInElevator, int enquiriesAmount, int maxF, int minF, std::string addInfo);

void Osobnik::Mutate() { // Wykonuje mutacje o szansie określonej przez zmienną globalną
	for (int i = 0; i < DNALength; i++) {
		int r = rand() % MutationRate;
		if (r == 0) {
			if (DNA[i] == 0)DNA[i] = 1;
			else if (DNA[i] == 1)DNA[i] = 0;
			else DNA[i] = rand() % 2;
		}
	}
}
void Osobnik::IsDone(int index) {	//Funckja przypisuje Fitness
		// Należy przekazać aktualny index pętli w której wykonoywana jest symulacja i usuwanie zapytań.
	Fitness = index;
}
void Osobnik::GenerateRandomDNA() {
	for (int i = 0; i < DNALength; i++) {
		DNA.push_back(rand() % 2);
	}
}
std::vector<int> Osobnik::getDNA() {
	return DNA;
}
void PrintRandomDNAForPopulation(int PopulationStartSize_a) {
	int counter{ 0 };
	Osobnik* obj = new Osobnik; //Wyswietlenie przykladowego DNA
	for (int i = 0; i < PopulationStartSize_a; i++) {
		std::cout << "Probka nr: " << counter++ << std::endl;
		obj->GenerateRandomDNA();
		for (int DNACell : obj->getDNA()) {
			std::cout << DNACell << " ";
		}
		std::cout << std::endl;
		obj->DNA.clear();
	}
	delete obj;
}

bool CanStart() { // Funckja do sprawdzania integralności
	bool ret = true;
	return ret;
}
std::vector<int> TranslateDNA(Osobnik x) {
	std::vector<int> xx;
	int y=0;  // Poprawić na CurrentFloor w przyszłości
	xx.push_back(y);
	for (int i = 0; i < DNALength; i++) {
		if (x.DNA[i]) {
			if (y == maxFloor) { // Przed uruchomieniem algorytmu musisz sie upewnic, ze maxFloor ma jakas wartosc
				xx.push_back(y);
			}
			else {
				y++;
				xx.push_back(y);
			}
		}
		else {
			if (y == minFloor) { 
				xx.push_back(y);
			}
			else {
				y--;
				xx.push_back(y);
			}
		}
	}
	return xx;
}
void ClearData() {  // Czycie dane na razie tylko tyle trzeba aby ponownie uruchomić algorytm
	BestOsobnik.Fitness = 0;
	BestOsobnik2.Fitness = 0;
	BestOsobnik.MovesAmount = 10000;
	BestOsobnik2.MovesAmount = 10000;
}
void PrintInformations(std::vector<Osobnik> arr, Osobnik x, int generationC, double previousFitness) { // Wywoływać po sortFitness
	if(previousFitness != x.Fitness){
		std::cout << "Najlepszy Fitness w " << generationC << " Generacji: " << arr[0].Fitness << " Ilosc ruchow: " << arr[0].MovesAmount << " ";
		std::cout << "Najlepszy Fitness zawsze to: " << x.Fitness << " Ilosc ruchow: " << x.MovesAmount << std::endl;
	}
	else {
		std::cout << "Najlepszy Fitness w " << generationC << " Generacji: " << arr[0].Fitness << " Ilosc ruchow: " << arr[0].MovesAmount << std::endl;
	}
}
double NormalizingFitness(int MovesAmount, int DNALength, int totalServed) {
	// Wagi dla różnych komponentów
	const double MOVES_WEIGHT = 0.3;
	const double SERVED_WEIGHT = 0.7;
	
	// Efektywność ruchów (mniej ruchów = lepiej)
	double movementEfficiency = 1.0 - (static_cast<double>(MovesAmount) / DNALength);
	
	// Efektywność obsługi (więcej obsłużonych = lepiej)
	double serviceEfficiency = static_cast<double>(totalServed) / MaxZapytan;
	
	// Końcowy wynik
	return (movementEfficiency * MOVES_WEIGHT + serviceEfficiency * SERVED_WEIGHT);
}
double InvertFitness(double f) { // Nie wiem dlaczego nie działa, Chciałem żeby np. z wartości 0.7 zmieniało się na wartość 0.3 w przypadku maxFitness = 1;
	double x = FitnessScaleMax - f;  // Albo z 4.2 na 0.8 w przypadku jak max fitness = 5; Ale wychodzą wartości ujemne jakimś cudem
	return x;
}
void FitnessSimulation(Osobnik& x, std::vector<Zapytanie> newEnquiryVector) {
	std::vector<int> CurrentF = TranslateDNA(x);
	std::vector<Zapytanie> Queue;
	int EnquirySize = newEnquiryVector.size();
	for (size_t i = 0; i < CurrentF.size(); i++) {
		for (int j = 0; j < EnquirySize; j++) {
			if (newEnquiryVector[j].MiejsceP == CurrentF[i]) {
				if (Queue.size() >= static_cast<size_t>(MaxZapytan)) {
					break;
				}
				Queue.push_back(newEnquiryVector[j]);
				newEnquiryVector.erase(newEnquiryVector.begin() + j);
				j--;
				EnquirySize--;
			}
		}
		int QueueSize = Queue.size();
		for (int j = 0; j < QueueSize; j++) {
			if (Queue[j].MiejsceD == CurrentF[i]) {
				Queue.erase(Queue.begin() + j);
				j--;
				QueueSize--;
			}
		}
		if (newEnquiryVector.size() == 0 && Queue.size() == 0) {
			x.MovesAmount = i;
			// a = InvertFitness(a);
			x.Fitness = InvertFitness(NormalizingFitness(i,DNALength,0));
			break;
		}
		if(i == CurrentF.size() - 1){
			x.MovesAmount = i;
			// a = InvertFitness(a);
			x.Fitness = InvertFitness(NormalizingFitness(i, DNALength, 0));
			break;
		}
	}
}
void InvertingWrongDNA(Osobnik& x) {  //Zmienia DNA jeśli wyszłoby poza zakres aby ulepszyć rozwiązanie
	int FCounter = 0; // Zmienić potem na CurrentFloor
	for (int i = 0; i < DNALength; i++) {
		if (x.DNA[i] == 0) {
			FCounter--;
			if (FCounter < minFloor) {
				FCounter += 2;
				x.DNA[i] = 1;
			}
		}
		else {
			FCounter++;
			if (FCounter > maxFloor) {
				FCounter -= 2;
				x.DNA[i] = 0;
			}
		}
	}
}
// Trzeba przekazać wektor z osobnikami przez referencję, dokonuje on selekcji i zmniejsza ilość osobników o 50% (200 -> 100). Zwraca ten sam wektor z nową populacją.
void Selection(std::vector<Osobnik>& population) {
	std::vector<Osobnik> newPopulation;
	int populationSize = population.size();
	
	// Sortuj populację według fitness (malejąco)
	std::sort(population.begin(), population.end(), 
		[](const Osobnik& a, const Osobnik& b) { return a.Fitness > b.Fitness; });
	
	// Zachowaj 10% najlepszych osobników
	int eliteSize = populationSize / 10;
	for (int i = 0; i < eliteSize; i++) {
		newPopulation.push_back(population[i]);
	}
	
	// Selekcja turniejowa dla reszty populacji
	while (newPopulation.size() < static_cast<size_t>(populationSize)) {
		// Wybierz 3 losowych osobników
		int idx1 = rand() % populationSize;
		int idx2 = rand() % populationSize;
		int idx3 = rand() % populationSize;
		
		// Wybierz najlepszego z nich
		Osobnik& best = population[idx1];
		if (population[idx2].Fitness > best.Fitness) best = population[idx2];
		if (population[idx3].Fitness > best.Fitness) best = population[idx3];
		
		newPopulation.push_back(best);
	}
	
	population = newPopulation;
}
void Crossover(std::vector<Osobnik>& arr) { // Należy przekazać vektor, zwraca ona 2 razy większy wektor z 50% starej populacji i 50% nowej
	PopulationSize = arr.size();
	for (int i = 0; i < PopulationSize; i += 2) {
		Osobnik p1, p2;
		if (i == PopulationSize - 1) {
			for (int j = 0; j < DNALength; j++) {
				if (j % 2 == 0) {
					p1.DNA.push_back(arr[i].DNA[j]);
					p2.DNA.push_back(arr[i - 1].DNA[j]);
				}
				else {
					p1.DNA.push_back(arr[i - 1].DNA[j]);
					p2.DNA.push_back(arr[i].DNA[j]);
				}
			}
		}
		else {
			for (int j = 0; j < DNALength; j++) {
				if (j % 2 == 0) {
					p1.DNA.push_back(arr[i].DNA[j]);
					p2.DNA.push_back(arr[i + 1].DNA[j]);
				}
				else {
					p1.DNA.push_back(arr[i + 1].DNA[j]);
					p2.DNA.push_back(arr[i].DNA[j]);
				}
			}
		}
		arr.push_back(p1);
		arr.push_back(p2);
	}
	if (arr.size() % 2 != 0) {
		arr.pop_back();
	}
}
void Crossover2(std::vector<Osobnik>& arr) { // Minimalna wielkość populacji to 5
	PopulationSize = arr.size();
	if (PopulationSize < 5) {
		std::cout << "Za mała populacja";
		return;
	}
	for (int i = 0; i < PopulationSize; i++) {
		Osobnik p1;
		if (i == PopulationSize - 2) {
			for (int j = 0; j < DNALength; j++) {
				if (arr[i].DNA[j] == arr[i + 1].DNA[j]) {
					p1.DNA.push_back(arr[i].DNA[j]);
				}
				else p1.DNA.push_back(rand() % 2);
				if (arr[i].DNA[j] == arr[0].DNA[j]) {
					p1.DNA.push_back(arr[i].DNA[j]);
				}
				else p1.DNA.push_back(rand() % 2);
			}
		}
		else if (i == PopulationSize - 1) {
			for (int j = 0; j < DNALength; j++) {
				if (arr[i].DNA[j] == arr[0].DNA[j]) {
					p1.DNA.push_back(arr[i].DNA[j]);
				}
				else p1.DNA.push_back(rand() % 2);
				if (arr[i].DNA[j] == arr[1].DNA[j]) {
					p1.DNA.push_back(arr[i].DNA[j]);
				}
				else p1.DNA.push_back(rand() % 2);
			}
		}
		else {
			for (int j = 0; j < DNALength; j++) {
				if (arr[i].DNA[j] == arr[i + 1].DNA[j]) {
					p1.DNA.push_back(arr[i].DNA[j]);
				}
				else p1.DNA.push_back(rand() % 2);
				if (arr[i].DNA[j] == arr[i + 2].DNA[j]) {
					p1.DNA.push_back(arr[i].DNA[j]);
				}
				else p1.DNA.push_back(rand() % 2);
			}
		}
		arr.push_back(p1);
	}
}
void SortFitness(std::vector<Osobnik>& arr) { // Należy przekazać vektor, Funkcja sortuje vector pod względem Fitnesu osobników i przygotowuje go do funkcji Crossover, zwraca vektor posortoway
	sort(arr.begin(),
		arr.end(),
		[](const Osobnik& lhs, const Osobnik& rhs)
		{
			return lhs.Fitness > rhs.Fitness;
		});
}
void IsBest(Osobnik x, Osobnik& y) { // Wywoływać po SortFitness
	if (x.Fitness > y.Fitness) {
		y = x;
	}
	else if (x.MovesAmount < y.MovesAmount) {
		y = x;
	}
}
void CrossoverView(std::vector<Zapytanie> enquiries, std::vector<int>& moveQueue) {
		int NumberOfGenerations = 0;
		double previousBest = 0;
		srand(time(NULL));
		std::vector<Osobnik> o(PopulationStartSize);
		for (int i = 0; i < PopulationStartSize; i++) {
			o[i].GenerateRandomDNA();
		}
		for (int i = 0; i < o.size(); i++) {
			FitnessSimulation(o[i], enquiries);
		}
		SortFitness(o);
		IsBest(o[0],BestOsobnik);
		PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
		while (NumberOfGenerations < GenerationAmount) {
			NumberOfGenerations++;
			previousBest = BestOsobnik.Fitness;
			Crossover(o);
			for (size_t i = o.size()/10; i < o.size(); i++) {
				o[i].Mutate();
			}
			for (int i = 0; i < o.size(); i++) {
				InvertingWrongDNA(o[i]);
			}
			for (int i = 0; i < o.size(); i++) {
				FitnessSimulation(o[i], enquiries);
			}
			Selection(o);
			SortFitness(o);
			IsBest(o[0], BestOsobnik);
			PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
		}
		std::cout << std::endl;

		for (int move : BestOsobnik.DNA) {
			moveQueue.push_back(move);
			std::cout << move << " ";
		}
}
void AlgorithmConfiguration() {
	std::cout << "Podaj długość DNA: ";
	std::cin >> DNALength;
	std::cout << "Podaj ilość generacji: ";
	std::cin >> GenerationAmount;
	std::cout << "Podaj współczynnik mutacji (1/x): ";
	std::cin >> MutationRate;
	std::cout << "Podaj rozmiar populacji początkowej: ";
	std::cin >> PopulationStartSize;
}
int AlgorithmPopulationSize() {
	std::cout << "Wpisz poczatkowa wielkosc populacji: ";
	std::cin >> PopulationStartSize;
	return PopulationStartSize;
}


// POWTORZENIE ALGORYTMOW Z PARAMETRAMI WINDY - JEZELI MOZNA TO ZCALIC W JEDNA FUNKCJE - MAX FLOOR ZASTEPOWANY CAPACITY WINDY KTORA BEDZIE UZYWANA
void AlgorithmObliczania(std::vector<Zapytanie> enquiries, std::vector<int>& moveQueue, int capacity) {
	int NumberOfGenerations = 0;
	double previousBest = 0;
	srand(time(NULL));
	std::vector<Osobnik> o(PopulationStartSize);
	for (int i = 0; i < PopulationStartSize; i++) {
		o[i].GenerateRandomDNA();
	}
	for (size_t i = 0; i < o.size(); i++) {
		FitnessSimulationWithElevator(o[i], enquiries, capacity);
	}
	SortFitness(o);
	IsBest(o[0], BestOsobnik);
	PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
	while (NumberOfGenerations < GenerationAmount) {
		NumberOfGenerations++;
		previousBest = BestOsobnik.Fitness;
		Crossover(o);
		for (size_t i = o.size()/10; i < o.size(); i++) {
			o[i].Mutate();
		}
		for (int i = 0; i < o.size(); i++) {
			InvertingWrongDNA(o[i]);
		}
		for (size_t i = 0; i < o.size(); i++) {
			FitnessSimulationWithElevator(o[i], enquiries, capacity);
		}
		Selection(o);
		SortFitness(o);
		IsBest(o[0], BestOsobnik);
		PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
	}
	std::cout << std::endl;

	for (int move : BestOsobnik.DNA) {
		moveQueue.push_back(move);
		std::cout << move << " ";
	}
}
void displayElevatorState(int currentFloor, const std::vector<Zapytanie>& queue, 
                         const std::vector<Zapytanie>& enquiriesWaiting, 
                         int maxFloor, int capacity, int currentStep, int lastMove) {
    ClearScreen();
    std::cout << "Symulacja windy - Krok " << currentStep << " z " << DNALength << std::endl;
    
    // Wyświetl informacje o windzie
    std::cout << "Osoby w windzie: " << queue.size() << "/" << capacity << std::endl;
    if (!queue.empty()) {
        std::cout << "Cel pasażerów: ";
        for (const auto& p : queue) {
            std::cout << p.getMiejsceD() << " ";
        }
        std::cout << std::endl;
    }
    
    // Wyświetl budynek z windą
    for (int floor = maxFloor; floor >= 0; floor--) {
        std::cout << std::setw(2) << floor << " |";
        
        // Winda
        if (floor == currentFloor) {
            if (queue.empty()) {
                std::cout << "[□]"; // Pusta winda
            } else {
                std::cout << "[■]"; // Winda z pasażerami
            }
        } else {
            std::cout << "   ";
        }
        
        // Oczekujący pasażerowie
        bool hasWaiting = false;
        for (const auto& p : enquiriesWaiting) {
            if (p.getMiejsceP() == floor) {
                std::cout << " ○"; // Symbol oczekującego pasażera
                hasWaiting = true;
            }
        }
        if (!hasWaiting) {
            std::cout << "  ";
        }
        
        std::cout << std::endl;
    }
    std::cout << "---+------------------" << std::endl;
    
    // Wyświetl kierunek ruchu
    std::cout << "Kierunek: " << (lastMove == 1 ? "UP" : "DOWN") << std::endl;
    
    Sleep(500); // Krótka pauza dla lepszej wizualizacji
}

void FitnessSimulationWithElevator(Osobnik& x, std::vector<Zapytanie> newEnquiryVector, int ElevatorCapacity_a) {
    std::vector<int> CurrentF = TranslateDNA(x);
    std::vector<Zapytanie> Queue;
    int currentFloor = 0;
    int totalServed = 0;
    int totalMoves = 0;
    bool lastMoveCompleted = false;
    
    // Kopiujemy wektor zapytań, żeby nie modyfikować oryginału
    std::vector<Zapytanie> remainingEnquiries = newEnquiryVector;
    
    for (size_t i = 0; i < CurrentF.size(); i++) {
        bool passengerAction = false;
        
        // Aktualizacja piętra i liczenie ruchów
        if (CurrentF[i] == 1 && currentFloor < maxFloor) {
            currentFloor++;
            totalMoves++;
        } else if (CurrentF[i] == 0 && currentFloor > minFloor) {
            currentFloor--;
            totalMoves++;
        }

        // Wysiadanie pasażerów
        for (int j = Queue.size() - 1; j >= 0; j--) {
            if (Queue[j].getMiejsceD() == currentFloor) {
                Queue.erase(Queue.begin() + j);
                totalServed++;
                passengerAction = true;
            }
        }

        // Wsiadanie pasażerów
        if (Queue.size() < static_cast<size_t>(ElevatorCapacity_a)) {
            for (int j = remainingEnquiries.size() - 1; j >= 0; j--) {
                if (remainingEnquiries[j].getMiejsceP() == currentFloor) {
                    if (Queue.size() < static_cast<size_t>(ElevatorCapacity_a)) {
                        Queue.push_back(remainingEnquiries[j]);
                        remainingEnquiries.erase(remainingEnquiries.begin() + j);
                        passengerAction = true;
                    }
                }
            }
        }

        // Sprawdzenie zakończenia
        if (i == CurrentF.size() - 1) {
            if (currentFloor == minFloor && Queue.empty() && remainingEnquiries.empty()) {
                lastMoveCompleted = true;
            }
        }
    }

    // Obliczanie fitness
    double efficiency = static_cast<double>(totalServed) / newEnquiryVector.size(); // Skuteczność obsługi
    double moveEfficiency = 1.0 - (static_cast<double>(totalMoves) / DNALength); // Efektywność ruchów
    double completionBonus = lastMoveCompleted ? 0.3 : 0.0; // Bonus za zakończenie na parterze
    
    // Kary
    double unservedPenalty = static_cast<double>(remainingEnquiries.size()) / newEnquiryVector.size(); // Kara za nieobsłużonych
    double queuePenalty = static_cast<double>(Queue.size()) / ElevatorCapacity_a; // Kara za pozostałych w windzie
    
    // Końcowy fitness
    double fitness = (efficiency * 0.4) + (moveEfficiency * 0.3) + completionBonus - (unservedPenalty * 0.2) - (queuePenalty * 0.1);
    
    // Normalizacja fitness do zakresu [0,1]
    fitness = std::max(0.0, std::min(1.0, fitness));
    
    x.MovesAmount = totalMoves;
    x.Fitness = fitness;
}
void SymulationFromFile(std::vector<Zapytanie> newEnquiryVector ,std::vector<int>& moveQueueVector, int ElevatorCapacity) {
	int NumberOfGenerations = 0;
	double previousBest = 0;
	srand(time(NULL));
	std::vector<Osobnik> o;
	int ifgen;
	std::cout << "Wygenerowac nowy plik z DNA? (0,1)" << std::endl;
	std::cin >> ifgen;
	if (ifgen) {
		int am;
		std::string fn;
		std::cout << "Wpisz Ilosc Zestawow Do Wygenerowania: ";
		std::cin >> am;
		std::cout << "Wpisz Nazwe Pliku (er)";
		std::cin >> fn;
		generateDNAToFile(am,fn);
	}
	o = readDNAFromFile(PopulationStartSize, "er");
	for (size_t i = 0; i < o.size(); i++) {
		FitnessSimulationWithElevator(o[i], newEnquiryVector, ElevatorCapacity);
	}
	SortFitness(o);
	IsBest(o[0], BestOsobnik);
	PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
	saveAlgorithmDataToFile("er", "er", NumberOfGenerations, o[0], BestOsobnik, DNALength, PopulationStartSize, MutationRate, GenerationAmount, FitnessScaleMin, FitnessScaleMax, ElevatorCapacity, newEnquiryVector.size(), maxFloor, minFloor, "");
	while (NumberOfGenerations < GenerationAmount) {
		NumberOfGenerations++;
		previousBest = BestOsobnik.Fitness;
		Crossover(o);
		for (size_t i = o.size()/10; i < o.size(); i++) {
			o[i].Mutate();
		}
		for (size_t i = 0; i < o.size(); i++) {
			InvertingWrongDNA(o[i]);
		}
		for (size_t i = 0; i < o.size(); i++) {
			FitnessSimulationWithElevator(o[i], newEnquiryVector, ElevatorCapacity);
		}
		Selection(o);
		SortFitness(o);
		IsBest(o[0], BestOsobnik);
		PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
		saveAlgorithmDataToFile("er", "er", NumberOfGenerations, o[0], BestOsobnik, DNALength, PopulationStartSize, MutationRate, GenerationAmount, FitnessScaleMin, FitnessScaleMax, ElevatorCapacity, newEnquiryVector.size(), maxFloor, minFloor, "");
	}
	std::cout << std::endl;

	for (int move : BestOsobnik.DNA) {
		moveQueueVector.push_back(move);
		std::cout << move << " ";
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generateDNAToFile(int amount, std::string fileName) { // Przekazujesz ilość Osobników dla ilu ma być wygenerowane DNA(amount) fileName to nazwa pliku jaki ma być utworzony, albo append do jakiego.
	std::vector<Osobnik> x(amount);
	for (int i = 0; i < amount; i++) {
		x[i].GenerateRandomDNA();
	}
	transferDNAToFile(x, fileName);
}
void transferDNAToFile(std::vector<Osobnik> vec, std::string fileName) { // Nie wywołuj tej funkcji samej. Wywołaj generateDNAToFile. 
	// Funkcja jest stworzona tak że jeśli istnieje już plik z danymi o takiej samej nazwie to usuwa jego zawartości i generuje nowe DNA
	// Pierwsze dwie linijki w wygenerowanym pliku to w kolejności długość wygenerowanego DNA a następnie ilość wygenerowanych.
	std::fstream MyFile;
	if (fileName == "er") {
		fileName = "DNASample.csv";
	}
	MyFile.open(fileName, std::ios::out);
	if (MyFile.is_open()) {
		MyFile << DNALength << std::endl;
		MyFile << vec.size() << std::endl;
		for (size_t i = 0; i < vec.size(); i++) {
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
void deleteFile(std::string fileName) { // Funkcja do usuwania pliku, należy przekazać nazwę i rozszerzenie
	if (fileName == "er") {
		fileName = "DNASample.csv";
	}
	if (std::remove(fileName.c_str()) != 0) {
		std::cout << "Nie usunieto lub taki plik juz nie istnial \n";
	}
	else {
		std::cout << "Usunieto pomyslnie \n";
	}
}
std::vector<Osobnik> readDNAFromFile(int amount, std::string fileName) { // Należy przekazać nazwę pliku oraz ilość osobników dla ilu ma być pobrane DNA. Długość DNA pobierana jest z DNALength
	std::vector<Osobnik> x;  // Funckja zwróci vektor o odpowiedniej długości(amount) i DNALenght takim jak w algorytm.cpp
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

		if (amount > maxAmount) {
			std::cout << "W pliku jest zbyt malo danych aby pobrac taka ilosc DNA osobnikow";
		}
		else if (DNALength > maxDNALength) {
			std::cout << "W pliku DNA jest zbyt krotkie zeby pobrac taka dlugosc";
		}
		else {
			for (int i = 0; i < amount; i++) {
				Osobnik p;
				getline(MyFile, temp);
				for (int j = 0; j < DNALength; j++) {
					p.DNA.push_back((temp[j] - 48));

				}
				x.push_back(p);
			}
		}
		MyFile.close();
	}
	return x;
}
void saveAlgorithmDataToFile(std::string fileName, std::string enquiriesFileName, int currGeneration, Osobnik x, Osobnik Best, int DNAL, int popStartSize, int mutationChance, int genAmount,
	int minFitness, int maxFitness, int maxEnquiriesInElevator, int enquiriesAmount, int maxF, int minF, std::string addInfo) {
	std::fstream MyFile;
	if (fileName == "er") {
		fileName = "AlgorithmData.csv";
	}
	if (addInfo == "er") {
		addInfo = "No Additional Info";
	}
	if (enquiriesFileName == "er") {
		enquiriesFileName = "Enquiries.csv";
	}
	MyFile.open(fileName, std::ios::app);
	if (MyFile.is_open()) {
		if (currGeneration == 0) {
			MyFile << "Informacje o Konfiguracji" << std::endl;
			MyFile << addInfo << std::endl;
			MyFile << "ALGORYTM" << std::endl;
			MyFile << "Długość DNA: " << DNAL << " Populacja Początkowa: " << popStartSize << " Częstotliwość Mutacji: " << mutationChance << " Ilość Generacji: " << genAmount <<
				" Minimalny Fitness: " << minFitness << " Maksymalny Fitness: " << maxFitness << std::endl;
			MyFile << "ZAPYTANIA" << std::endl;
			MyFile << "Maksymalna Ilość Zapytań w Windzie: " << maxEnquiriesInElevator << " Ilość Zapytań: " << enquiriesAmount << " Minimalne Możliwe Piętro: " << minF << " Maksymalne Możliwe Piętro"
				<< maxF << std::endl;
			MyFile << "LISTA ZAPYTAŃ" << std::endl;
			std::fstream* enq = new std::fstream();
			enq->open(enquiriesFileName);
			if (enq->is_open()) {
				std::string temp;
				while (getline(*enq, temp)) {
					MyFile << temp << std::endl;
				}
			}
			else MyFile << "NIE UDAŁO SIĘ WCZYTAĆ ZAPYTAŃ" << std::endl;
			delete enq;
		}
		MyFile << "Aktualna Generacja: " << currGeneration << " Najlepszy Fitness: " << x.Fitness << " Najlepsza Ilość Ruchów: " << x.MovesAmount << std::endl;
		MyFile << "Najlepszy Fitness Zawsze: " << Best.Fitness << " Najlepsza Ilość Ruchów Zawsze: " << Best.MovesAmount << std::endl;
		MyFile << "Najlepsze DNA: ";
		for (int i : Best.DNA) {
			MyFile << i;
		}
		MyFile << std::endl;
		MyFile.close();
	}
	else std::cout << "NIE UDALO SIE OTWORZYC PLIKU" << std::endl;
}

double calculateFitness(const std::vector<int>& moves, const std::vector<Zapytanie>& enquiries, int capacity) {
	double fitness = 1.0;
	
	// Kary za:
	const double PENALTY_UNNECESSARY_MOVE = 0.05;
	const double PENALTY_LONG_WAIT = 0.1;
	const double PENALTY_CAPACITY_EXCEED = 0.3;
	const double REWARD_SERVED_REQUEST = 0.2;
	const double PENALTY_NOT_FINISHING = 0.5;
	
	int currentFloor = 0;
	int peopleInElevator = 0;
	std::vector<bool> servedEnquiries(enquiries.size(), false);
	int waitTime = 0;
	bool reachedBottom = false;

	for (size_t i = 0; i < moves.size(); i++) {
		bool isUsefulMove = false;
		
		// Aktualizacja piętra
		if (moves[i] == 1 && currentFloor < maxFloor) {
			currentFloor++;
		} else if (moves[i] == 0 && currentFloor > minFloor) {
			currentFloor--;
		}

		// Sprawdź zapytania na obecnym piętrze
		for (size_t j = 0; j < enquiries.size(); j++) {
			if (!servedEnquiries[j]) {
				if (enquiries[j].getMiejsceP() == currentFloor || 
					enquiries[j].getMiejsceD() == currentFloor) {
					isUsefulMove = true;
					if (enquiries[j].getMiejsceP() == currentFloor) {
						if (peopleInElevator < capacity) {
							peopleInElevator++;
							fitness += REWARD_SERVED_REQUEST;
						}
					}
					if (enquiries[j].getMiejsceD() == currentFloor) {
						peopleInElevator--;
						servedEnquiries[j] = true;
						fitness += REWARD_SERVED_REQUEST * 2;  // Większa nagroda za dostarczenie
					}
				}
			}
		}

		// Kary
		if (!isUsefulMove) {
			fitness -= PENALTY_UNNECESSARY_MOVE;
		}
		if (peopleInElevator > capacity) {
			fitness -= PENALTY_CAPACITY_EXCEED;
		}
		if (waitTime > 10) {
			fitness -= PENALTY_LONG_WAIT;
		}
		
		// Sprawdź czy winda dotarła na parter pod koniec
		if (i >= moves.size() - 5 && currentFloor == minFloor) {
			reachedBottom = true;
			fitness += 0.3;  // Bonus za dotarcie na parter
		}
		
		waitTime++;
	}

	// Kara za niedokończenie trasy na parterze
	if (!reachedBottom) {
		fitness -= PENALTY_NOT_FINISHING;
	}

	// Oblicz procent obsłużonych zapytań
	double servedRatio = std::count(servedEnquiries.begin(), servedEnquiries.end(), true) / 
						static_cast<double>(enquiries.size());
	fitness += servedRatio;

	return std::max(0.0, std::min(1.0, fitness));
}

int findNearestEnquiry(int currentFloor, const std::vector<Zapytanie>& enquiries) {
	if (enquiries.empty()) return currentFloor;
	
	int nearestFloor = enquiries[0].getMiejsceP();
	int minDistance = std::abs(currentFloor - nearestFloor);
	
	for (const auto& enquiry : enquiries) {
		int startFloor = enquiry.getMiejsceP();
		int distance = std::abs(currentFloor - startFloor);
		
		if (distance < minDistance) {
			minDistance = distance;
			nearestFloor = startFloor;
		}
	}
	
	return nearestFloor;
}

std::vector<int> generateSmartDNA(const std::vector<Zapytanie>& enquiries) {
	std::vector<int> dna(static_cast<size_t>(DNALength));
	int currentFloor = 0;
	
	// Rezerwujemy więcej ruchów na powrót
	int reservedMoves = std::min(20, DNALength / 4);
	int mainSequenceLength = DNALength - reservedMoves;
	
	// Generowanie głównej sekwencji ruchów
	for (int i = 0; i < mainSequenceLength; i++) {
		if (rand() % 100 < 80) {  // Zwiększamy szansę na inteligentny ruch
			int nearestFloor = findNearestEnquiry(currentFloor, enquiries);
			if (nearestFloor > currentFloor) {
				dna[i] = 1;
				currentFloor++;
			} else if (nearestFloor < currentFloor) {
				dna[i] = 0;
				currentFloor--;
			} else {
				dna[i] = rand() % 2;
			}
		} else {
			dna[i] = rand() % 2;
			if (dna[i] == 1 && currentFloor < maxFloor) currentFloor++;
			else if (dna[i] == 0 && currentFloor > minFloor) currentFloor--;
		}
	}
	
	// Sekwencja powrotu na parter
	for (int i = mainSequenceLength; i < DNALength; i++) {
		if (currentFloor > minFloor) {
			dna[i] = 0;
			currentFloor--;
		} else {
			dna[i] = 0;
		}
	}
	
	return dna;
}