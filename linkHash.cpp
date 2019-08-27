#include "linkHash.h"

linkHash::~linkHash()
{
	for (int i = 0; i < divisor; i++)
	{
		if (hashTable[i] != nullptr)
			delete hashTable[i];
	}
	delete[]hashTable;
}

bool linkHash::empty() const
{
	return hashSize == 0;
}

int linkHash::size() const
{
	return hashSize;
}

std::pair<const string, linkHash*>* linkHash::find(const string& theKey) const        //查找键为key的数对
{
	int homeBucket = Hash(theKey) % divisor;
	if (hashTable[homeBucket] == nullptr) {
		return nullptr;
	}
	else {
		return hashTable[homeBucket]->find(theKey);
	}
}

void linkHash::erase(const string& theKey)
{
	hashTable[Hash(theKey) % divisor]->erase(theKey);
}

void linkHash::insert(const std::pair<const string, linkHash*>& thePair)
{
	int homeBucket = (int)Hash(thePair.first) % divisor;
	if (hashTable[homeBucket] == nullptr)
	{
		linkDictionary<string, linkHash*>* New = new linkDictionary<string, linkHash*>;
		New->insert(thePair);
		hashTable[homeBucket] = New;
		hashSize++;
	}
	else
	{
		int homeSize = hashTable[homeBucket]->size();
		hashTable[homeBucket]->insert(thePair);
		if (hashTable[homeBucket]->size() > homeSize)
			hashSize++;
	}
}

void linkHash::output(std::ostream& out)
{
	for (int i = 0; i < divisor; i++)
	{
		linkDictionary<string, linkHash*>* Tmp = hashTable[i];
		out << "hashTable[" << i << "]:";
		if (Tmp != nullptr)
			Tmp->output(out);
		out << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, linkHash& cLinkHash)
{
	cLinkHash.output(out);
	return out;
}
