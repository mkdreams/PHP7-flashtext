#pragma once
#include "phpx.h"
#include "linkHash.h"
#include "arrayList.h"
#include <tchar.h>

using namespace php;
using namespace std;

class Cflashtext
{
public:
	Cflashtext();
	void learn(Array keywordsArr);
	Array match(String content);

private:
	string nextWord(string csi, char chr, int& i);

public:
	linkHash* tree = nullptr;
};

