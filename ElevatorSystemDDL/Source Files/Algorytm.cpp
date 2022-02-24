#include "Algorytm.h"
#include "GlobalVariables.h"

int DNALength = 200;  // Sta�a d�ugo�� �a�cucha DNA	
int GenerationAmount = 100;
int MutationRate = 100; // Cz�stotliwo�� mutacji im wi�ksza tym mniejsza szansa na mutacje
int PopulationStartSize = 200; // Wielko�� pocz�tkowa populacji
int PopulationSize = 0; // Obecna wielko�� populacji
int MaxZapytan = 10;
int FitnessScaleMax = 1;
int FitnessScaleMin = 0;

Osobnik BestOsobnik;
Osobnik BestOsobnik2;
void generateDNAToFile(int amount, std::string fileName);
void transferDNAToFile(std::vector<Osobnik> vec, std::string fileName);
void deleteFile(std::string fileName);
std::vector<Osobnik> readDNAFromFile(int amount, std::string fileName);
void saveAlgorithmDataToFile(std::string fileName, std::string enquiriesFileName, int currGeneration, Osobnik x, Osobnik Best, int DNAL, int popStartSize, int mutationChance, int genAmount,
	int minFitness, int maxFitness, int maxEnquiriesInElevator, int enquiriesAmount, int maxF, int minF, std::string addInfo);

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
void PrintInformations(std::vector<Osobnik> arr, Osobnik x, int generationC, double previousFitness) { // Wywo�ywa� po sortFitness
	if(previousFitness != x.Fitness){
		std::cout << "Najlepszy Fitness w " << generationC << " Generacji: " << arr[0].Fitness << " Ilosc ruchow: " << arr[0].MovesAmount << " ";
		std::cout << "Najlepszy Fitness zawsze to: " << x.Fitness << " Ilosc ruchow: " << x.MovesAmount << std::endl;
	}
	else {
		std::cout << "Najlepszy Fitness w " << generationC << " Generacji: " << arr[0].Fitness << " Ilosc ruchow: " << arr[0].MovesAmount << std::endl;
	}
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
		double previousBest = 0;
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
		PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
		while (NumberOfGenerations < GenerationAmount) {
			NumberOfGenerations++;
			previousBest = BestOsobnik.Fitness;
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
			PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
		}
		std::cout << std::endl;

		for (int move : BestOsobnik.DNA) {
			moveQueueVector.push_back(move);
			std::cout << move << " ";
		}
}
void AlgorithmConfiguration() {
	std::cout << "Wpisz dlugosc DNA(200): ";
	std::cin >> DNALength;
	std::cout << "Wpisz poczatkowa wielkosc populacji(200): ";
	std::cin >> PopulationStartSize;
	std::cout << "Wpisz szanse na mutacje[im wiekszy tym mniejsza szansa](100): ";
	std::cin >> MutationRate;
	std::cout << "Wpisz ilosc generacji(100): ";
	std::cin >> GenerationAmount;
	std::cout << "Wpisz minimalny Fitness(0): ";
	std::cin >> FitnessScaleMin;
	std::cout << "Wpisz maksymalny Fitness(1): ";
	std::cin >> FitnessScaleMax;
}
int AlgorithmPopulationSize() {
	std::cout << "Wpisz poczatkowa wielkosc populacji: ";
	std::cin >> PopulationStartSize;
	return PopulationStartSize;
}


