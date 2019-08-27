#pragma once
#include "flashtext.h"

Cflashtext::Cflashtext() {
	tree = new linkHash(11);
	//tree = linkHash<string, linkHash<string, int>*>(11);
	//tree.insert({ "11", new linkHash<string, int>(11) });
}

void Cflashtext::learn(Array keywordsArr) {
	auto begin = keywordsArr.begin();
	auto end = keywordsArr.end();

	//linkHash<string, int>* node = &linkHash<string, int>(11);
	//linkHash<string, int>* node2 = &linkHash<string, int>(11);

	////linkHash<string, int> node2(11);
	//root.insert({ "12",node });
	//root.insert({ "13",node2 });

	linkHash* nodeHash;
	std::pair<const string, linkHash*>* node;
	char chr;
	string word;
	bool isEnd = false;

	for (auto i = begin; i != end; i++) {
		string csi = i.value().toCString();

		linkHash* header = this->tree;

		for (int i = 0; (chr = csi[i]) != '\0';) {
			word = this->nextWord(csi, chr, i);
			if (csi[i] == '\0') {
				isEnd = true;
			}
			else {
				isEnd = false;
			}

			node = header->find(word);
			if (nullptr == node) {
				nodeHash = new linkHash(11);
				if (isEnd == true) {
					nodeHash->m_isEnd = true;
				}
				header->insert({ word,  nodeHash });
				header = nodeHash;
			}
			else {
				if (isEnd == true) {
					node->second->m_isEnd = true;
					header->insert({ word,  node->second });
				}

				header = node->second;
			}


			//cout << word << endl;
		}
	}

}


string Cflashtext::nextWord(string csi,char chr,int& i) {
	string word;
	if ((chr & 0x80) == 0) {
		word = chr;
		i = i + 1;
	}
	else if ((chr & 0xE0) == 0xC0) {
		word = csi.substr(i, 2);
		i = i + 2;
	}
	else if ((chr & 0xF0) == 0xE0) {
		word = csi.substr(i, 3);
		i = i + 3;
	}
	else if ((chr & 0xF8) == 0xF0) {
		word = csi.substr(i, 4);
		i = i + 4;
	}

	return word;
}

Array Cflashtext::match(String content) {
	linkHash* header = this->tree;
	std::pair<const string, linkHash*>* node;


	linkHash* matchedNode;

	CarrayList<linkHash*> matched(16);

	string csi = content.c_str();

	Array arr;

	//node = header->find(_T("m"));
	//matched.add(node->second);
	//node = matched.get(0)->find(_T("m"));

	char chr;
	string word;
	for (int i = 0; (chr = csi[i]) != '\0';) {
		word = this->nextWord(csi, chr, i);

		//cout << "words:" << word << endl;

		int length = matched.length();

		for (int j = 0; j < length; ) {
			matchedNode = matched.get(j);
			node = matchedNode->find(word);

			if (node == nullptr) {
				matched.remove(j);
				length--;
			}
			else {
				node->second->m_preKey = matchedNode->m_preKey + word;
				if (node->second->m_isEnd == true) {
					arr.append(node->second->m_preKey);
					//cout << node->second->m_preKey << " | " << "ok" << endl;
				}
				matched.replace(j, node->second);

				//cout << word << endl;
				j++;
			}
		}


		node = header->find(word);

		if (node != nullptr) {
			node->second->m_preKey = word;
			if (node->second->m_isEnd == true) {
				arr.append(node->second->m_preKey);
				//cout << "ok" << endl;
			}
			matched.add(node->second);
		}

		/*if (matchedTemp.isEmpty()) {
			matched.clear();
		}
		else {
			matched = matchedTemp;
		}*/

		//arr.append(word);
	}

	return arr;
}
