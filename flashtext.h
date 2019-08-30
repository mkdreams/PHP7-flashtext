#pragma once
#include "phpx.h"
#include "Tree.h"

using namespace php;
using namespace std;

class Cflashtext
{
public:
	Cflashtext();
	void learn(Array keywordsArr);
	Array match(String content);

private:
	uint8_t nextWordUnicode(string csi, int& i);

public:
	Tree* tree = nullptr;
};

