//#include "pch.h"
#include <fstream>
//#include <string>
#include "user.h"
#include "store.h"
Store::Store() {
	std::ifstream test("userData");
	if (!test.good()) {
		ISBN = BlockList("ISBN");
		name = BlockList("name");
		author = BlockList("author");
		keyword = BlockList("keyword");

		//std::ofstream userData("userData");
		addUser("root", "sjtu", 7);
	}
	user = findUser("root");
}	

void Store::valid(int level) {
	if (user.level < level) throw(std::domain_error("Invalid"));
}

void Store::execute(std::string command) {
	int pos = command.find(" ");
	std::string t = command.substr(0, pos);
	if (t == "select") {
		valid(3);
		t = command.substr(pos + 1, command.length() - pos - 1);
		auto _ = ISBN.find(t);
		if(_.size()) select = 
	}
	else if (t == "modify") {
		valid(3);
	}
	if(t == "")
}


int Store::load(std::string fileName) {
	std::ifstream loadFile(fileName, std::ios::binary);
	if (!loadFile.good()) return ;
	char s[250];
	while(loadFile.peek() != EOF) {
		loadFile.getline(s, 250);
		int p = execute(s);
		if (p == 0) return 0;
	}
}