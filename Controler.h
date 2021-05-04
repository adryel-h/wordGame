#pragma once
#include "Dictionary.h"
#include "Graph.h"
#include <random>
#include <time.h>
class Controler
{
private:
	Dictionary* dict;
public:
	Controler();
	string getTarget(string startword,int diff);
	string getStart(int size);
	int getHint(string prevword, string targetword, vector<string>& hintwords);
	vector<string> AutomaticMode(string startword, string targetword, int* moves);
	Dictionary* getaddressdict();
	~Controler();
};

