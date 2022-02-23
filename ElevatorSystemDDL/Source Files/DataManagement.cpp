#include "DataManagement.h"
const int ID = 0, startFloor = 0, endFloor = 0;

Data::Data() {
}
Data::~Data() {
}


void Data::addEnquiry(const int& ID, const int& startFloor, const int& endFloor, std::vector<Zapytanie>& newEnquiryVector) {
	Zapytanie enquiry(1);
	enquiry.setID(ID);
	enquiry.setMiejsceP(startFloor);
	enquiry.setMiejsceD(endFloor);
	newEnquiryVector.push_back(enquiry);
}
void Data::atoiCheckOutOfRange(const int quantity) const
{
	// Handle out of range errors from atoi
	if (INT_MAX == quantity || INT_MIN == quantity)
	{
		throw std::exception("atoi operation failed");
	}
}
void Data::parseLine(const std::string& currentLine, int& ID,int& startFloor,int& endFloor) const 
{
	static const int NEXT_CHAR = 1;         // 1 char after comma
	std::string endFloorStr = "";           // End floor string rep
	int firstCommaPos = std::string::npos;  // First comma pos    
	int secondCommaPos = std::string::npos; // Second comma pos
	std::string startFloorStr = "";         // Start floor string rep
	std::string IDStr = "";

	firstCommaPos = currentLine.find(",");
	secondCommaPos = currentLine.find(",", firstCommaPos + NEXT_CHAR);

	IDStr = currentLine.substr(0, firstCommaPos);

	ID = (atoi(IDStr.c_str()));

	static const int  END_POS_OFFSET = 2;
	int               secondStringEndPos = secondCommaPos - END_POS_OFFSET;

	startFloorStr = currentLine.substr(
		firstCommaPos + NEXT_CHAR,
		secondStringEndPos);
	startFloor = (atoi(startFloorStr.c_str()));

	endFloorStr = currentLine.substr(secondCommaPos + NEXT_CHAR);

	endFloor = (atoi(endFloorStr.c_str()));

	this->atoiCheckOutOfRange(ID);
	this->atoiCheckOutOfRange(startFloor);
	this->atoiCheckOutOfRange(endFloor);

};
void Data::loadEnquiryDataFromFile(std::vector<Zapytanie>& newEnquiryVector) {
	std::string currentLine = "";
	std::fstream currentFile(this->EnquiryDataFile.c_str(), std::ios::in);
	if (currentFile) {
		getline(currentFile, currentLine);
		while (!currentFile.eof()) {
			getline(currentFile, currentLine);
			if (currentLine != "") {
				int startFloor;
				int endFloor;
				int ID;
				this->parseLine(currentLine,ID,startFloor,endFloor);
				this->addEnquiry(ID, startFloor, endFloor, newEnquiryVector);
			}
		}
	}
	else
	{
		throw std::exception("ifstream operation failed!");
	}
}
void Data::setEnquiryDataFile(const std::string& dataFile) {
	this->EnquiryDataFile = dataFile;
}
void Data::runDefault(std::vector<Zapytanie>& newEnquiryVector) {
	this->setEnquiryDataFile("Enquiries.csv");
	this->loadEnquiryDataFromFile(newEnquiryVector);
	/*for (Zapytanie enquiryData : newEnquiryVector) {
		std::cout << enquiryData.ID << " " << enquiryData.MiejsceP << " " << enquiryData.MiejsceD << std::endl;
	}
			this->saveOutput();
	*/
}

void Data::saveOutput() {
	std::ofstream fileOut;
	fileOut.open("Output.txt");
	std::cout << "Hello" << std::endl;
	fileOut << "This is txt" << std::endl;
	fileOut.close();
}