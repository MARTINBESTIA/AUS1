// Semestralka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "LevelOne.h"
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>
#include <libds/amt/hierarchy.h>





int main()
{
	SetConsoleOutputCP(1252);
	{
		LevelOne levelOne("2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv", "uzemie.csv", "obce.csv");
		auto it = levelOne.getIterator(levelOne.getIteratorNode());
		int choice = levelOne.choosePredicate();
		switch (choice) {
			case 1:
				levelOne.filter(it, levelOne.getNullptrIterator(),levelOne.containsStr, levelOne.getPredValue());
				break;
			case 2:
				levelOne.filter(it, levelOne.getNullptrIterator(), levelOne.hasType, levelOne.getPredTypeValue());
				break;
			case 3:
				levelOne.filter(it, levelOne.getNullptrIterator(), levelOne.hasMaxResidents, levelOne.getPredPopulationValue(), levelOne.getPredYearValue());
				break;
			case 4:
				levelOne.filter(it, levelOne.getNullptrIterator(), levelOne.hasMinResidents, levelOne.getPredPopulationValue(), levelOne.getPredYearValue());
				break;
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
		
}
