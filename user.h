#pragma once
#include <string>
struct User {
public:
	std::string name;
	std::string password;
	char level;

	User(std::string _name, std::string _password, char _level);


	//void record(std::string);   //with a '\n' at the end

	//void delete();

	//void report();
};

User findUser(std::string);