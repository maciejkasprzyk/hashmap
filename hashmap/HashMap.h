#ifndef HASHMAP_H
#define HASHMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <forward_list>
#include <vector>
#include <functional>


#define PRIME 31

template<typename ValueType>
class HashMap {
public:
    using key_type = std::string;
    using mapped_type = ValueType;
    using value_type = std::pair<key_type, mapped_type>;
    using size_type = std::size_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using list = std::forward_list<value_type>;
    using list_iterator = typename list::const_iterator;
    using vectorOfLists = std::vector<list>;

    class ConstIterator;

    friend class ConstIterator;

    class Iterator;

    using iterator = Iterator;
    using const_iterator = ConstIterator;

private:

    size_type capacity;
    size_type itemsInsertedCount{0};
    vectorOfLists table;

public:

    HashMap(size_type capacity) : capacity(capacity), table{capacity} {};

    HashMap(const HashMap &other) = default;

    mapped_type &operator[](const key_type &key) {

        auto found = find(key);
        if (found != end()) {
            return found->second;
        } else {
            itemsInsertedCount++;
            size_type index = getHash(key);
            table[index].push_front({key, mapped_type{}});
            return table[index].front().second;
        }

    }

    const mapped_type &valueOf(const key_type &key) const {

        auto found = find(key);
        if (found != end()) {
            return found->second;
        } else {
            throw std::out_of_range("Getting value of missing element.");
        }
    }

    mapped_type &valueOf(const key_type &key) {
        return const_cast<mapped_type & >((static_cast<const HashMap *>(this))->valueOf(key));
    }

    const_iterator find(const key_type &key) const {
        size_type index = getHash(key);

        auto const &searchedList = table[index];

        for (auto it = searchedList.begin(); it != searchedList.end(); it++) {
            if (it->first == key)
                return ConstIterator(this, index, it);
        }
        return end();
    }


    iterator find(const key_type &key) {
        return (static_cast<const HashMap * >(this)->find(key));
    }

    void remove(const key_type &key) {
        size_type index = getHash(key);
        auto &searchedList = table[index];

        if(searchedList.empty()) {
            throw std::out_of_range("Removing missing element.");
        }
        if (searchedList.begin()->first == key) {
            searchedList.pop_front();
            itemsInsertedCount--;
            return;
        }

        for (auto it = searchedList.begin();it != searchedList.end(); ++it) {
        }

        for (auto it = searchedList.begin();; ++it) {

            auto next = it;
            next++;
            if (next == searchedList.end()){
                throw std::out_of_range("Removing missing element.");
            }
            if (next->first == key){
                searchedList.erase_after(it);
                itemsInsertedCount--;
                return;
            }
        }
    }


    size_type getSize() const {
        return itemsInsertedCount;
    }

    iterator begin() {
        return Iterator(cbegin());
    }

    iterator end() {
        return Iterator(cend());
    }

    const_iterator cbegin() const {
        if (itemsInsertedCount == 0)
            return cend();

        size_type counter = 0;

        for (auto const &lista : table) {
            if (!lista.empty()) {
                return ConstIterator(this, counter, lista.begin());
            }
            counter++;
        }

        throw std::runtime_error("Unknown error when getting begin iterator");
    }

    const_iterator cend() const {
        return ConstIterator(this, capacity);
    }

    const_iterator begin() const {
        return cbegin();
    }

    const_iterator end() const {
        return cend();
    }

private:
    size_type getHash(const key_type &key) const {
        unsigned int hash = 0;
        for (char const &c: key) {
            hash = (hash * PRIME + (unsigned char) (c)) % capacity;
        }
        return hash;
    };


};


template<typename ValueType>
class HashMap<ValueType>::ConstIterator {
public:
    using reference = typename HashMap<ValueType>::const_reference;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename HashMap<ValueType>::value_type;
    using pointer = const typename HashMap<ValueType>::value_type *;
    using size_type = typename HashMap<ValueType>::size_type;
    using list = typename HashMap<ValueType>::list;
    using list_iterator = typename HashMap<ValueType>::list_iterator;
    using vectorOfLists = typename HashMap<ValueType>::vectorOfLists;

    friend class HashMap;

private:
    const HashMap<ValueType> *map;
    // when index == table.capacity then it is HashMap.end()
    size_type index;
    list_iterator currentListIterator;


public:
    explicit ConstIterator(const HashMap<ValueType> *map, size_type index, list_iterator it = {}) :
            map(map), index(index), currentListIterator(it) {}


    ConstIterator(const ConstIterator &other) :
            map(other.map), index(other.index), currentListIterator(other.currentListIterator) {}

    ConstIterator &operator++() {

        if (*this == map->end()) {
            throw std::out_of_range("Incrementing map end");
        }

        ++currentListIterator;
        //skip empty lists
        while (currentListIterator == getCurrentList().end()) {
            ++index;

            //we got out of range
            if (index == map->capacity) {
                *this = map->end();
                return *this;
            }

            currentListIterator = getCurrentList().begin();
        }
        return *this;
    }

    ConstIterator operator++(int) {
        auto result = *this;
        ++(*this);
        return result;
    }

    ConstIterator &operator--() {
        if (*this == map->begin()) {
            throw std::out_of_range("Decrementing map begin");
        }
        if (*this == map->end()) {
            index = map->capacity - 1;
            currentListIterator = map->table[index].end();
        }
        while (currentListIterator == getCurrentList().begin()) {
            --index;
            currentListIterator = getCurrentList().end();
        }

        --currentListIterator;

        return *this;
    }

    ConstIterator operator--(int) {
        auto result = *this;
        --(*this);
        return result;
    }

    reference operator*() const {
        if (*this == map->end()) {
            throw std::out_of_range("Dereferencing map end");
        }
        return *currentListIterator;
    }

    pointer operator->() const {
        return &this->operator*();
    }

    bool operator==(const ConstIterator &other) const {
        if (index != other.index) {
            return 0;
        }
            //we have 2 end iterators
        else if (index == map->capacity && other.index == map->capacity) {
            return 1;
        } else if (currentListIterator == other.currentListIterator) {
            return 1;
        } else {
            return 0;
        }
    }

    bool operator!=(const ConstIterator &other) const {
        return !(*this == other);
    }

private:
    const list &getCurrentList() {
        return map->table[index];
    }
};

template<typename ValueType>
class HashMap<ValueType>::Iterator : public HashMap<ValueType>::ConstIterator {
public:
    using reference = typename HashMap::reference;
    using pointer = typename HashMap::value_type *;

    Iterator() = delete;

    Iterator(const ConstIterator &other)
            : ConstIterator(other) {}

    Iterator &operator++() {
        ConstIterator::operator++();
        return *this;
    }

    Iterator operator++(int) {
        auto result = *this;
        ConstIterator::operator++();
        return result;
    }

    Iterator &operator--() {
        ConstIterator::operator--();
        return *this;
    }

    Iterator operator--(int) {
        auto result = *this;
        ConstIterator::operator--();
        return result;
    }

    pointer operator->() const {
        return &(this->operator*());
    }

    reference operator*() const {
        // ugly cast, yet reduces code duplication.
        return const_cast<reference>(ConstIterator::operator*());
    }
};


#endif 