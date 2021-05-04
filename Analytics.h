#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <set>


using namespace std;
class Analytics
{
private:
	ofstream of;
public:
	void write(string username, string sword, string tword, string start_time, string end_time,int hints, vector<string> words, int usermoves, int compmoves);
	void write(string& username, string& sword, string& tword, string start_time, string end_time);
	int getUniqueWords(string username);
	double getExtraData(string username);
};

