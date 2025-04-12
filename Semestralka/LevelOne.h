#pragma once
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <libds/amt/explicit_hierarchy.h>
#include <libds/amt/hierarchy.h>


class LevelOne
{
private:

	struct Territorial_unit {
		int unitID;
		int malePopulation2020;
		int femalePopulation2020;
		int malePopulation2021;
		int femalePopulation2021;
		int malePopulation2022;
		int femalePopulation2022;
		int malePopulation2023;
		int femalePopulation2023;
		int malePopulation2024;
		int femalePopulation2024;
		std::string unitName;
		std::string regionID;

		bool operator==(const Territorial_unit& pUnit) const {
			return unitID == pUnit.unitID && malePopulation2020 == pUnit.malePopulation2020 && malePopulation2021 == pUnit.malePopulation2021
				&& malePopulation2022 == pUnit.malePopulation2022 && malePopulation2023 == pUnit.malePopulation2023 && malePopulation2024 == pUnit.malePopulation2024
				&& femalePopulation2020 == pUnit.femalePopulation2020 && femalePopulation2021 == pUnit.femalePopulation2021
				&& femalePopulation2022 == pUnit.femalePopulation2022 && femalePopulation2023 == pUnit.femalePopulation2023 && femalePopulation2024 == pUnit.femalePopulation2024
				&& unitName == pUnit.unitName && regionID == pUnit.regionID;
		};

		Territorial_unit() = default;

		Territorial_unit(int ptownID, int pmalePopulation2020, int pfemalePopulation2020, int pmalePopulation2021, int pfemalePopulation2021, int pmalePopulation2022,
			int pfemalePopulation2022, int pmalePopulation2023, int pfemalePopulation2023, int pmalePopulation2024, int pfemalePopulation2024, const std::string& ptownName, const std::string& pRegionID) :
			unitID(ptownID), malePopulation2020(pmalePopulation2020), femalePopulation2020(pfemalePopulation2020), malePopulation2021(pmalePopulation2021),
			femalePopulation2021(pfemalePopulation2021), malePopulation2022(pmalePopulation2022), femalePopulation2022(pfemalePopulation2022),
			malePopulation2023(pmalePopulation2023), femalePopulation2023(pfemalePopulation2023), malePopulation2024(pmalePopulation2024),
			femalePopulation2024(pfemalePopulation2024), unitName(ptownName), regionID(pRegionID) {}

		
		
	
	};

	std::vector<Territorial_unit> data;
	std::vector<Territorial_unit> filteredData;
	ds::amt::MultiWayExplicitHierarchy<Territorial_unit> dataHierarchy;

	enum TerritoryType {
		Commune,
		Region,
		FedRepublic,
		GeoPart,
		Country
	};

	std::string predValue;
	int predResidentsValue = 0;
	int predYearValue = 0;
	TerritoryType predTypeValue;

	
	
	public:
		LevelOne(std::string pfilePath2020, std::string pfilePath2021, std::string pfilePath2022, std::string pfilePath2023, std::string pfilePath2024, std::string uzemie, std::string obce);

		std::function<bool(const Territorial_unit&, TerritoryType)> hasType = [](const Territorial_unit& town, TerritoryType type) -> bool {
			TerritoryType tType;
			if (town.unitID == 0) tType = Country;
			else if (town.unitID > 0 && town.unitID <= 3) tType = GeoPart;
			else if (town.unitID > 10 && town.unitID < 100) tType = FedRepublic;
			else if (town.unitID > 100 && town.unitID <= 1000) tType = Region;
			else tType = Commune;

			return type == tType;

		};

		std::function<bool(const Territorial_unit&, const std::string&)> containsStr = [](const Territorial_unit& town, const std::string& substr) -> bool {
			if (substr.length() > town.unitName.length()) return false;
			for (int i = 0; i <= town.unitName.length() - substr.length(); i++) {
				if (town.unitName.substr(i, substr.length()) == substr) {
					return true;
				}
			}
			return false;
		};

		std::function<bool(const Territorial_unit&, int residentsAmount, int year)> hasMaxResidents = [](const Territorial_unit& town, int residentsAmount, int year) -> bool {
			switch (year) {
			case 2020:
				return town.malePopulation2020 + town.femalePopulation2020 < residentsAmount;
				break;
			case 2021:
				return town.malePopulation2021 + town.femalePopulation2021 < residentsAmount;
				break;
			case 2022:
				return town.malePopulation2022 + town.femalePopulation2022 < residentsAmount;
				break;
			case 2023:
				return town.malePopulation2023 + town.femalePopulation2023 < residentsAmount;
				break;
			case 2024:
				return town.malePopulation2024 + town.femalePopulation2024 < residentsAmount;
				break;
			}
			return false;
		};

