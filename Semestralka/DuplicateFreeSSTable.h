#pragma once
#include <libds/adt/abstract_data_type.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>

template<typename K, typename T>
class DuplicateFreeSSTable : public ds::adt::SortedSequenceTable<K, T>
{
    using Base = ds::adt::SortedSequenceTable<K, T>;
    using DuplicateTableType = ds::adt::SortedSequenceTable<K, ds::adt::ImplicitList<T*>*>;
    using ListType = ds::adt::ImplicitList<T>;
    using BlockType = typename Base::BlockType;
private:
    DuplicateTableType duplicates = {};

public:
    DuplicateFreeSSTable() = default;
    void insert(const K& key, T data) override
    {
        ds::adt::TableItem<K, T>* tableItem;

        if (this->isEmpty())
        {
            tableItem = &this->getSequence()->insertFirst().data_;
        }
        else
        {
            BlockType* blok = nullptr;
            if (this->tryFindBlockWithKey(key, 0, this->size(), blok))
            {
                //std::cout << "duplicita najdena" << std::endl;
                if (duplicates.contains(key)) {
                    duplicates.find(key)->insertLast(&data);
                }
                else {
                    duplicates.insert(key, new ds::adt::ImplicitList<T*>());
                    duplicates.find(key)->insertLast(&data);
                }
            }
            tableItem = key > blok->data_.key_
                ? &this->getSequence()->insertAfter(*blok).data_
                : &this->getSequence()->insertBefore(*blok).data_;
        }

        tableItem->key_ = key;
        tableItem->data_ = data;
    }
	~DuplicateFreeSSTable()
	{
		for (auto& item : duplicates)
		{
			delete item.data_;
		}
	}
	
};