// POWTORZENIE ALGORYTMOW Z PARAMETRAMI WINDY - JEZELI MOZNA TO ZCALIC W JEDNA FUNKCJE - MAX FLOOR ZASTEPOWANY CAPACITY WINDY KTORA BEDZIE UZYWANA
void AlgorithmObliczania(std::vector<Zapytanie> newEnquiryVector, std::vector<int>& moveQueueVector, int ElevatorCapacity) {
	int NumberOfGenerations = 0;
	double previousBest = 0;
	srand(time(NULL));
	std::vector<Osobnik> o(PopulationStartSize);
	for (int i = 0; i < PopulationStartSize; i++) {
		o[i].GenerateRandomDNA();
	}
	for (int i = 0; i < o.size(); i++) {
		FitnessSimulationWithElevator(o[i], newEnquiryVector, ElevatorCapacity);
	}
	SortFitness(o);
	IsBest(o[0], BestOsobnik);
	PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
	while (NumberOfGenerations < GenerationAmount) {
		NumberOfGenerations++;
		previousBest = BestOsobnik.Fitness;
		Crossover(o);
		for (int i = o.size() / 10; i < o.size(); i++) {
			o[i].Mutate();
		}
		for (int i = 0; i < o.size(); i++) {
			InvertingWrongDNA(o[i]);
		}
		for (int i = 0; i < o.size(); i++) {
			FitnessSimulationWithElevator(o[i], newEnquiryVector,ElevatorCapacity);
		}
		Selection(o);
		SortFitness(o);
		IsBest(o[0], BestOsobnik);
		PrintInformations(o, BestOsobnik, NumberOfGenerations, previousBest);
	}
	std::cout << std::endl;

	for (int move : BestOsobnik.DNA) {
		moveQueueVector.push_back(move);
		std::cout << move << " ";
	}
}
void FitnessSimulationWithElevator(Osobnik& x, std::vector<Zapytanie> newEnquiryVector, int ElevatorCapacity_a) {
	std::vector<int> CurrentF = TranslateDNA(x);
	std::vector<Zapytanie> Queue;
	int EnquirySize = newEnquiryVector.size();
	for (int i = 0; i < CurrentF.size(); i++) {
		for (int j = 0; j < EnquirySize; j++) {
			if (newEnquiryVector[j].MiejsceP == CurrentF[i]) {
				if (Queue.size() >= ElevatorCapacity_a) {
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
			x.Fitness = InvertFitness(NormalizingFitness(i, DNALength, 0));
			break;
		}
		if (i == CurrentF.size() - 1) {
			x.MovesAmount = i;
			// a = InvertFitness(a);
			x.Fitness = InvertFitness(NormalizingFitness(i, DNALength, 0));
			break;
		}
	}
}
void SymulationFromFile(std::vector<Zapytanie> newEnquiryVector ,std::vector<int>& moveQueueVector, int ElevatorCapacity) {
	int NumberOfGenerations = 0;
	double previousBest = 0;
	srand(time(NULL));
	std::vector<Osobnik> o;
	o = readDNAFromFile(PopulationStartSize, "er");
	for (int i = 0; i < o.size(); i++) {
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
		for (int i = o.size() / 10; i < o.size(); i++) {
			o[i].Mutate();
		}
		for (int i = 0; i < o.size(); i++) {
			InvertingWrongDNA(o[i]);
		}
		for (int i = 0; i < o.size(); i++) {
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

void generateDNAToFile(int amount, std::string fileName) { // Przekazujesz ilo�� Osobnik�w dla ilu ma by� wygenerowane DNA(amount) fileName to nazwa pliku jaki ma by� utworzony, albo append do jakiego.
	std::vector<Osobnik> x(amount);
	for (int i = 0; i < amount; i++) {
		x[i].GenerateRandomDNA();
	}
	transferDNAToFile(x, fileName);
}
void transferDNAToFile(std::vector<Osobnik> vec, std::string fileName) { // Nie wywo�uj tej funkcji samej. Wywo�aj generateDNAToFile. 
	// Funkcja jest stworzona tak �e je�eli istnieje ju� plik z danymi o takiej samej nazwie to usuwa jego zawarto�ci i generuje nowe DNA
	// Pierwsze dwie linijki w wygenerowanym pliku to w kolejno�ci d�ugo�� wygenerowanego DNA a nast�pnie ilo�� wygenerowanych.
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
void deleteFile(std::string fileName) { // Funkcja do usuwania pliku, nale�y przekaza� nazw� i rozszerzenie
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
std::vector<Osobnik> readDNAFromFile(int amount, std::string fileName) { // Nale�y przekaza� nazw� pliku oraz ilo�� osobnik�w dla ilu ma by� pobrane DNA. D�ugo�� DNA pobierana jest z DNALength
	std::vector<Osobnik> x;  // Funckja zwr�ci vektor o odpowiedniej d�ugo�ci(amount) i DNALenght takim jak w algorytm.cpp
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
			MyFile << "D�ugo�� DNA: " << DNAL << " Populacja Pocz�tkowa: " << popStartSize << " Cz�stotliwo�� Mutacji: " << mutationChance << " Ilo�� Generacji: " << genAmount <<
				" Minimalny Fitness: " << minFitness << " Maksymalny Fitness: " << maxFitness << std::endl;
			MyFile << "ZAPYTANIA" << std::endl;
			MyFile << "Maksymalna Ilo�� Zapyta� w Windzie: " << maxEnquiriesInElevator << " Ilo�� Zapyta�: " << enquiriesAmount << " Minimalne Mo�liwe Pi�tro: " << minF << " Maksymalne Mo�liwe Pi�tro" <<
				maxF << std::endl;
			MyFile << "LISTA ZAPYTA�" << std::endl;
			std::fstream* enq = new std::fstream();
			enq->open(enquiriesFileName);
			if (enq->is_open()) {
				std::string temp;
				while (getline(*enq, temp)) {
					MyFile << temp << std::endl;
				}
			}
			else MyFile << "NIE UDA�O SI� WCZYTA� ZAPYTA�" << std::endl;
			delete enq;
			MyFile << std::endl;
		}
		MyFile << "Aktualna Generacja: " << currGeneration << " Najlepszy Fitness: " << x.Fitness << " Najlepsza Ilo�� Ruch�w: " << x.MovesAmount << std::endl;
		MyFile << "Najlepszy Fitness Zawsze: " << Best.Fitness << " Najlepsza Ilo�� Ruch�w Zawsze: " << Best.MovesAmount << std::endl;
		MyFile << "Najlepsze DNA: ";
		for (int i : Best.DNA) {
			MyFile << i;
		}
		MyFile.close();
	}
	else std::cout << "NIE UDALO SIE OTWORZYC PLIKU" << std::endl;
}