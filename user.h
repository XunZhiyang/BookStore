#pragma once
#include <string>
struct User {
public:
	std::string username;
	std::string password;
	std::string name;
	char level;

	User() = default;

	User(std::string _username, std::string _password, std::string _name, char _level);


	//void record(std::string);   //with a '\n' at the end

	//void delete();

	//void report();
};

User findUser(std::string);

int count(std::string);

int addUser(std::string username, std::string password, std::string name, char level);

void deleteUser(std::string username);