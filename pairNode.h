#pragma once
#include <utility>
using namespace std;

template<typename K,typename V>
struct pairNode
{
	std::pair<const K, V> element;
	pairNode<K, V>* next;
	pairNode(const std::pair<const K, V>& thePair) :element(thePair) {}
	pairNode(const std::pair<const K, V>& thePair, pairNode<K, V>* theNext) :element(thePair) {
		next = theNext;
	}
};
