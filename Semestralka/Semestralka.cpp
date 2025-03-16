// Semestralka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "LevelOne.h"





int main()
{
	SetConsoleOutputCP(1252);
	LevelOne levelOne("2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv");
	auto containsStr = [](LevelOne& instance, const std::string& substr) -> bool {
		auto it = instance.getData().begin();
		auto end = instance.getData().end();
		while (it != end) {
			for (int i = 0; i < (*it).townName.length() - substr.length(); i++) {
				if ((*it).townName.substr(i, substr.length()) == substr) {
					return true;
				}
				
			}
			++it; // mozno skipuje posledny prvok
		}
		return false;
	};
	auto hasMaxResidents = [](LevelOne& instance, int residentsAmount, int year) -> bool {
		auto it = instance.getData().begin();
		auto end = instance.getData().end();
		while (it != end) {
			switch (year) {
			case 2020:
				return (*it).malePopulation2020 + (*it).femalePopulation2020 > residentsAmount;
				break;
			case 2021:
				return (*it).malePopulation2021 + (*it).femalePopulation2021 > residentsAmount;
				break;
			case 2022:
				return (*it).malePopulation2022 + (*it).femalePopulation2022 > residentsAmount;
				break;
			case 2023:
				return (*it).malePopulation2023 + (*it).femalePopulation2023 > residentsAmount;
				break;
			case 2024:
				return (*it).malePopulation2024 + (*it).femalePopulation2024 > residentsAmount;
				break;
			}
			++it;
		}
		return false;
	};
	auto hasMinResidents = [](LevelOne& instance, int residentsAmount, int year) -> bool {
		auto it = instance.getData().begin();
		auto end = instance.getData().end();
		while (it != end) {
			switch (year) {
			case 2020:
				return (*it).malePopulation2020 + (*it).femalePopulation2020 < residentsAmount;
				break;
			case 2021:
				return (*it).malePopulation2021 + (*it).femalePopulation2021 < residentsAmount;
				break;
			case 2022:
				return (*it).malePopulation2022 + (*it).femalePopulation2022 < residentsAmount;
				break;
			case 2023:
				return (*it).malePopulation2023 + (*it).femalePopulation2023 < residentsAmount;
				break;
			case 2024:
				return (*it).malePopulation2024 + (*it).femalePopulation2024 < residentsAmount;
				break;
			}
			++it;
		}
		return false;
		};


	return 0;
		
}