		std::function<bool(const Territorial_unit&, int residentsAmount, int year)> hasMinResidents = [](const Territorial_unit& town, int residentsAmount, int year) -> bool {
			switch (year) {
			case 2020:
				return town.malePopulation2020 + town.femalePopulation2020 > residentsAmount;
				break;
			case 2021:
				return town.malePopulation2021 + town.femalePopulation2021 > residentsAmount;
				break;
			case 2022:
				return town.malePopulation2022 + town.femalePopulation2022 > residentsAmount;
				break;
			case 2023:
				return town.malePopulation2023 + town.femalePopulation2023 > residentsAmount;
				break;
			case 2024:
				return town.malePopulation2024 + town.femalePopulation2024 > residentsAmount;
				break;
			}
			return false;
		};
		

		std::function<void(Territorial_unit&, Territorial_unit&)> addResidents = [](Territorial_unit& father, Territorial_unit& son) -> void {
			father.malePopulation2020 += son.malePopulation2020;
			father.femalePopulation2020 += son.femalePopulation2020;
			father.malePopulation2021 += son.malePopulation2021;
			father.femalePopulation2021 += son.femalePopulation2021;
			father.malePopulation2022 += son.malePopulation2022;
			father.femalePopulation2022 += son.femalePopulation2022;
			father.malePopulation2023 += son.malePopulation2023;
			father.femalePopulation2023 += son.femalePopulation2023;
			father.malePopulation2024 += son.malePopulation2024;
			father.femalePopulation2024 += son.femalePopulation2024;
	
		};

		template <typename Iterator, typename Predicate>
		void filter(Iterator begin, Iterator end, Predicate predicate, std::string str) {
			Iterator it = begin;
			while (it != end) {
				if (predicate(*it, str)) {
					filteredData.push_back(*it);
					std::cout << (*it).unitName << " " << (*it).unitID << " " << (*it).regionID << std::endl;
				}
				++it;
			}
		};
		
		template <typename Iterator, typename Predicate>
		void filter(Iterator begin, Iterator end, Predicate predicate, int residents, int year) {
			Iterator it = begin;
			while (it != end) {
				if (predicate(*it, residents, year)) {
					filteredData.push_back(*it);
					std::cout << (*it).unitName << " " << "<" << (*it).unitID << "> Male Population: ";
					switch (year) {
						case (2020):
						std::cout << (*it).malePopulation2020;
						break;
						case (2021):
							std::cout << (*it).malePopulation2021;
							break;
						case (2022):
							std::cout << (*it).malePopulation2022;
							break;
						case (2023):
							std::cout << (*it).malePopulation2023;
							break;
						case (2024):
							std::cout << (*it).malePopulation2024;
							break;
					}
					std::cout  << " Female population: ";
					switch (year) {
						case (2020):
							std::cout << (*it).femalePopulation2020;
							break;
						case (2021):
							std::cout << (*it).femalePopulation2021;
							break;
						case (2022):
							std::cout << (*it).femalePopulation2022;
							break;
						case (2023):
							std::cout << (*it).femalePopulation2023;
							break;
						case (2024):
							std::cout << (*it).femalePopulation2024;
							break;
					}
					std::cout << std::endl;
				}
				++it;
			}
		};

