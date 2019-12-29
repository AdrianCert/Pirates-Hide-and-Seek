#include "Configuration.h"

namespace cfg {
	
	// Add a new key in configuration
	void add(dictionaty* configuration, std::string left, std::string right) {
		key* tmp = new key;
		tmp->Left = left;
		tmp->Right = right;
		tmp->Next = NULL;

		if (configuration->head == NULL)
		{
			configuration->head = tmp;
			configuration->tail = tmp;
		}
		else
		{
			configuration->tail->Next = tmp;
			configuration->tail = configuration->tail->Next;
		}
	}

	// Reading from the filename path the configuration
	// If filename don't exist that return false
	bool ReadConfiguration(dictionaty* configuration, std::string filename){
		std::fstream file;
		std::string left, right;
		file.open(filename.c_str());
		if (file.is_open()) {
			while (file >> left >> right) {
				add(configuration,left, right);
			}
			file.close();
			return true;
		}
		return false;
	}

	// Save in filename path the configuration
	// If filename don't exist that return false
	bool WriteConfiguration(dictionaty* configuration, std::string filename){
		key* tmp = configuration->head;
		std::fstream file;
		file.open(filename.c_str());
		if (file.is_open()) {
			bool ok = true;
			do {
				file << tmp->Left << " " << tmp->Right << std::endl;
				if (tmp->Next == NULL)
					ok = false;
				tmp = tmp->Next;
			} while (ok);
			file.close();
			return true;
		}
		return false;
	}

	// Overwriting the key "s" with result in confifiguration
	// If the key don't exist than will return false
	bool GetParm(dictionaty* configuration, std::string s, std::string& result){
		key* tmp = configuration->head;
		bool ok = true;
		do {
			if (s == tmp->Left) {
				result = tmp->Right;
				return true;
			}
			if (tmp->Next == NULL)
				ok = false;
			tmp = tmp->Next;
		}while(ok);
		return false;
	}

	// Overwriting the key "s" with result in confifiguration
	// If the key don't exist than will return false
	bool GetParm(dictionaty* configuration, std::string s, int& result){
		key* tmp = configuration->head;
		bool ok = true;
		do {
			if (s == tmp->Left) {
				result = std::stoi(tmp->Right);
				return true;
			}
			if (tmp->Next == NULL)
				ok = false;
			tmp = tmp->Next;
		} while (ok);
		return false;
	}

	// Overwriting the key "s" with result in confifiguration
	// If the key don't exist than will return false
	bool SetParm(dictionaty* configuration, std::string s, int result) {
		key* tmp = configuration->head;
		bool ok = true;
		do {
			if (s == tmp->Left) {
				tmp->Right = std::to_string(result);
				return true;
			}
			if (tmp->Next == NULL)
				ok = false;
			tmp = tmp->Next;
		} while (ok);
		return false;
	}

	// Overwriting the key "s" with result in confifiguration
	// If the key don't exist than will return false
	bool SetParm(dictionaty* configuration, std::string s, std::string result) {
		key* tmp = configuration->head;
		bool ok = true;
		do {
			if (s == tmp->Left) {
				tmp->Right = result;
				return true;
			}
			if (tmp->Next == NULL)
				ok = false;
			tmp = tmp->Next;
		} while (ok);
		return false;
	}
}