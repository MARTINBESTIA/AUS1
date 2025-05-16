#include <iostream>
#include <Windows.h>
#include "LevelOne.h"
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>
#include <libds/amt/hierarchy.h>


int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	{
		LevelOne levelOne("2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv", "uzemie.csv", "obce.csv");
		while (true) {
			std::cout << "Zadaj príkaz na vykonávanie: " << std::endl;
			std::cout << "-1 --- Prechádzaj hierarchiou" << std::endl;
			std::cout << "-2 --- Vyhľadaj informácie o tabuľke na základe názvu: " << std::endl;
			std::cout << "-3 --- Ukonči program: " << std::endl;
			std::string command = "";
			std::getline(std::cin, command);
			if (command == "-3") {
				std::cout << "Program ended." << std::endl;
				break;
			}
			else if (command == "-1") {
				while (true) {
					auto it = levelOne.getIterator(*levelOne.getIteratorNode());
					if (levelOne.getEndedProgram()) {
						std::cout << "Program ended." << std::endl;
						break;
					}
					int predChoice = levelOne.choosePredicate();
					int compChoice = levelOne.chooseComparator();
					switch (predChoice) {
					case 1:
						levelOne.filter(it, levelOne.getNullptrIterator(), levelOne.containsStr, levelOne.getPredValue());
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
					levelOne.sort(compChoice);
					levelOne.writeOutDataFiltered();
				}
			}
			else if (command == "-2") {
				std::cout << "Zadaj kluc od tabulky a tabulku, od ktorej chces vyhladat inforamcie, -End ukonci program. " << std::endl;
				std::cout << "Nazvy tabuliek su nasledovne: {communeTable, regionTable, geoPartTable, fedRepublicTable}" << std::endl;
				while (true) {
					std::string key;
					std::string table;
					std::cout << "Zadaj nazov uzemnej jednotky:" << std::endl;
					std::getline(std::cin, key);
					if (key == "-End") break;
					std::cout << "Zadaj nazov tabulky v ktorej hladat" << std::endl;
					std::getline(std::cin, table);
					if (table != "communeTable" && table != "regionTable" && table != "geoPartTable" && table != "fedRepublicTable") {
						std::cout << "invalid table name" << std::endl;
						continue;
					}
					levelOne.writeUnitInfo(key, table);
				}
			}
			else {
				std::cout << "invalid command" << std::endl;
			}
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
		
}
