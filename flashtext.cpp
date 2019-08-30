#pragma once
#include "flashtext.h"

Cflashtext::Cflashtext() {
	tree = new Tree();
}

void Cflashtext::learn(Array keywordsArr) {
	auto begin = keywordsArr.begin();
	auto end = keywordsArr.end();

	uint8_t unicode;
	bool isEnd = false;
	int wordlen = 0;
	TreeNode* headerNodeMap;
	TreeNode::NextMap::const_iterator nodePair;

	for (auto i = begin; i != end; i++) {
		char* csi = i.value().toCString();

		headerNodeMap = this->tree->root;

		for (int i = 0; csi[i] != '\0';) {
			unicode = this->nextWordUnicode(csi+i, wordlen);
			i += wordlen;

			if (csi[i] == '\0') {
				isEnd = true;
			}
			else {
				isEnd = false;
			}

			if (NULL == headerNodeMap->next) {
				headerNodeMap->next = new TreeNode::NextMap;
			}

			nodePair = headerNodeMap->next->find(unicode);
			//not matched
			if (nodePair == headerNodeMap->next->end()) {
				TreeNode* nextNode = new TreeNode;
				if (isEnd == true) {
					nextNode->m_isEnd = true;
				}
				headerNodeMap->next->insert(make_pair(unicode, nextNode));
				headerNodeMap = nextNode;
			}
			else {
				if (isEnd == true) {
					nodePair->second->m_isEnd = true;
				}

				headerNodeMap = nodePair->second;
			}
		}
	}
}

uint8_t Cflashtext::nextWordUnicode(string str,int& len) {
	uint8_t unicode;
	if ((str[0] & 0x80) == 0) {
		unicode = (uint8_t)(str[0]) & 0x7f;
		len = 1;
	}
	else if ((str[0] & 0xE0) == 0xC0) {
		// 110xxxxxx
		// 5bit, total 5bit
		unicode = (uint8_t)(str[0]) & 0x1f;

		// 6bit, total 11bit
		unicode <<= 6;
		unicode |= (uint8_t)(str[1]) & 0x3f;
		len = 2;
	}
	else if ((str[0] & 0xF0) == 0xE0) {
		// 4bit, total 4bit
		unicode = (uint8_t)(str[0]) & 0x0f;

		// 6bit, total 10bit
		unicode <<= 6;
		unicode |= (uint8_t)(str[1]) & 0x3f;

		// 6bit, total 16bit
		unicode <<= 6;
		unicode |= (uint8_t)(str[2]) & 0x3f;
		len = 3;
	}
	else if ((str[0] & 0xF8) == 0xF0) {
		// 3bit, total 3bit
		unicode = (uint8_t)(str[0]) & 0x07;

		// 6bit, total 9bit
		unicode <<= 6;
		unicode |= (uint8_t)(str[1]) & 0x3f;

		// 6bit, total 15bit
		unicode <<= 6;
		unicode |= (uint8_t)(str[2]) & 0x3f;

		// 6bit, total 21bit
		unicode <<= 6;
		unicode |= (uint8_t)(str[3]) & 0x3f;

		len = 4;
	}
	else {
		unicode = 1;
		len = 1;
	}


	return unicode;
}

Array Cflashtext::match(String content) {
	vector<word*> words;
	TreeNode* headerNodeMap;
	TreeNode::NextMap::const_iterator nodePair;
	int wordlen = 0;
	headerNodeMap = this->tree->root;

	vector<struct MatchWord*> res;
	MatchWord* MatchWordTemp;

	word* wordTemp;

	char* csi = content.c_str();
	for (int i = 0; csi[i] != '\0';) {
		wordTemp = new word();
		wordTemp->unicode = nextWordUnicode(csi+i, wordlen);
		wordTemp->len = wordlen;

		words.push_back(wordTemp);

		i += wordlen;
	}
	int words_size = words.size();

	res.empty();
	res.resize(words_size);

	uint8_t unicode,unicodeTemp;
	for (int i = 0; i < words_size; i++) {
		for (int j = 0; (i+j < words_size && j < 512); j++) {
			unicode = words[i+j]->unicode;

			if (NULL == headerNodeMap->next) {
				break;
			}

			nodePair = headerNodeMap->next->find(unicode);
			//not found break;
			if (nodePair == headerNodeMap->next->end()) {
				break;
			}
			else {
				if (nodePair->second->m_isEnd == true) {
					if (NULL == res[i]) {
						MatchWordTemp = new MatchWord();
						MatchWordTemp->nexts.push_back(make_pair(i, j+1));
						MatchWordTemp->pos = i;
						res[i] = MatchWordTemp;
					}
					else {
						res[i]->nexts.push_back(make_pair(i, j + 1));
					}
				}

				headerNodeMap = nodePair->second;
			}

		}

		headerNodeMap = this->tree->root;
	}

	Array arr;
	for (int i = 0; i < words_size; i++) {
		if (NULL == res[i]) {
			continue;
		}

		int len  = res[i]->nexts.size();
		string temp;
		for (int j = 0; j < len; j++) {
			for (int first = 1; first < res[i]->nexts[j].second; first++) {
				char c[20];
				itoa(words[res[i]->nexts[j].first + first]->unicode,c,10);
				temp += c;
			}
			arr.append(temp);
		}
	}
	//res to array



	return arr;
}
