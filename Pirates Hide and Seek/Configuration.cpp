
#include "Configuration.h"

dictionaty::dictionaty() {
	head = NULL;
	tail = NULL;
}

void dictionaty::add(std::string left, std::string right) {
	key* tmp = new key;
	tmp->Left = left;
	tmp->Right = right;
	tmp->Next = NULL;

	if (head == NULL)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tail->Next = tmp;
		tail = tail->Next;
	}
}

bool dictionaty::ReadConfiguration(std::string filename){
	std::fstream file;
	std::string left, right;
	file.open(filename.c_str());
	if (file.is_open()) {
		while (file >> left >> right) {
			add(left, right);
		}
		file.close();
		return true;
	}
	return false;
}

bool dictionaty::WriteConfiguration(std::string filename){
	return true;
}

bool dictionaty::GetParm(std::string s, std::string& result){
	key* tmp = this->head;
	do {
		if (s == tmp->Left) {
			result = tmp->Right;
			return true;
		}
		tmp = tmp->Next;
	} while (tmp->Next != NULL);
	return false;
}

bool dictionaty::GetParm(std::string s, int& result){
	key* tmp = this->head;
	do {
		if (s == tmp->Left) {
			result = std::stoi(tmp->Right);
			return true;
		}
		tmp = tmp->Next;
	} while (tmp->Next != NULL);
	return false;
}