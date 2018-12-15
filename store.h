#pragma once
#include <stack>
#include <string>
#include "user.h"
#include "blocklist.h"
class Store {
private:
	//bool ISBNcmp(int x, int y);
public:	
	User user;
	BlockList ISBN, name, author, keyword;
	int select = -1;
	std::stack<double> stack;

    Store();

	BlockList &ch(std::string);

	int execute(std::string);

	void valid(int level);

	void modify(std::string command, int pos);

	void import(std::string command, int pos);

	void showFinance(std::string command, int pos);

	void intersect(std::vector<int> &, std::vector<int>);

	void buy(std::string command, int pos);

	void show(std::string command, int pos);

	//int load(std::string);
};