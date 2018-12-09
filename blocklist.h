#pragma once
#include<string>
#include<vector>
class BlockList {
	static const int size = 2;  // must be even
	static const int blockSize = 40 * size + 4 * size + 2 * 4;
	class Block {
		int next;
	};
public:
	std::string name;

	BlockList(std::string _name);
	void readInt(std::fstream &stream, int &t);

	void readString(std::fstream &stream, std::string &s);

	void writeInt(std::fstream &stream, int t);

	void writeString(std::fstream &stream, std::string &s);

	//void locate(std::ifstream &stream, int thisblock);

	//void nextblock(std::ifstream &stream, int thisBLock);

	void insert(std::string index, int num);

	std::vector<int> find(std::string index);

	void del(std::string index, int key);
};
