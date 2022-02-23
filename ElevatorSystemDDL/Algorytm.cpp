#include "Algorytm.h"
#include "Zapytania.h"
#include "GlobalVariables.h"

int DNALength = 200;  // Sta�a d�ugo�� �a�cucha DNA
extern int maxFloor;
extern int minFloor; //Na przyszlosc do poprawienia liniki 49
int GenerationAmount = 100;
int MutationRate = 100; // Cz�stotliwo�� mutacji im wi�ksza tym mniejsza szansa na mutacje
int PopulationStartSize = 200; // Wielko�� pocz�tkowa populacji
int PopulationSize = 0; // Obecna wielko�� populacji
int MaxZapytan = 10;
int FitnessScaleMax = 1;
int FitnessScaleMin = 0;

Osobnik BestOsobnik;
Osobnik BestOsobnik2;

void Osobnik::Mutate() { // Wykonuje mutacje o szansie okre�lonej przez zmienn� globaln�
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
		// Nale�y przekaza� aktualny index p�tli w kt�rej wykonoywana jest symulacja i usuwanie zapyta�.
	Fitness = index;
}
void Osobnik::GenerateRandomDNA() {
	for (int i = 0; i < DNALength; i++) {
		DNA.push_back(rand() % 2);
	}
}
bool CanStart() { // Funckja do sprawdzania integralno�ci
	bool ret = true;
	return ret;
}
std::vector<int> TranslateDNA(Osobnik x) {
	std::vector<int> xx;
	int y=0;  // Poprawi� na CurrentFloor w przysz�o�ci
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
void ClearData() {  // Czy�cie dane na razie tylko tyle trzeba aby ponownie uruchomi� algorytm
	BestOsobnik.Fitness = 0;
	BestOsobnik2.Fitness = 0;
	BestOsobnik.MovesAmount = 10000;
	BestOsobnik2.MovesAmount = 10000;
}
void PrintInformations(std::vector<Osobnik> arr, Osobnik x, int generationC) { // Wywo�ywa� po sortFitness
	std::cout << "Najlepszy Fitness w tej generacji " << generationC <<" : " <<  arr[0].Fitness << std::endl;
	std::cout << "Najlepszy Fitness zawsze: " << x.Fitness << std::endl;
}
double NormalizingFitness(double f, int max, int min) {
	double x = ((f - min) / (max - min)) * (FitnessScaleMax - FitnessScaleMin) + FitnessScaleMin;
	return x;
}
double InvertFitness(double f) { // Nie wiem dlaczego nie dzia�a, Chcia�em �eby np. z warto�ci 0.7 zmienia�o si� na warto�� 0.3 w przypadku maxFitness = 1;
	double x = FitnessScaleMax - f;  // Albo z 4.2 na 0.8 w przypadku jak max fitness = 5; Ale wychodza warto�ci ujemne jakim� cudem
	return x;
}
void FitnessSimulation(Osobnik& x, std::vector<Zapytanie> newEnquiryVector) {
	std::vector<int> CurrentF = TranslateDNA(x);
	std::vector<Zapytanie> Queue;
	int EnquirySize = newEnquiryVector.size();
	for (int i = 0; i < CurrentF.size(); i++) {
		for (int j = 0; j < EnquirySize; j++) {
			if (newEnquiryVector[j].MiejsceP == CurrentF[i]) {
				if (Queue.size() >= MaxZapytan) {
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
		if(i==CurrentF.size()-1){
			x.MovesAmount = i;
			// a = InvertFitness(a);
			x.Fitness = InvertFitness(NormalizingFitness(i, DNALength, 0));
			break;
		}
	}
}
void InvertingWrongDNA(Osobnik& x) {  //Zmienia DNA je�eli wysz�oby poza zakres aby ulepszy� rozwi�zanie
	int FCounter = 0; // Zmieni� potem na CurrentFloor
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
// Trzeba przekaza� wektor z osobnikami przez referencj�, dokonuje on selekcji i zmniejsza ilo�� osobnik�w o 50% (200 -> 100). Zwraca ten sam wektor z now� populacj�.
void Selection(std::vector<Osobnik>& arr) {
	std::vector<Osobnik> newVector;
	PopulationSize = arr.size();
	while (PopulationSize) {
		Osobnik p1, p2;
		PopulationSize = arr.size();
		int RNumber;
		RNumber = rand() % PopulationSize;
		p1 = arr[RNumber];
		arr.erase(arr.begin() + RNumber);
		PopulationSize = arr.size();
		RNumber = rand() % PopulationSize;
		p2 = arr[RNumber];
		arr.erase(arr.begin() + RNumber);
		if (p1.Fitness > p2.Fitness) {
			newVector.push_back(p1);
		}
		else if (p1.Fitness < p2.Fitness) {
			newVector.push_back(p2);
		}
		else if (p1.Fitness == p2.Fitness) {
			if (rand() % 2)newVector.push_back(p1);
			else newVector.push_back(p2);
		}
		PopulationSize = arr.size();
	}
	arr = newVector;
}
void Crossover(std::vector<Osobnik>& arr) { // Nale�y przekaza� vektor, zwraca ona 2 razy wi�kszy wektor z 50% starej populacji i 50% nowej
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
void Crossover2(std::vector<Osobnik>& arr) { // Minimalna wielko�� populacji to 5
	PopulationSize = arr.size();
	if (PopulationSize < 5) {
		std::cout << "Za ma�a populacja";
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
void SortFitness(std::vector<Osobnik>& arr) { // Nale�y przekaza� vektor, Funkcja sortuje vector pod wzgl�dem Fitnesu osobnik�w i przygotowuje go do funkcji Crossover, zwraca vektor posortoway
	sort(arr.begin(),
		arr.end(),
		[](const Osobnik& lhs, const Osobnik& rhs)
		{
			return lhs.Fitness > rhs.Fitness;
		});
}
void IsBest(Osobnik x, Osobnik& y) { // Wywo�ywa� po SortFitness
	if (x.Fitness > y.Fitness) {
		y = x;
	}
}
void CrossoverView(std::vector<Zapytanie> newEnquiryVector, std::vector<int>& moveQueueVector) {
		int NumberOfGenerations = 0;
		srand(time(NULL));
		std::vector<Osobnik> o(PopulationStartSize);
		for (int i = 0; i < PopulationStartSize; i++) {
			o[i].GenerateRandomDNA();
		}
		for (int i = 0; i < o.size(); i++) {
			FitnessSimulation(o[i], newEnquiryVector);
		}
		SortFitness(o);
		IsBest(o[0],BestOsobnik);
		PrintInformations(o, BestOsobnik, NumberOfGenerations);
		while (NumberOfGenerations < GenerationAmount) {
			NumberOfGenerations++;
			Crossover(o);
			for (int i = o.size()/10; i < o.size(); i++) {
				o[i].Mutate();
			}
			for (int i = 0; i < o.size(); i++) {
				InvertingWrongDNA(o[i]);
			}
			for (int i = 0; i < o.size(); i++) {
				FitnessSimulation(o[i], newEnquiryVector);
			}
			Selection(o);
			SortFitness(o);
			IsBest(o[0], BestOsobnik);
			PrintInformations(o, BestOsobnik, NumberOfGenerations);
		}
		std::cout << std::endl;

		for (int move : BestOsobnik.DNA) {
			moveQueueVector.push_back(move);
			std::cout << move << " ";
		}
}
void Symulacja2() {
}
void AlgorithmConfiguration() {
	std::cout << "Wpisz dlugosc DNA: ";
	std::cin >> DNALength;
	std::cout << "Wpisz poczatkowa wielkosc populacji: ";
	std::cin >> PopulationStartSize;
	std::cout << "Wpisz szanse na mutacje(int) 50 to 1/50 szansy na mutacje: ";
	std::cin >> MutationRate;
	std::cout << "Wpisz maksymalna ilosc zapytan w windzie na raz: ";
	std::cin >> MaxZapytan;
	std::cout << "Wpisz ilosc generacji: ";
	std::cin >> GenerationAmount;
	// Dodaj opcje wy�wietlania tej funkcji w menu
}
// Trzeba zrobi� funkcj� losuj�c� w taki spos�b �e po wylosowaniu danej liczby usuwa ona si� ze zbioru liczb kt�re mo�na wylosowa�
