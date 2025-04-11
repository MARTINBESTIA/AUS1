#include "LevelOne.h"
#include <fstream>
#include <iostream>
#include <sstream>



LevelOne::LevelOne(std::string pfilePath2020, std::string pfilePath2021, std::string pfilePath2022, std::string pfilePath2023, std::string pfilePath2024, std::string pUzemie, std::string pObce)
{
	// beginning level 1
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
										name, "");
		//std::cout << this->data.back().townName << " " << this->data.back().townID << " " << this->data.back().malePopulation2020 << " " << this->data.back().femalePopulation2020 << " " << this->data.back().malePopulation2021 << " " << this->data.back().femalePopulation2021 << " " << this->data.back().malePopulation2022 << " " << this->data.back().femalePopulation2022 << " " << this->data.back().malePopulation2023 << " " << this->data.back().femalePopulation2023 << " " << this->data.back().malePopulation2024 << " " << this->data.back().femalePopulation2024 << std::endl;
	}
	
	file_2020.close();
	file_2021.close();
	file_2022.close();
	file_2023.close();
	file_2024.close();

	// end level 1 start level 2

	std::ifstream file_obce(pObce);
	std::ifstream file_uzemie(pUzemie);
	if (!file_obce.is_open() || !file_uzemie.is_open()) {
		std::cout << "failed file reading." << std::endl;
		return;
	}

	ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>& root = dataHierarchy.emplaceRoot();
	root.data_ = Territorial_unit(0,0,0,0,0,0,0,0,0,0,0,"Austria","<AT0>");
	ds::amt::MultiWayExplicitHierarchy<Territorial_unit>::PreOrderHierarchyIterator it(&this->dataHierarchy, &root);

	std::string name;
	std::string unit_id;
	std::string region_id;
	int index = 0;
	while (!file_uzemie.eof()) {
		std::getline(file_uzemie, line);
		std::istringstream uzemie_ss(line);
		std::getline(uzemie_ss, name, ';');
		std::getline(uzemie_ss, unit_id, ';');
		if (unit_id.size() == 5) {
			int index = stoi(unit_id.substr(3, 1)) - 1;
			dataHierarchy.emplaceSon(root, index).data_ = Territorial_unit(stoi(unit_id.substr(3, 1)),0,0,0,0,0,0,0,0,0,0,name,unit_id);
			//std::cout << dataHierarchy.accessSon(root, index)->data_.unitName << std::endl;
		}
		if (unit_id.size() == 6) {
			int fatherIndex = stoi(unit_id.substr(3, 1)) - 1;
			int sonIndex = stoi(unit_id.substr(4, 1)) - 1;
			auto* father = dataHierarchy.accessSon(root, fatherIndex);
			dataHierarchy.emplaceSon(*father, sonIndex).data_ = Territorial_unit(stoi(unit_id.substr(3, 2)), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, name, unit_id);
		}
		if (unit_id.size() == 7) {
			int preFatherIndex = stoi(unit_id.substr(3, 1)) - 1;
			int fatherIndex = stoi(unit_id.substr(4, 1)) - 1;
			int sonIndex = stoi(unit_id.substr(5, 1)) - 1;
			if (sonIndex < 0) sonIndex = 0;
			auto* preFather = dataHierarchy.accessSon(root, preFatherIndex);
			auto* father = dataHierarchy.accessSon(*preFather, fatherIndex);
			dataHierarchy.emplaceSon(*father, sonIndex).data_ = Territorial_unit(stoi(unit_id.substr(3, 3)), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, name, unit_id);
			//std::cout << dataHierarchy.accessSon(*father, sonIndex)->data_.unitName << " " << dataHierarchy.accessSon(*father, sonIndex)->data_.unitID << std::endl;
		}
	}
	int sequenceIndex = 0;
	int hierarchyIndex = 0;
	std::string region_id_mark = "AT111";
	while (!file_obce.eof()) {
		if (sequenceIndex >= this->data.size()) break;
		std::getline(file_obce, line);
		std::istringstream uzemie_ss(line);
		std::getline(uzemie_ss, name, ';');
		std::getline(uzemie_ss, unit_id, ';');
		std::getline(uzemie_ss, region_id, ';');
		if (this->data[sequenceIndex].unitName != name) {
			std::cout << "nesedi meno " << this->data[sequenceIndex].unitName << " " << name << std::endl;
		}/*
		if (this->data[0].regionID != region_id) {
			std::cout << "nesedi regionID " << this->data[0].regionID << " " << region_id << std::endl;
		}*/
		if (region_id_mark != region_id) {
			region_id_mark = region_id;
			hierarchyIndex = 0;
		}

		int prePreFatherIndex = stoi(region_id.substr(2, 1)) - 1;
		int preFatherIndex = stoi(region_id.substr(3, 1)) - 1;
		int FatherIndex = stoi(region_id.substr(4, 1)) - 1;
		if (FatherIndex < 0) FatherIndex = 0;
		auto* prePreFather = dataHierarchy.accessSon(root, prePreFatherIndex);
		auto* preFather = dataHierarchy.accessSon(*prePreFather, preFatherIndex);
		auto* father = dataHierarchy.accessSon(*preFather, FatherIndex);

		this->data[sequenceIndex].regionID = region_id;
		dataHierarchy.emplaceSon(*father, hierarchyIndex).data_ = this->data[sequenceIndex];

		addResidents(father->data_, this->data[sequenceIndex]);
		addResidents(preFather->data_, this->data[sequenceIndex]);
		addResidents(prePreFather->data_, this->data[sequenceIndex]);
		addResidents(root.data_, this->data[sequenceIndex]);

		sequenceIndex++;
		hierarchyIndex++;
		//std::cout << sequenceIndex << std::endl;
	}
	/*
	auto* prePreFather = dataHierarchy.accessSon(root, 2);
	auto* preFather = dataHierarchy.accessSon(*prePreFather, 3);
	std::cout << preFather->data_.femalePopulation2024 + preFather->data_.malePopulation2024 << " " << preFather->data_.unitName << std::endl;*/
	file_obce.close();
	file_uzemie.close();
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
			std::cout << (*it).unitName << " " << "<" << (*it).unitID << ">" << std::endl;
		}
		++it; 
	}
}
/*
ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<Territorial_unit>>::PreOrderHierarchyIterator LevelOne::getHierarchyIterator()
{
	return ;
}*/


LevelOne::~LevelOne()
{
	this->data.clear();
	this->filteredData.clear();
	this->data.shrink_to_fit();
	this->filteredData.shrink_to_fit();
	

	//std::cout << this->data.capacity()  << " " << this->filteredData.capacity() << std::endl;
	
}
