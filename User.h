#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
class User
{
public:
	int ezWin = 0, medWin = 0, hardWin = 0;
	int ezTotal = 0, medTotal = 0, hardTotal = 0;
	int ezBest = 0, medBest = 0, hardBest = 0;
	std::string userName = "Default";
	std::string getEzWR();
	std::string getMedWR();
	std::string getHardWR();
	void save();
	void load();
	void reset();
	~User() {
		save();
	};
};
