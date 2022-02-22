#include "Algorytm.h"
#include "Zapytania.h"

extern const int DNALength;  // Sta�a d�ugo�� �a�cucha DNA
extern int maxFloor;
extern int minFloor; //Na przyszlosc do poprawienia liniki 49
extern std::vector<Zapytanie>Enquiries;
int GenerationAmount = 40;
const int MutationRate = 50; // Cz�stotliwo�� mutacji im wi�ksza tym mniejsza szansa na mutacje
const int PopulationStartSize = 200; // Wielko�� pocz�tkowa populacji
int PopulationSize = 0; // Obecna wielko�� populacji
Osobnik BestOsobnik;
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
		DNA[i] = rand() % 2;
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
			if (y == 0) {  // Poprawi� na MinPietro
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
void PrintInformations(std::vector<Osobnik> arr, Osobnik x, int generationC) { // Wywo�ywa� po sortFitness
	std::cout << "Najlepszy Fitness w tej generacji " << generationC <<" : " <<  arr[0].Fitness << std::endl;
	std::cout << "Najlepszy Fitness zawsze: " << x.Fitness << std::endl;
}
void FitnessSimulation(Osobnik& x, std::vector<Zapytanie> newEnquiryVector) {
	std::vector<int> CurrentF = TranslateDNA(x);
	std::vector<Zapytanie> Queue;
	int EnquirySize = newEnquiryVector.size();
	for (int i = 0; i < CurrentF.size(); i++) {
		for (int j = 0; j < EnquirySize; j++) {
			if (newEnquiryVector[j].MiejsceP == CurrentF[i]) {
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
			x.Fitness = i;
			break;
		}
		if(i==CurrentF.size()-1){
			x.Fitness = i;
			break;
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
void IsBest(std::vector<Osobnik> arr) { // Wywo�ywa� po SortFitness
	if (arr[0].Fitness < BestOsobnik.Fitness) {
		BestOsobnik = arr[0];
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
		IsBest(o);
		PrintInformations(o, BestOsobnik, NumberOfGenerations);
		while (NumberOfGenerations < GenerationAmount) {
			NumberOfGenerations++;
			Crossover(o);
			for (int i = 0; i < o.size(); i++) {
				o[i].Mutate();
			}
			for (int i = 0; i < o.size(); i++) {
				FitnessSimulation(o[i], newEnquiryVector);
			}
			Selection(o);
			SortFitness(o);
			IsBest(o);
			PrintInformations(o, BestOsobnik, NumberOfGenerations);
		}
		std::cout << std::endl;
		for (int i = 0; i < DNALength; i++) {
			moveQueueVector.push_back(BestOsobnik.DNA[i]);
		}
		for (int i = 0; i < DNALength; i++) {
			std::cout << BestOsobnik.DNA[i] << " ";
		}

}
void Testowa() {
	
	// Dodaj opcje wy�wietlania tej funkcji w menu
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


/*std::cout << "Podaj liczb� generacji";
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
	std::cout << "Najlepszy Fitness og�lnie: " << BestOsobnik.Fitness << std::endl;
	Crossover(o);
	SortFitness(o);
	Selection(o);*/