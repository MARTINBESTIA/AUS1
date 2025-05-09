#pragma once
#include <libds/adt/abstract_data_type.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>

template<typename K, typename T>
class DuplicateFreeSSTable : public ds::adt::SortedSequenceTable<K, ds::adt::ImplicitList<T>*>
{
	using TableType = ds::adt::SortedSequenceTable<K, ds::adt::ImplicitList<T>*>;
	using ListType = ds::adt::ImplicitList<T>;

public:
	DuplicateFreeSSTable() : TableType() {}
	DuplicateFreeSSTable(const DuplicateFreeSSTable& other) : TableType(other) {}

	void insert(K key, T data)
	{
		using TableItemType = ds::adt::TableItem<K, ds::adt::ImplicitList<T>*>;
		TableItemType* tableItem;

		if (this->isEmpty())
		{
			tableItem = &this->getSequence()->insertFirst().data_;
		}
		else
		{
			using BlockType = typename TableType::BlockType;
			BlockType* blok = nullptr;
			if (this->tryFindBlockWithKey(key, 0, this->size(), blok))
			{
				blok->data_.data_->insertLast(data);
				return;
			}
			tableItem = key > blok->data_.key_
				? &this->getSequence()->insertAfter(*blok).data_
				: &this->getSequence()->insertBefore(*blok).data_;
		}

		tableItem->key_ = key;
		tableItem->data_->insertLast(data);
	}
};

