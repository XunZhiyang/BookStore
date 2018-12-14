#pragma once
#include<string>
#include "user.h"
#include "blocklist.h"
class Store {
public:	
	User user;
	BlockList ISBN, name, author, keyword;
	int select = -1;
	std::string wname;
    Store();

	void execute(std::string);

	void valid(int level);

	int load(std::string);
};