#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include "hash.h"
#include "dictionary.h"
#include "linkDictionary.h"


class linkHash : public dictionary<string, linkHash*>
{
public:
	linkHash(int theDivisor = 11)
	{
		divisor = theDivisor;
		hashSize = 0;
		hashTable = new linkDictionary<string, linkHash*>* [divisor];
		for (int i = 0; i < divisor; i++)
			hashTable[i] = nullptr;
	}
	~linkHash();
	bool empty() const;
	int size() const;
	std::pair<const string, linkHash*>* find(const string& theKey) const;        //查找键为key的数对
	void erase(const string& theKey);
	void insert(const std::pair<const string, linkHash*>& thePair);
	void output(std::ostream& out);

public:
	bool m_isEnd{false};
	string m_preKey;

protected:
	linkDictionary<string, linkHash*>** hashTable;
	int hashSize;                        //哈希表中数对的数量
	int divisor;                        //除法散列函数的除数
	Hash<string> Hash;                        //映射
};
