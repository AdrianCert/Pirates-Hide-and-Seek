#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

struct key
{
	std::string Left;
	std::string Right;
	key *Next = 0;
};

class dictionaty
{
private:
	key* head, * tail;
public:
	dictionaty();
	void add(std::string left, std::string right);
	bool ReadConfiguration(std::string filename);
	bool WriteConfiguration(std::string filename);
	bool GetParm(std::string s, std::string& result);
	bool GetParm(std::string s, int &result);
};
#endif

#define VariableName(stream,variable) stream<<#variable
