#pragma once


#include <complexities/complexity_analyzer.h>
#include <libds/adt/table.h>
#include <random>
#include <vector>
#include "../Semestralka/DuplicateFreeSSTable.h"

namespace ds::utils
{
	/**
	 * @brief Common base for table analyzers.
	 */
	template<class Table>
	class TableAnalyzer : public ComplexityAnalyzer<Table>
	{
	protected:
		explicit TableAnalyzer(const std::string& name);

	protected:
		void growToSize(Table& structure, size_t size) override;

		size_t getRandomIndex() const;
		int getRandomData() const;
		std::vector<int> insertedKeys_ = {};

	private:
		std::default_random_engine rngData_;
		std::default_random_engine rngIndex_;
		size_t index_;
		int data_;
	};

	/**
	 * @brief Analyzes complexity of an insertion at the beginning.
	 */
	template<class Table>
	class TableInsertAnalyzer : public TableAnalyzer<Table>
	{
	public:
		explicit TableInsertAnalyzer(const std::string& name);
	protected:
		void executeOperation(Table& structure) override;
	};
	/**
	 * @brief Analyzes complexity of an erasure at the beginning.
	 */
	template<class Table>
	class TableFindAnalyzer : public TableAnalyzer<Table>
	{
	public:
		explicit TableFindAnalyzer(const std::string& name);
	protected:
		void executeOperation(Table& structure) override;
	};

	class TablesAnalyzer : public CompositeAnalyzer

	{
	public:
		TablesAnalyzer();
	};

	template<class Table>
	inline TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) : TableAnalyzer<Table>(name)
	{

	}
	
	template<class Table>
	inline void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
	{
		auto data = this->getRandomData();
		auto key = this->getRandomData();
		structure.insert(key, data);
		insertedKeys_.push_back(key);
	}

	template<class Table>
	inline TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name) : TableAnalyzer<Table>(name)
	{

	}

	template<class Table>
	inline void TableFindAnalyzer<Table>::executeOperation(Table& structure)
	{
		auto key = insertedKeys_.back();
		insertedKeys_.pop_back();
		structure.find(key);
	}

	template<class Table>
	TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
		ComplexityAnalyzer<Table>(name),
		rngData_(144),
		rngIndex_(144),
		index_(0),
		data_(0)
	{
		ComplexityAnalyzer<Table>::registerBeforeOperation([this](Table& table)
			{
				std::uniform_int_distribution<size_t> indexDist(0, table.size() - 1);
				index_ = indexDist(rngIndex_);
				data_ = rngData_();
			});
	}


	template<class Table>
	inline void TableAnalyzer<Table>::growToSize(Table& structure, size_t size)
	{
		const size_t toInsert = size - structure.size();
		for (size_t i = 0; i < toInsert; ++i)
		{
			auto key = rngData_();    
			auto value = rngData_(); 
			structure.insert(key, value);
			insertedKeys_.push_back(key);
		}
	}

	template<class Table>
	inline size_t TableAnalyzer<Table>::getRandomIndex() const
	{
		return index_;
	}

	template<class Table>
	inline int TableAnalyzer<Table>::getRandomData() const
	{
		return data_;
	}

	inline TablesAnalyzer::TablesAnalyzer() :
		CompositeAnalyzer("Tables")
	{
		this->addAnalyzer(std::make_unique<TableInsertAnalyzer<DuplicateFreeSSTable<int, int>>>("DuplicateFreeSSTable-insert"));
		this->addAnalyzer(std::make_unique<TableFindAnalyzer<DuplicateFreeSSTable<int, int>>>("DuplicateFreeSSTable-find"));
	}

}
