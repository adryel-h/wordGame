#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include "Controler.h"
#include "Verify.h"
#include "Analytics.h"
#include <chrono>
#include <ctime>
using namespace std;
class UserInterface
{
public:
	void load();
	void printtrans(vector<string> result);
};

