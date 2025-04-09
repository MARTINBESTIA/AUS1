// Semestralka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "LevelOne.h"
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>





int main()
{
	SetConsoleOutputCP(1252);
	{
		LevelOne levelOne("2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv", "uzemie.csv", "obce.csv");
		levelOne.filter(levelOne.getData().begin(), levelOne.getData().end(), levelOne.containsStr, "öf");
	}
	_CrtDumpMemoryLeaks();
	return 0;
		
}
