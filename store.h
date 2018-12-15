#pragma once
#include <vector>
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
	std::vector<double> vector;

    Store();

	BlockList &ch(std::string);

	int execute(std::string &);

	void valid(int level);

	void modify(std::string &command, int pos);

	void import(std::string &command, int pos);

	void showFinance(std::string &command, int pos);

	void intersect(std::vector<int> &, std::vector<int>);

	void buy(std::string &command, int pos);

	void show(std::string &command, int pos);

	void su(std::string &command, int pos);

	void useradd(std::string &command, int pos);

	void reg(std::string &command, int pos);

	void del(std::string &command, int pos);

	void passwd(std::string &command, int pos);

	int load(std::string);
};