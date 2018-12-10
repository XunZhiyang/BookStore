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
		if (username == s) return User(username, password, level);
	}
	
}