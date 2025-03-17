#include "LevelOne.h"
#include <fstream>
#include <iostream>
#include <sstream>
LevelOne::LevelOne(std::string pfilePath2020, std::string pfilePath2021, std::string pfilePath2022, std::string pfilePath2023, std::string pfilePath2024)
{

	this->data = {};
	this->filteredData = {};
	std::ifstream file_2020(pfilePath2020);
	std::ifstream file_2021(pfilePath2021);
	std::ifstream file_2022(pfilePath2022);
	std::ifstream file_2023(pfilePath2023);
	std::ifstream file_2024(pfilePath2024);
	if (!file_2020.is_open() || !file_2021.is_open() || !file_2022.is_open() || !file_2023.is_open() || !file_2024.is_open()) {
		std::cout << "failed file reading." << std::endl;
		return;
	}
	std::string line;
	for (int i = 0; i < 12; i++) {
		std::getline(file_2020, line);
		std::getline(file_2021, line);
		std::getline(file_2022, line);
		std::getline(file_2023, line);
		std::getline(file_2024, line);
	}
	while (true) {
		int malePopulation2020 = 0;
		int femalePopulation2020 = 0;
		int malePopulation2021 = 0;
		int femalePopulation2021 = 0;
		int malePopulation2022 = 0;
		int femalePopulation2022 = 0;
		int malePopulation2023 = 0;
		int femalePopulation2023 = 0;
		int malePopulation2024 = 0;
		int femalePopulation2024 = 0;
		int townID = 0;
		std::string name;
		std::string slice;


		std::getline(file_2020, line);
		std::istringstream iss_2020(line);
		std::getline(file_2021, line);
		std::istringstream iss_2021(line);
		std::getline(file_2022, line);
		std::istringstream iss_2022(line);
		std::getline(file_2023, line);
		std::istringstream iss_2023(line);
		std::getline(file_2024, line);
		std::istringstream iss_2024(line);

		std::getline(iss_2020, slice, ';');
		name = slice;
		if (name == "Nicht klassifizierbar") break;
		std::getline(iss_2020, slice, ';');
		townID = stoi(slice.substr(1, slice.length() - 2));
		std::getline(iss_2020, slice, ';');
		malePopulation2020 = stoi(slice);
		std::getline(iss_2020, slice, ';');
		femalePopulation2020 = stoi(slice);

		std::getline(iss_2021, slice, ';');
		name = slice;
		if (name == "Nicht klassifizierbar") break;
		std::getline(iss_2021, slice, ';');
		townID = stoi(slice.substr(1, slice.length() - 2));
		std::getline(iss_2021, slice, ';');
		malePopulation2021 = stoi(slice);
		std::getline(iss_2021, slice, ';');
		femalePopulation2021 = stoi(slice);

		std::getline(iss_2022, slice, ';');
		name = slice;
		if (name == "Nicht klassifizierbar") break;
		std::getline(iss_2022, slice, ';');
		townID = stoi(slice.substr(1, slice.length() - 2));
		std::getline(iss_2022, slice, ';');
		malePopulation2022 = stoi(slice);
		std::getline(iss_2022, slice, ';');
		femalePopulation2022 = stoi(slice);

		std::getline(iss_2023, slice, ';');
		name = slice;
		if (name == "Nicht klassifizierbar") break;
		std::getline(iss_2023, slice, ';');
		townID = stoi(slice.substr(1, slice.length() - 2));
		std::getline(iss_2023, slice, ';');
		malePopulation2023 = stoi(slice);
		std::getline(iss_2023, slice, ';');
		femalePopulation2023 = stoi(slice);

		std::getline(iss_2024, slice, ';');
		name = slice;
		if (name == "Nicht klassifizierbar") break;
		std::getline(iss_2024, slice, ';');
		townID = stoi(slice.substr(1, slice.length() - 2));
		std::getline(iss_2024, slice, ';');
		malePopulation2024 = stoi(slice);
		std::getline(iss_2024, slice, ';');
		femalePopulation2024 = stoi(slice);

		this->data.emplace_back(townID, malePopulation2020, femalePopulation2020, 
										malePopulation2021, femalePopulation2021, 
										malePopulation2022, femalePopulation2022,
										malePopulation2023, femalePopulation2023,
										malePopulation2024, femalePopulation2024,
										name);
		//std::cout << this->data.back().townName << " " << this->data.back().townID << " " << this->data.back().malePopulation2020 << " " << this->data.back().femalePopulation2020 << " " << this->data.back().malePopulation2021 << " " << this->data.back().femalePopulation2021 << " " << this->data.back().malePopulation2022 << " " << this->data.back().femalePopulation2022 << " " << this->data.back().malePopulation2023 << " " << this->data.back().femalePopulation2023 << " " << this->data.back().malePopulation2024 << " " << this->data.back().femalePopulation2024 << std::endl;
	}
	


	file_2020.close();
	file_2021.close();
	file_2022.close();
	file_2023.close();
	file_2024.close();
}




void LevelOne::filterOnPredicates(const std::string& str, int maxResidents, int minResidents, int year)
{
	this->filteredData.clear();
	auto it = this->data.begin();
	auto end = this->data.end();
	while (it != end) {
		if (this->containsStr(*(it), str) && this->hasMaxResidents(*(it), maxResidents, year) && this->hasMinResidents(*(it), minResidents, year))
		{
			this->filteredData.push_back(*it);
			std::cout << (*it).townName << " " << "<" << (*it).townID << ">" << std::endl;
		}
		++it; // mozno skipuje posledny
	}
}


LevelOne::~LevelOne()
{
	this->data.clear();
}
