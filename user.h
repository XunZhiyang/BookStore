#pragma once
#include "pch.h"
#include <string>
struct User {
public:
	std::string name;
	std::string password;
	char level;

	User() = default;

	User(std::string _name, std::string _password, char _level);


	//void record(std::string);   //with a '\n' at the end

	//void delete();

	//void report();
};

User findUser(std::string);

int count(std::string);

int addUser(std::string username, std::string password, char level);