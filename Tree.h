#pragma once
#include <unordered_map>
using namespace std;
typedef unsigned int TrieKey;

struct word {
	uint8_t unicode;
	int len;
};

struct MatchWord {
	int pos;
	vector<pair<int,int>> nexts;
	MatchWord() :pos(0){
	}
};

class TreeNode {
public:
	TreeNode();
public:
	typedef unordered_map<TrieKey, TreeNode*> NextMap;
	NextMap* next;//用于key，value
	bool m_isEnd = false;
};

class Tree
{
public:
	Tree();

public:
	TreeNode* root;
};
