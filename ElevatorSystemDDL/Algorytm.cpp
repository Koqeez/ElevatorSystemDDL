#include "Algorytm.h"
#include "Zapytania.h"
#include "DispatcherUnit.h"

extern const int DNALength;  // Sta³a d³ugoœæ ³añcucha DNA
extern int MaxPietro;
extern std::vector<Zapytanie>Enquiries;

const int MutationRate = 100; // Czêstotliwoœæ mutacji im wiêksza tym mniejsza szansa na mutacje
const int PopulationStartSize = 100; // Wielkoœæ pocz¹tkowa populacji
int PopulationSize = 0; // Obecna wielkoœæ populacji
int FloorMoveTime = 5; // Wyra¿ony w sekundach czas podró¿y miêdzy jednym piêtrem
int FloorWaitTime = 2; // Wyra¿ony w sekundach czas otwarcia i oczekiwania windy na piêtrze
int EnquiryCounter;  // Zmienna przedstawiaj¹ca ile zosta³o jeszcze zapytañ
Osobnik BestOsobnik;
void Osobnik::Mutate() { // Wykonuje mutacje o szansie okreœlonej przez zmienn¹ globaln¹
	for (int i = 0; i < Fitness; i++) {
		if (rand() % MutationRate == 0) {
			if (DNA[i] == 0)DNA[i] = 1;
			else if (DNA[i] == 1)DNA[i] = 0;
			else DNA[i] = rand() % 2;
		}
	}
}
bool Osobnik::IsDone(int index) {  // Funkcja która sprawdza czy wszystkie zapytania zosta³y zrealizowanie. Je¿eli nie ma ju¿ zapytañ zwraca true i przypisuje index do zmiennej, inaczej zwraca false
		// Nale¿y przekazaæ aktualny index pêtli w której wykonoywana jest symulacja i usuwanie zapytañ.
	if (!EnquiryCounter) {
		Fitness = index;
		return true;
	}
	else if (index == DNALength) {
		Fitness = index;
		return true;
	}
	else return false;
	// W pêtli symulacyjnej uwzglêdniæ ¿e je¿eli po jakimœ indexie isDone zwróci³o true
}

void Osobnik::GenerateRandomDNA() {
	for (int i = 0; i < DNALength; i++) {
		DNA[i] = rand() % 2;
	}
}
std::vector<int> TranslateDNA(Osobnik x) {
	std::vector<int> xx;
	int y=0;  // Poprawiæ na CurrentFloor w przysz³oœci
	for (int i = 0; i < DNALength; i++) {
		if (x.DNA[i]) {
			if (y == MaxPietro) {
				xx.push_back(y);
			}
			else {
				y++;
				xx.push_back(y);
			}
		}
		else {
			if (y == 0) {  // Poprawiæ na MinPietro
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
void FitnessSymulation(std::vector<Osobnik> arr, std::vector<Zapytanie> newEnquiryVector) {

}
// Trzeba przekazaæ wektor z osobnikami przez referencjê, dokonuje on selekcji i zmniejsza iloœæ osobników o 50% (200 -> 100). Zwraca ten sam wektor z now¹ populacj¹.
void Selection(std::vector<Osobnik>& arr) {
	std::vector<Osobnik> newVector;
	PopulationSize = arr.size();
	while (PopulationSize) {
		Osobnik p1, p2;
		PopulationSize = arr.size();
		int RNumber = rand() % PopulationSize;
		p1 = arr[RNumber];
		arr.erase(arr.begin() + RNumber);
		PopulationSize = arr.size();
		RNumber = rand() % PopulationSize;
		p2 = arr[RNumber];
		arr.erase(arr.begin() + RNumber);
		if (p1.Fitness < p2.Fitness) {
			newVector.push_back(p1);
		}
		else if (p1.Fitness > p2.Fitness) {
			newVector.push_back(p2);
		}
		else if (p1.Fitness == p2.Fitness) {
			if (rand() % 2)newVector.push_back(p1);
			else newVector.push_back(p2);
		}
		PopulationSize = arr.size();
	}
	arr = newVector;
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
}
void Crossover(std::vector<Osobnik>& arr) { // Nale¿y przekazaæ vektor, zwraca ona 2 razy wiêkszy wektor z 50% starej populacji i 50% nowej
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
void SortFitness(std::vector<Osobnik>& arr) { // Nale¿y przekazaæ vektor, Funkcja sortuje vector pod wzglêdem Fitnesu osobników i przygotowuje go do funkcji Crossover, zwraca vektor posortoway
	sort(arr.begin(),
		arr.end(),
		[](const Osobnik& lhs, const Osobnik& rhs)
		{
			return lhs.Fitness < rhs.Fitness;
		});
}
void IsBest(std::vector<Osobnik> arr) { // Wywo³ywaæ po SortFitness
	if (arr[0].Fitness < BestOsobnik.Fitness) {
		BestOsobnik = arr[0];
	}
}
void CrossoverView() {
	
	else {
		int NumberOfGenerations;
		srand(time(NULL));
		std::vector<Osobnik> o(PopulationStartSize);
		for (int i = 0; i < PopulationStartSize; i++) {
			o[i].GenerateRandomDNA();
		}
	}

	/*std::cout << "Podaj liczbê generacji";
	std::cin >> NumberOfGenerations;
	for (int i = 0; i < NumberOfGenerations; i++) {
		if (i == 0) {
			for (int j = 0; j < o.size(); j++) {
				o[j].IsDone
			}
			SortFitness(o);
			IsBest(o);
		}
		std::cout << "Najlepszy obecny Fitness : " << o[0].Fitness << std::endl;
		std::cout << "Najlepszy Fitness ogólnie: " << BestOsobnik.Fitness << std::endl;
		Crossover(o);
		SortFitness(o);
		Selection(o);*/
}
// Trzeba zrobiæ funkcjê losuj¹c¹ w taki sposób ¿e po wylosowaniu danej liczby usuwa ona siê ze zbioru liczb które mo¿na wylosowaæ

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

