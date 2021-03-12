#include "User.h"

std::string User::getEzWR() {
	if (ezTotal == 0) return std::to_string(0) + "% WR";
	std::stringstream stream;
	std::string ret;
	stream << std::setprecision(2) << std::fixed << ((float)ezWin / ezTotal) * 100;
	stream >> ret;
	return ret + "% WR";
};
std::string User::getMedWR() {
	if (medTotal == 0) return std::to_string(0) + "% WR";
	std::stringstream stream;
	std::string ret;
	stream << std::setprecision(2) << std::fixed << ((float)medWin / medTotal) * 100;
	stream >> ret;
	return ret + "% WR";
};
std::string User::getHardWR() {
	if (hardTotal == 0) return std::to_string(0) + "% WR";
	std::stringstream stream;
	std::string ret;
	stream << std::setprecision(2) << std::fixed << ((float)hardWin / hardTotal) * 100;
	stream >> ret;
	return ret + "% WR";
};

void User::save() {

	std::ofstream saveData;
	char* buf = nullptr;
	size_t sz = 0;



	if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr) {
		std::string temp((std::string)buf + "\\Minesweeper");
		if (CreateDirectoryA(temp.c_str(), NULL) == 0 && GetLastError() == ERROR_PATH_NOT_FOUND) {
			std::cout << temp << std::endl;
			std::cout << GetLastError() << std::endl;
			std::cout << "ERROR_PATH_NOT_FOUND" << std::endl;
			return;
		};
		saveData.open((std::string)buf + "\\Minesweeper\\data.dat");
		std::cout << (std::string)buf + "\\Minesweeper\\data.dat" << std::endl;
	}
	else {
		std::cout << "Error saving file to buffer" << std::endl;
		return;
	}
	saveData << userName << std::endl;
	saveData << ezWin << std::endl;
	saveData << medWin << std::endl;
	saveData << hardWin << std::endl;
	saveData << ezTotal << std::endl;
	saveData << medTotal << std::endl;
	saveData << hardTotal << std::endl;
	free(buf);
	saveData.close();
}

void User::load() {
	std::ifstream saveData;

	char* buf = nullptr;
	size_t sz = 0;

	if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr) {
		saveData.open((std::string)buf + "\\minesweeper\\data.dat");
	}
	else {
		std::cout << "Error saving file to buffer" << std::endl;
		return;
	}

	if (!saveData.is_open()) return;

	std::string line;
	getline(saveData,line);
	userName = line;
	line.clear();
	getline(saveData, line);
	ezWin = std::stoi(line);
	line.clear();
	getline(saveData, line);
	medWin = std::stoi(line);
	line.clear();
	getline(saveData, line);
	hardWin = std::stoi(line);
	line.clear();
	getline(saveData, line);
	ezTotal = std::stoi(line);
	line.clear();
	getline(saveData, line);
	medTotal = std::stoi(line);
	line.clear();
	getline(saveData, line);
	hardTotal = std::stoi(line);
	line.clear();
	free(buf);
	saveData.close();
}

void User::reset() {
	userName = "Default";
	ezWin = 0, medWin = 0, hardWin = 0;
	ezTotal = 0, medTotal = 0, hardTotal = 0;
}