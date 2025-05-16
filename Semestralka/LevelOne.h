#pragma once
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <sstream>
#include <libds/amt/explicit_hierarchy.h>
#include <libds/amt/hierarchy.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include "libds/adt/sorts.h"
#include "DuplicateFreeSSTable.h"


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

		bool operator!=(const Territorial_unit& other) const {
			return !(*this == other);
		}

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
	ds::amt::ImplicitSequence<Territorial_unit> dataFiltered;
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
	int sortYear = 0;
	std::string sortGender = "both";

	bool endProgram = false;

	DuplicateFreeSSTable<std::string, Territorial_unit*> communeTable = {};
	DuplicateFreeSSTable<std::string, Territorial_unit*> regionTable = {};
	DuplicateFreeSSTable<std::string, Territorial_unit*> geoPartTable = {};
	DuplicateFreeSSTable<std::string, Territorial_unit*> FedRepublicTable = {};

	
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
					auto& block = dataFiltered.insertLast();
					block.data_ = *it;
					//std::cout << (*it).unitName << " " << (*it).unitID << " " << (*it).regionID << std::endl;
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
					auto& block = dataFiltered.insertLast();
					block.data_ = *it;
					/*std::cout << (*it).unitName << " " << "<" << (*it).unitID << "> Male Population: ";
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
					std::cout << std::endl;*/
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
					auto& block = dataFiltered.insertLast();
					block.data_ = *it;
					//std::cout << (*it).unitName << " " << (*it).unitID << " " << (*it).regionID << std::endl;
				}
				++it;
				
			}
		};

		std::function<bool(const Territorial_unit&, const Territorial_unit&)> compareAlphabetical = [](const Territorial_unit& leftUnit, const Territorial_unit& rightUnit) -> bool {
			return leftUnit.unitName < rightUnit.unitName;
		};

		std::function<bool(const Territorial_unit&, const Territorial_unit&, int, std::string)> comparePopulation = [](const Territorial_unit& leftUnit, const Territorial_unit& rightUnit, int year, std::string gender) -> bool {
			int leftPopulation = 0;
			int rightPopulation = 0;
			if (year == 2020 && gender == "male") {
				leftPopulation = leftUnit.malePopulation2020;
				rightPopulation = rightUnit.malePopulation2020;
			}
			if (year == 2021 && gender == "male") {
				leftPopulation = leftUnit.malePopulation2021;
				rightPopulation = rightUnit.malePopulation2021;
			}
			if (year == 2022 && gender == "male") {
				leftPopulation = leftUnit.malePopulation2022;
				rightPopulation = rightUnit.malePopulation2022;
			}
			if (year == 2023 && gender == "male") {
				leftPopulation = leftUnit.malePopulation2023;
				rightPopulation = rightUnit.malePopulation2023;
			}
			if (year == 2024 && gender == "male") {
				leftPopulation = leftUnit.malePopulation2024;
				rightPopulation = rightUnit.malePopulation2024;
			}
			if (year == 2020 && gender == "female") {
				leftPopulation = leftUnit.femalePopulation2020;
				rightPopulation = rightUnit.femalePopulation2020;
			}
			if (year == 2021 && gender == "female") {
				leftPopulation = leftUnit.femalePopulation2021;
				rightPopulation = rightUnit.femalePopulation2021;
			}
			if (year == 2022 && gender == "female") {
				leftPopulation = leftUnit.femalePopulation2022;
				rightPopulation = rightUnit.femalePopulation2022;
			}
			if (year == 2023 && gender == "female") {
				leftPopulation = leftUnit.femalePopulation2023;
				rightPopulation = rightUnit.femalePopulation2023;
			}
			if (year == 2024 && gender == "female") {
				leftPopulation = leftUnit.femalePopulation2024;
				rightPopulation = rightUnit.femalePopulation2024;
			}
			if (year == 2020 && gender == "both") {
				leftPopulation = leftUnit.malePopulation2020 + leftUnit.femalePopulation2020;
				rightPopulation = rightUnit.malePopulation2020 + rightUnit.femalePopulation2020;
			}
			if (year == 2021 && gender == "both") {
				leftPopulation = leftUnit.malePopulation2021 + leftUnit.femalePopulation2021;
				rightPopulation = rightUnit.malePopulation2021 + rightUnit.femalePopulation2021;
			}
			if (year == 2022 && gender == "both") {
				leftPopulation = leftUnit.malePopulation2022 + leftUnit.femalePopulation2022;
				rightPopulation = rightUnit.malePopulation2022+ rightUnit.femalePopulation2022;
			}
			if (year == 2023 && gender == "both") {
				leftPopulation = leftUnit.malePopulation2023 + leftUnit.femalePopulation2023;
				rightPopulation = rightUnit.malePopulation2023 + rightUnit.femalePopulation2023;
			}
			if (year == 2024 && gender == "both") {
				leftPopulation = leftUnit.malePopulation2024 + leftUnit.femalePopulation2024;
				rightPopulation = rightUnit.malePopulation2024 + rightUnit.femalePopulation2024;
			}
			return leftPopulation < rightPopulation;
		};
		
		ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>* getIteratorNode() {
		ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>* rootPtr = dataHierarchy.accessRoot();

		int residentsAmount = 0;
		std::string nameSubstr = "";
		std::cout << "ITERATOR MENU:" << std::endl;
		std::cout << "-r --- runs the iterations from set root" << std::endl;
		std::cout << "s n --- jumps to son at nth index. Example s 3 jumps to son at 3rd index" << std::endl;
		std::cout << "-f --- jumps to father" << std::endl;
		std::cout << "-end --- end program" << std::endl;
		
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
			if (command == "-end") {
				this->endProgram = true;
				return nullptr;
			}
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
		int chooseComparator() {
			std::cout << "CHOOSE COMPARATOR MENU:" << std::endl;
			std::cout << "comp popul [year] [type] --- sorts unit based on population count. [year] = {2020, 2021, 2022, 2023, 2024}. [type] = {male, female, both}" << std::endl;
			std::cout << "comp alpha --- sorts units alphabetically, Example comp alpha" << std::endl;
			std::string command;
			std::getline(std::cin, command);
			std::vector<std::string> result;
			std::stringstream ss(command);
			std::string token;
			while (std::getline(ss, token, ' ')) {
				result.push_back(token);
			}
			while (true) {
				if (result.size() != 2 && result.size() != 4) {
					std::cout << "Invalid command" << std::endl;
					continue;
				}
				if (result.size() == 2) {
					if (result[0] == "comp" && result[1] == "alpha") {
						return 1;
					}
					else {
						std::cout << "Invalid command" << std::endl;
						continue;
					}
				}
				if (result.size() == 4) {
					if (result[0] != "comp" && result[1] != "popul") {
						std::cout << "Invalid command" << std::endl;
						continue;
					}
					try {
						this->sortYear = std::stoi(result[2]);
					}
					catch (std::exception e) {
						std::cout << "Invalid year" << std::endl;
						this->sortYear = 0;
						continue;
					}
					if (this->sortYear < 2020 || this->sortYear > 2024) {
						std::cout << "Invalid year" << std::endl;
						continue;
					}
				}
				if (result[3] != "male" && result[3] != "female" && result[3] != "both") {
					std::cout << "Invalid type" << std::endl;
					continue;
				}
				else {
					this->sortGender = result[3];
					return 2;
				}
			}
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
				std::string str;
				int year = 0;
				while (true) {
					std::cout << "Enter year: " << std::endl;
					std::getline(std::cin, str);
					try {
						year = std::stoi(str);
					}
					catch (std::exception e) {
						std::cout << "Invalid year" << std::endl;
						continue;
					}
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

		void sort(int compNumber) {
			if (compNumber == 1) {
				ds::adt::ShellSort<Territorial_unit> shellSort;
				shellSort.sort(this->dataFiltered, this->compareAlphabetical);
			}
			else if (compNumber == 2) {
				ds::adt::ShellSort<Territorial_unit> shellSort;
				shellSort.sort(this->dataFiltered, this->comparePopulation, this->sortYear, this->sortGender);
			}
			else {
				std::cout << "Invalid comparator" << std::endl;
			}
		}

		void writeOutDataFiltered() {
			std::cout << "Filtered data:" << std::endl;
			for (int i = 0; i < this->dataFiltered.size(); i++) {
				std::cout << this->dataFiltered.access(i)->data_.unitName << ", Unit ID: " << this->dataFiltered.access(i)->data_.unitID << std::endl <<
					" Male Population 2020: " << this->dataFiltered.access(i)->data_.malePopulation2020 << ", Female Population 2020: " << this->dataFiltered.access(i)->data_.femalePopulation2020 << std::endl <<
					" Male Population 2021: " << this->dataFiltered.access(i)->data_.malePopulation2021 << ", Female Population 2021: " << this->dataFiltered.access(i)->data_.femalePopulation2021 << std::endl <<
					" Male Population 2022: " << this->dataFiltered.access(i)->data_.malePopulation2022 << ", Female Population 2022: " << this->dataFiltered.access(i)->data_.femalePopulation2022 << std::endl <<
					" Male Population 2023: " << this->dataFiltered.access(i)->data_.malePopulation2023 << ", Female Population 2023: " << this->dataFiltered.access(i)->data_.femalePopulation2023 << std::endl <<
					" Male Population 2024: " << this->dataFiltered.access(i)->data_.malePopulation2024 << ", Female Population 2024: " << this->dataFiltered.access(i)->data_.femalePopulation2024
					<< std::endl;
			}
			this->dataFiltered.clear();
		};

		void writeUnitInfo(std::string pKey, std::string pTable) {
			DuplicateFreeSSTable<std::string, Territorial_unit*>* table = nullptr;
			if (pTable == "communeTable") {
				table = &this->communeTable;
			}
			else if (pTable == "regionTable") {
				table = &this->regionTable;
			}
			else if (pTable == "geoPartTable") {
				table = &this->geoPartTable;
			}
			else if (pTable == "fedRepublicTable") {
				table = &this->FedRepublicTable;
			}
			if (table->contains(pKey)) {
				std::cout << table->find(pKey)->unitID << " " << table->find(pKey)->unitName << std::endl <<
					" Male Population 2020: " << table->find(pKey)->malePopulation2020 << ", Female Population 2020: " << table->find(pKey)->femalePopulation2020 << std::endl <<
					" Male Population 2021: " << table->find(pKey)->malePopulation2021 << ", Female Population 2021: " << table->find(pKey)->femalePopulation2021 << std::endl <<
					" Male Population 2022: " << table->find(pKey)->malePopulation2022 << ", Female Population 2022: " << table->find(pKey)->femalePopulation2022 << std::endl <<
					" Male Population 2023: " << table->find(pKey)->malePopulation2023 << ", Female Population 2023: " << table->find(pKey)->femalePopulation2023 << std::endl <<
					" Male Population 2024: " << table->find(pKey)->malePopulation2024 << ", Female Population 2024: " << table->find(pKey)->femalePopulation2024 << std::endl;
			}
			else {
				std::cout << "Key not found" << std::endl;
			}
		}
		

		ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator getIterator(ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>& currentRoot) {
			ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator it(&this->dataHierarchy, &currentRoot);
			return it;
		};

		ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator getNullptrIterator() {
			ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator it(&this->dataHierarchy, nullptr);
			return it;
		};

		std::string getPredValue() { return this->predValue; };

		bool getEndedProgram() { return this->endProgram; };

		int getPredPopulationValue() { return this->predResidentsValue; };

		int getPredYearValue() { return this->predYearValue; };

		TerritoryType getPredTypeValue() { return this->predTypeValue; };

		void filterOnPredicates(const std::string& str, int maxResidents, int minResidents, int year);

		ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>* getRoot() { return this->dataHierarchy.accessRoot(); };

		DuplicateFreeSSTable<std::string, Territorial_unit*>& getCommuneTable() { return this->communeTable; };

		~LevelOne();

};

