#pragma once
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
using namespace std;

class Dictionary
{
public:
	Dictionary();
	unordered_set<string> getdict(int size);
	bool find(string word);
	string randomWord(int size);
private:
	unordered_map<unsigned int, unordered_set<std::string>> dict;
};

