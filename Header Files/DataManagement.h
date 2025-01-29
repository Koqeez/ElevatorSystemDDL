#ifndef DATA_H 
#define DATA_H

#include <fstream>
#include <iostream>
#include <string>
#include "Zapytania.h"
#include "GlobalVariables.h"

class Data {

public:
	std::string EnquiryDataFile;
	
	Data();
	~Data();

	void loadEnquiryDataFromFile(std::vector<Zapytanie>&);
	void saveEnquiryDataToFile(std::vector<Zapytanie>&, std::string);
	void parseLine(const std::string& currentLine, int& ID,int& startFloor,int& endFloor)const;
	void atoiCheckOutOfRange(const int quantity) const;
	void addEnquiry(const int&,const int&,const int&,std::vector<Zapytanie>&);
	void setEnquiryDataFile(const std::string&);
	std::string getDataFile();
	void runDefault(std::vector<Zapytanie>&);
	void saveEnquiryOutput(std::vector<Zapytanie>& );

};

#endif