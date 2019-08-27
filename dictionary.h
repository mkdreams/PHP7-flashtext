#pragma once

template<typename K, typename V>
class dictionary
{
public:
	virtual ~dictionary() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual std::pair<const K, V>* find(const K& theKey) const = 0;    //查找键为key的数对
	virtual void erase(const K& theKey) = 0;
	virtual void insert(const std::pair<const K, V>& thePair) = 0;
};
