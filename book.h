#pragma once
#include <string>
#include <vector>
namespace Book {  //The file saving data is "bookData"
	std::pair<int, int> getPos(std::string c);

	int insert();

	void modify(int, std::string c, std::string &val);

	std::string query(int, std::string);

	int queryq(int);

	void modifyq(int, int);

	std::string getISBN(int pos);

	void display(int pos);

	std::vector<int> allList();
}