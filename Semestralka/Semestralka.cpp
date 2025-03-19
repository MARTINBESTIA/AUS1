// Semestralka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "LevelOne.h"





int main()
{
	SetConsoleOutputCP(1252);
	LevelOne levelOne("2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv");
	levelOne.filter(levelOne.getData().begin(), levelOne.getData().end(), levelOne.hasMinResidents, 3000,2021);
	return 0;
		
}