		template <typename Iterator, typename Predicate>
		void filter(Iterator begin, Iterator end, Predicate predicate, TerritoryType pType) {
			Iterator it = begin;
			while (it != end) {
				if (predicate(*it, pType)) {
					filteredData.push_back(*it);
					std::cout << (*it).unitName << " " << (*it).unitID << " " << (*it).regionID << std::endl;
				}
				++it;
				
			}
		};
		
		ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>* getIteratorNode() {
		ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>* rootPtr = dataHierarchy.accessRoot();

		int residentsAmount = 0;
		std::string nameSubstr = "";
		std::cout << "ITERATOR MENU:" << std::endl;
		std::cout << "-r --- runs the iterations from set root" << std::endl;
		std::cout << "s n --- jumps to son at nth index. Example s 3 jumps to son at 3rd index" << std::endl;
		std::cout << "-f --- jumps to father" << std::endl;
		
		while (true) {
			std::cout << " ------------------------------------------------" << std::endl;
			std::cout << "Current root: " << (*rootPtr).data_.unitName << std::endl;
			std::cout << "Root sons: " << std::endl;
			for (int i = 0; i < (*rootPtr).sons_->size(); i++) {
				std::cout << "At index " << i << " : " << dataHierarchy.accessSon((*rootPtr), i)->data_.unitName << std::endl;
			}
			std::cout << "Write command: " << std::endl;
			std::string command;
			std::getline(std::cin, command);
			if (command == "-r") {
				return rootPtr;
			}
			else if (command[0] == 's') {
				int index = std::stoi(command.substr(2, command.size() - 2));
				if (index < 0 || index >= (*rootPtr).sons_->size()) {
					std::cout << "Invalid index" << std::endl;
					continue;
				}
				rootPtr = dataHierarchy.accessSon((*rootPtr), index);
				
			}
			else if (command == "-f") {
				if (dataHierarchy.accessParent((*rootPtr)) == nullptr) {
					std::cout << "No father" << std::endl;
					continue;
				}
				rootPtr = dataHierarchy.accessParent((*rootPtr));
			}
			else {
				std::cout << "Invalid command" << std::endl;
				continue;
			}
		}

		return rootPtr;
		
		};
		
		int choosePredicate() {

			std::cout << "CHOOSE PREDICATE MENU:" << std::endl;
			std::cout << "pmax value --- sets predicate to hasMaxResidents, Example pmax 3000" << std::endl;
			std::cout << "pmin value --- sets predicate to hasMinResidents, Example pmin 3000" << std::endl;
			std::cout << "pstr value --- sets predicate to containsStr, Example pstr dorf" << std::endl;
			std::cout << "ptype value --- sets predicate to hasType, ptype Region" << std::endl;
			std::cout << "ptype key values are: Commune, Region, FedRepublic, GeoPart, Country" << std::endl;
			std::string command;
			std::getline(std::cin, command);
			int manMixValue = 0;
			while (true) {
				if (command.substr(0, 4) == "pmax") {
					int residents = std::stoi(command.substr(5, command.size() - 5));
					this->predResidentsValue = residents;
					manMixValue = 3;
					break;
				}
				if (command.substr(0, 4) == "pmin") {
					int residents = std::stoi(command.substr(5, command.size() - 5));
					this->predResidentsValue = residents;
					manMixValue = 4;
					break;
				}
				if (command.substr(0, 4) == "pstr") {
					std::string nameSubstr = command.substr(5, command.size() - 5);
					this->predValue = nameSubstr;
					return 1;
				}
				if (command.substr(0, 5) == "ptype") {
					std::string typeStr = command.substr(6, command.size() - 6);
					if (typeStr == "Commune") this->predTypeValue = Commune;
					else if (typeStr == "Region") this->predTypeValue = Region;
					else if (typeStr == "FedRepublic") this->predTypeValue = FedRepublic;
					else if (typeStr == "GeoPart") this->predTypeValue = GeoPart;
					else if (typeStr == "Country") this->predTypeValue = Country;
					else {
						std::cout << "Invalid type" << std::endl;
						continue;
					}
					return 2;
				}
			}
			if (command.substr(0, 4) == "pmax" || command.substr(0, 4) == "pmin") {
				std::cout << "Enter year from 2020 to 2024" << std::endl;
				int year = 0;
				while (true) {
					std::cout << "Enter year: " << std::endl;
					std::cin >> year;
					if (year < 2020 || year > 2024) {
						std::cout << "Invalid year" << std::endl;
						continue;
					}
					this->predYearValue = year;
					return manMixValue;
				}
			}
			return 0;
		};

		ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator getIterator(ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>& currentRoot) {
			ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator it(&this->dataHierarchy, &currentRoot);
			return it;
		};

		ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator getNullptrIterator() {
			ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator it(&this->dataHierarchy, nullptr);
			return it;
		};

		std::string getPredValue() { return this->predValue; };

		int getPredPopulationValue() { return this->predResidentsValue; };

		int getPredYearValue() { return this->predYearValue; };

		TerritoryType getPredTypeValue() { return this->predTypeValue; };

		void filterOnPredicates(const std::string& str, int maxResidents, int minResidents, int year);

		std::vector<Territorial_unit>& getData() { return this->data; };

		ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>* getRoot() { return this->dataHierarchy.accessRoot(); };

		~LevelOne();

};

