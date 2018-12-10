#include "pch.h"
#include <fstream>
//#include <string>
#include "user.h"
#include "store.h"
Store::Store() {
	std::ifstream test("userData");
	if (!test.good()) {
		//std::ofstream userData("userData");
		addUser("root", "sjtu", 7);
	}
	user = findUser("root");
}

void Store::execute(std::string command) {
	
}


int Store::load(std::string fileName) {
	std::ifstream loadFile(fileName, std::ios::binary);
	if (!loadFile.good()) return -1;
	char s[250];
	while(loadFile.peek() != EOF) {
		loadFile.getline(s, 250);
		execute(s);
	}
}