#pragma once
#include <string>
#include <vector>
class LevelOne
{


	private:
		struct Town {
			int townID;
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
			std::string townName;

			Town(int ptownID, int pmalePopulation2020, int pfemalePopulation2020, int pmalePopulation2021, int pfemalePopulation2021, int pmalePopulation2022,
				int pfemalePopulation2022, int pmalePopulation2023, int pfemalePopulation2023, int pmalePopulation2024, int pfemalePopulation2024, const std::string& ptownName) :
				townID(ptownID), malePopulation2020(pmalePopulation2020), femalePopulation2020(pfemalePopulation2020), malePopulation2021(pmalePopulation2021),
				femalePopulation2021(pfemalePopulation2021), malePopulation2022(pmalePopulation2022), femalePopulation2022(pfemalePopulation2022),
				malePopulation2023(pmalePopulation2023), femalePopulation2023(pfemalePopulation2023), malePopulation2024(pmalePopulation2024),
				femalePopulation2024(pfemalePopulation2024), townName(ptownName) {}
		}; 
		std::vector<Town> data;
		std::vector<Town> filteredData;
	
	public:
		LevelOne(std::string pfilePath2020, std::string pfilePath2021, std::string pfilePath2022, std::string pfilePath2023, std::string pfilePath2024);
		std::vector<Town>& getData() { return this->data; };
		void addToFiltered(const Town& pTown);
		~LevelOne();


};

