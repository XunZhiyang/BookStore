#pragma once
#include<string>
#include "user.h"
#include "blocklist.h"
class Store {
public:	
	User user;

    Store();

	void execute(std::string);

	int load(std::string);
};