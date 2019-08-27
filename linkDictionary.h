#pragma once
#include <iostream>
#include <sstream>
#include "pairNode.h"
#include "dictionary.h"


template<typename K, typename V>
class linkDictionary : public dictionary<K, V>
{
public:
	linkDictionary() { headerNode = nullptr; dictionarySize = 0; }
	~linkDictionary();
	bool empty() const;
	int size() const;
	std::pair<const K, V>* find(const K& theKey) const;    //查找键为key的数对
	void erase(const K& theKey);
	void insert(const std::pair<const K, V>& thePair);

	void output(std::ostream& out);
protected:
	pairNode<K, V>* headerNode;
	int dictionarySize;
};

template<typename K, typename V>
linkDictionary<K, V>::~linkDictionary()
{
	pairNode<K, V>* Del = headerNode;
	while (Del != nullptr)
	{
		headerNode = Del->next;
		delete Del;
		Del = headerNode;
	}
}

template<typename K, typename V>
bool linkDictionary<K, V>::empty() const
{
	return dictionarySize == 0;
}

template<typename K, typename V>
int linkDictionary<K, V>::size() const
{
	return dictionarySize;
}

template<typename K, typename V>
std::pair<const K, V>* linkDictionary<K, V>::find(const K& theKey) const    //查找键为key的数对
{
	pairNode<K, V>* Tmp = headerNode;
	while ((Tmp != nullptr) && (Tmp->element.first != theKey))
		Tmp = Tmp->next;
	if ((Tmp != nullptr) && (Tmp->element.first == theKey))
		return &Tmp->element;

	return nullptr;
}

template<typename K, typename V>
void linkDictionary<K, V>::erase(const K& theKey)
{
	pairNode<K, V>* Tmp = nullptr;
	pairNode<K, V>* Del = headerNode;
	while ((Del != nullptr) && (Del->element.first < theKey))
	{
		Tmp = Del;
		Del = Del->next;
	}

	if ((Del == nullptr) || (Del->element.first != theKey))        //要删除的数对不存在
	{
		std::ostringstream s;
		s << "theKey = " << theKey << "inexistence";
		//throw keyInexistence(s.str());
	}
	if (Tmp == nullptr)                //要删除的数对是首节点
		headerNode = Del->next;
	else
		Tmp->next = Del->next;

	delete Del;
	dictionarySize--;
}

template<typename K, typename V>
void linkDictionary<K, V>::insert(const std::pair<const K, V>& thePair)
{
	pairNode<K, V>* Tmp = nullptr;
	pairNode<K, V>* New = headerNode;
	while ((New != nullptr) && (New->element.first < thePair.first))
	{
		Tmp = New;
		New = New->next;
	}
	if ((New != nullptr) && (New->element.first == thePair.first))        //键为key的数对存在，修改值
		New->element.second = thePair.second;
	else    //不存在，创建新节点，插入
	{
		pairNode<K, V>* newNode = new pairNode<K, V>(thePair, New);
		if (Tmp == nullptr)            //要插入到首节点
			headerNode = newNode;
		else
			Tmp->next = newNode;
	}
	dictionarySize++;
}

template<typename K, typename V>
void linkDictionary<K, V>::output(std::ostream& out)
{
	out << "Key  ->" << "  value" << std::endl;
	pairNode<K, V>* Tmp = headerNode;
	while (Tmp != nullptr)
	{
		out << Tmp->element.first << "      " << Tmp->element.second << std::endl;
		Tmp = Tmp->next;
	}
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& out, linkDictionary<K, V>& cLinkDictionary)
{
	cLinkDictionary.output(out);
	return out;
}
