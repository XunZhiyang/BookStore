//#include "pch.h"
#include<string>
#include<fstream>
#include "user.h"
#include "opfile.h"

//All the user data are saved in the file "userData"
//log is saved in "log"
//
//void User::record(std::string) {    //with a '\n' at the end
//	std::fstream file("log", std::ios::binary | std::ios::out);
//	file.seekp(0, std::ios::end);
//	file << 
//
//}

User::User(std::string _name, std::string _password, char _level) : name(_name), password(_password), level(_level) {}

User findUser(std::string s) {
	std::fstream userData("userData");
	while (userData.peek() != EOF) {
		std::string username, password;
		char level;
		readString(userData, username, 30);
		readString(userData, password, 30);
		userData.read(&level, 1);
		if (username == s) {
			userData.close();
			return User(username, password, level);
		}
	}
	userData.close();
	throw(std::invalid_argument("NO SUCH USER"));
}

int count(std::string s) {
	try {
		findUser(s);
	}
	catch (const std::invalid_argument &msg) {
		return 0;
	}
	return 1;
}

int addUser(std::string username, std::string password, char level) {
	if (count(username)) return 0;
	std::fstream userData("userData");
	userData.seekp(0, std::ios::end);
	writeString(userData, username, 30);
	writeString(userData, password, 30);
	userData.write(&level, 1);
	return 1;
}