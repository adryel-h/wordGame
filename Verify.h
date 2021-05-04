#pragma once
#include <iostream>
#include "Dictionary.h"
using namespace std;
class Verify
{
private:
	Dictionary* dict;
public:
	Verify(Dictionary* p);
	bool validstart(string word);
	bool validtarget(string word, int length);
	bool validsize(int size);
	bool validmove(string prevword, string curword);
};

