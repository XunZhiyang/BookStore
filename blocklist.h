#pragma once
#include<string>
#include<vector>
class BlockList {
	static const int size = 100;  // must be even
	static const int blockSize = 40 * size + 4 * size + 2 * 4;
	class Block {
		int next;
	};
public:
	std::string name;

	BlockList() = default;

	BlockList(std::string _name);

	void insert(std::string &index, int num);

	std::vector<int> find(std::string &index);

	void del(std::string &index, int key);
};
