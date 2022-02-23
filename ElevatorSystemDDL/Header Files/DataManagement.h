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
	void parseLine(const std::string& currentLine, int& ID,int& startFloor,int& endFloor)const;
	void atoiCheckOutOfRange(const int quantity) const;
	void addEnquiry(const int&,const int&,const int&,std::vector<Zapytanie>&);
	void setEnquiryDataFile(const std::string&);
	void runDefault(std::vector<Zapytanie>&);
	void saveOutput();
};

#endif