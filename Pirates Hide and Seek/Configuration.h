#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

namespace cfg {

	struct key
	{
		std::string Left;
		std::string Right;
		key *Next = 0;
	};

	struct dictionaty
	{
		key* head = 0;
		key* tail = 0;
	};

	void add(dictionaty* configuration, std::string left, std::string right);
	bool ReadConfiguration(dictionaty* configuration, std::string filename);
	bool WriteConfiguration(dictionaty* configuration, std::string filename);
	bool GetParm(dictionaty* configuration, std::string s, std::string& result);
	bool GetParm(dictionaty* configuration, std::string s, int &result);
	bool SetParm(dictionaty* configuration, std::string s, int result);
	bool SetParm(dictionaty* configuration, std::string s, std::string result);
}
#endif

#define VariableName(stream,variable) stream<<#variable
