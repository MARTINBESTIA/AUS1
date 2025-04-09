#pragma once
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <libds/amt/explicit_hierarchy.h>

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

	

	
	public:
		LevelOne(std::string pfilePath2020, std::string pfilePath2021, std::string pfilePath2022, std::string pfilePath2023, std::string pfilePath2024, std::string uzemie, std::string obce);

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
		
		template <typename Iterator, typename Predicate>
		void filter(Iterator begin, Iterator end, Predicate predicate, std::string str) {
			for (Iterator it = begin; it != end; it++) {
				if (predicate(*it, str)) {
					filteredData.push_back(*it);
					std::cout << (*it).unitName << " " << "<" << (*it).unitID << "> Male Population: " 
					<< (*it).malePopulation2020 + (*it).malePopulation2021 + (*it).malePopulation2022 + (*it).malePopulation2023 + (*it).malePopulation2024 << " Female population: "
					<< (*it).femalePopulation2020 + (*it).femalePopulation2021 + (*it).femalePopulation2022 + (*it).femalePopulation2023 + (*it).femalePopulation2024 << std::endl;
				}
			}
		};
		
		template <typename Iterator, typename Predicate>
		void filter(Iterator begin, Iterator end, Predicate predicate, int residents, int year) {
			for (Iterator it = begin; it != end; it++) {
				if (predicate(*it, residents, year)) {
					std::cout << (*it).unitName << " " << "<" << (*it).unitID << "> Male Population: "
						<< (*it).malePopulation2020 + (*it).malePopulation2021 + (*it).malePopulation2022 + (*it).malePopulation2023 + (*it).malePopulation2024 << " Female population: "
						<< (*it).femalePopulation2020 + (*it).femalePopulation2021 + (*it).femalePopulation2022 + (*it).femalePopulation2023 + (*it).femalePopulation2024 << std::endl;
				}

			}
		};

		void filterOnPredicates(const std::string& str, int maxResidents, int minResidents, int year);

		std::vector<Territorial_unit>& getData() { return this->data; };

		~LevelOne();

};

