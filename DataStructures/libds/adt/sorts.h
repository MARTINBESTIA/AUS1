#pragma once

#include <libds/amt/implicit_sequence.h>
#include <libds/adt/queue.h>
#include <libds/adt/array.h>
#include <functional>
#include <cmath>
#include <algorithm>
#include <type_traits>

namespace ds::adt
{
    template <typename T>
    struct Sort
    {
    public:
        virtual void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) = 0;
        void sort(amt::ImplicitSequence<T>& is) { sort(is, [](const T& a, const T& b)->bool {return a < b; }); }
    };

    //----------

    template <typename T>
    class SelectSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class InsertSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class BubbleSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class QuickSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void quick(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max);
    };

    //----------

    template <typename T>
    class HeapSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class ShellSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&, int, std::string)> compare, int year, std::string gender);

    private:
        amt::ImplicitSequence<size_t> sedgewickSeq = {};
		size_t sedgewickSeqIndex = 0;
        void shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t k);
        void shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&, int, std::string)> compare, size_t k, int year, std::string gender);
    };

    //----------

    template <typename Key, typename T>
    class RadixSort :
        public Sort<T>
    {
        static_assert(std::is_integral_v<Key>, "Radix sort supports only integral types.");

    public:
        RadixSort();
        RadixSort(std::function<Key(const T&)> getKey);

        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        std::function<Key(const T&)> getKey_;
    };

    //----------

    template <typename T>
    class MergeSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void split(size_t n);
        void merge(std::function<bool(const T&, const T&)> compare, size_t n);

    private:
        ImplicitQueue<T>* queue1_ {nullptr};
        ImplicitQueue<T>* queue2_ {nullptr};
        ImplicitQueue<T>* mergeQueue_ {nullptr};
    };

    //----------

    template<typename T>
    void SelectSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void InsertSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        for (size_t i = 1; i < is.size(); ++i) {
            T tmp = is.access(i)->data_;
			size_t j = i;
            while (j > 0 && compare(tmp, is.access(j - 1)->data_)) 
            {
				is.access(j)->data_ = is.access(j - 1)->data_;
                --j;
            }
			is.access(j)->data_ = tmp;
        }
    }

    template<typename T>
    void BubbleSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void QuickSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        if (!is.isEmpty())
        {
            quick(is, compare, 0, is.size() - 1);
        }
    }

    template<typename T>
    void QuickSort<T>::quick(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void HeapSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void ShellSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        int k = 0;
        while (true) {
            size_t gap;
            if (k % 2 == 0) {
                gap = 9 * (1 << k) - 9 * (1 << (k / 2)) + 1;
            }
            else {
                gap = 8 * (1 << k) - 6 * (1 << ((k + 1) / 2)) + 1;
			}
			if (gap > is.size()) {
				break;
			}
			sedgewickSeq.insertLast().data_ = gap;
			sedgewickSeqIndex++;
			k++;
        }
        sedgewickSeqIndex--;
        //shell(is, compare, static_cast<size_t>(std::ceil(std::log10(is.size()))));
        shell(is, compare, sedgewickSeq.access(sedgewickSeqIndex)->data_);
    }

    template<typename T>
    void ShellSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&, int, std::string)> compare, int year, std::string gender)
    {
        int k = 0;
        while (true) {
            size_t gap;
            if (k % 2 == 0) {
                gap = 9 * (1 << k) - 9 * (1 << (k / 2)) + 1;
            }
            else {
                gap = 8 * (1 << k) - 6 * (1 << ((k + 1) / 2)) + 1;
            }
            if (gap > is.size()) {
                break;
            }
            sedgewickSeq.insertLast().data_ = gap;
            sedgewickSeqIndex++;
            k++;
        }
        sedgewickSeqIndex--;
        //shell(is, compare, static_cast<size_t>(std::ceil(std::log10(is.size()))), year, gender);
        shell(is, compare, sedgewickSeq.access(sedgewickSeqIndex)->data_, year, gender);
    }

    template<typename T>
    void ShellSort<T>::shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t k)
    {
        for (size_t d = 0; d < k; d++) {
            for (size_t i = d; i < is.size(); i++) {
                size_t j = i;
                while (j >= k && j - k >= d && compare(is.access(j)->data_, is.access(j - k)->data_)) {
					std::swap(is.access(j)->data_, is.access(j - k)->data_);
					j = j - k;
                }
            }
        }/*
        if (k > 1) {
			shell(is, compare, k - 1);
        }*/
        if (sedgewickSeqIndex > 0) {
			sedgewickSeqIndex--;
            shell(is, compare, sedgewickSeq.access(sedgewickSeqIndex)->data_);
        }

    }

    template<typename T>
    void ShellSort<T>::shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&, int, std::string)> compare, size_t k, int year, std::string gender)
    {
        for (size_t d = 0; d < k; d++) {
            for (size_t i = d; i < is.size(); i++) {
                size_t j = i;
                while (j >= k && j - k >= d && compare(is.access(j)->data_, is.access(j - k)->data_, year, gender)) {
                    std::swap(is.access(j)->data_, is.access(j - k)->data_);
                    j = j - k;
                }
            }
        }/*
        if (k > 1) {
            shell(is, compare, k - 1, year, gender);
        }*/
        if (sedgewickSeqIndex > 0) {
            sedgewickSeqIndex--;
            shell(is, compare, sedgewickSeq.access(sedgewickSeqIndex)->data_, year, gender);
        }
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort() :
        getKey_([](auto const& x) { return x; })
    {
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort(std::function<Key(const T&)> getKey) :
        getKey_(getKey)
    {
    }

    template<typename Key, typename T>
    void RadixSort<Key, T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::split(size_t n)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::merge(std::function<bool(const T&, const T&)> compare, size_t n)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }
}