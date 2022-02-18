#include "Algorytm.h"

extern const int DNALength;  // Sta�a d�ugo�� �a�cucha DNA


const int MutationRate = 100; // Cz�stotliwo�� mutacji im wi�ksza tym mniejsza szansa na mutacje
const int PopulationStartSize = 100; // Wielko�� pocz�tkowa populacji
int PopulationSize = 0; // Obecna wielko�� populacji

int GenerationCounter = 0; // Liczy ilo�� generacji
int FloorMoveTime = 5; // Wyra�ony w sekundach czas podr�y mi�dzy jednym pi�trem
int FloorWaitTime = 2; // Wyra�ony w sekundach czas otwarcia i oczekiwania windy na pi�trze
int ZapytanieCounter;  // Zmienna przedstawiaj�ca ile zosta�o jeszcze zapyta�

void Osobnik::Mutate() { // Wykonuje mutacje o szansie okre�lonej przez zmienn� globaln�
	for (int i = 0; i < Fitness; i++) {
		if (rand() % MutationRate == 0) {
			if (DNA[i] == 0)DNA[i] = 1;
			else if (DNA[i] == 1)DNA[i] = 0;
			else DNA[i] = rand() % 2;
		}
	}
}
bool Osobnik::IsDone(int index) {  // Funkcja kt�ra sprawdza czy wszystkie zapytania zosta�y zrealizowanie. Je�eli nie ma ju� zapyta� zwraca true i przypisuje index do zmiennej, inaczej zwraca false
		// Nale�y przekaza� aktualny index p�tli w kt�rej wykonoywana jest symulacja i usuwanie zapyta�.
	if (!ZapytanieCounter) {
		Fitness = index;
		return true;
	}
	else if (index == DNALength) {
		Fitness = index;
		return true;
	}
	else return false;
	// W p�tli symulacyjnej uwzgl�dni� �e je�eli po jakim� indexie isDone zwr�ci�o true
}

void Osobnik::GenerateRandomDNA() {
	for (int i = 0; i < DNALength; i++) {
		DNA[i] = rand() % 2;
	}
};



// Trzeba przekaza� wektor z osobnikami przez referencj�, dokonuje on selekcji i zmniejsza ilo�� osobnik�w o 50% (200 -> 100). Zwraca ten sam wektor z now� populacj�.
void Selection(std::vector<Osobnik>& arr) { // Do naprawy
	std::vector<Osobnik> newVector;
	PopulationSize = arr.size();

	
	
	/*std::vector<Osobnik> Young;
	do {
		PopulationSize = arr.size();
		if (PopulationSize == 0)break;
		if (PopulationSize == 1) {
			Young.push_back(arr[0]);
			arr.clear();
		}
		Osobnik p1, p2;
		// Wybieranie losowego osobnika i usuwanie go z starego wektora
		int RNumber1 = rand() % PopulationSize;
		p1 = arr[RNumber1];
		arr.erase(arr.begin() + RNumber1);
		PopulationSize = arr.size();
		int RNumber2 = rand() % PopulationSize;
		p2 = arr[RNumber2];
		arr.erase(arr.begin() + RNumber2);
		// Turniejowa metoda selekcji
		if (p1.Fitness < p2.Fitness)Young.push_back(p1);
		else if (p2.Fitness < p1.Fitness)Young.push_back(p2);
		else {
			int rn = rand() % 2;
			if (rn)Young.push_back(p2);
			else Young.push_back(p1);
		}
	} while (PopulationSize);
	arr.clear();
	arr = Young;
	PopulationSize = arr.size();
	*/
};
void Crossover(std::vector<Osobnik>& arr) { // Nale�y przekaza� vektor, zwraca ona 2 razy wi�kszy wektor z 50% starej populacji i 50% nowej
	PopulationSize = arr.size();
	for (int i = 0; i < PopulationSize; i += 2) {
		Osobnik p1, p2;
		if (i == PopulationSize - 1) {
			for (int j = 0; j < DNALength; j++) {
				if (j % 2 == 0) {
					p1.DNA[j] = arr[i].DNA[j];
					p2.DNA[j] = arr[i - 1].DNA[j];
				}
				else {
					p1.DNA[j] = arr[i - 1].DNA[j];
					p2.DNA[j] = arr[i].DNA[j];
				}
			}
		}
		else {
			for (int j = 0; j < DNALength; j++) {
				if (j % 2 == 0) {
					p1.DNA[j] = arr[i].DNA[j];
					p2.DNA[j] = arr[i + 1].DNA[j];
				}
				else {
					p1.DNA[j] = arr[i + 1].DNA[j];
					p2.DNA[j] = arr[i].DNA[j];
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
void SortFitness(std::vector<Osobnik>& arr) { // Nale�y przekaza� vektor, Funkcja sortuje vector pod wzgl�dem Fitnesu osobnik�w i przygotowuje go do funkcji Crossover, zwraca vektor posortoway
	sort(arr.begin(),
		arr.end(),
		[](const Osobnik& lhs, const Osobnik& rhs)
		{
			return lhs.Fitness < rhs.Fitness;
		});
}

void CrossoverView() {
	srand(time(NULL));
	std::vector<Osobnik> o(PopulationStartSize);
	for (int i = 0; i < PopulationStartSize; i++) {
		o[i].GenerateRandomDNA();
	}
	Crossover(o);
	for (int i = 0; i < o.size(); i++) {
		o[i].Fitness = rand() % 200;
	}
	SortFitness(o);
	for (int i = 0; i < o.size(); i++) {
		std::cout << o[i].Fitness << ",";
	}
	Selection(o);
}
// Trzeba zrobi� funkcj� losuj�c� w taki spos�b �e po wylosowaniu danej liczby usuwa ona si� ze zbioru liczb kt�re mo�na wylosowa�

/*int main()
{
	srand(time(NULL));
	std::vector<Osobnik> o(PopulationStartSize);
	for (int i = 0; i < PopulationStartSize; i++) {
		o[i].GenerateRandomDNA();
	}
	Crossover(o);
	for (int i = 0; i < o.size(); i++) {
		o[i].Fitness = rand() % 100;
	}
	SortFitness(o);
	for (int i = 0; i < o.size(); i++) {
		std::cout << o[i].Fitness << ",";
	}
	Selection(o);
	return 0;
}
*/

