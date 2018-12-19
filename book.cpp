#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "book.h"
#include "opfile.h"
namespace Book { // 20 + 3 * 40 + 6(price) + 4(quantity) = 150 bytes per book
	std::pair<int, int> getPos(std::string c) {
		if (c == "ISBN") return { 0, 20 };
		if (c == "name") return { 20, 40 };
		if (c == "author") return { 60, 40 };
		if (c == "keyword") return { 100, 40 };
		if (c == "price") return { 140, 6 };
		//if (c == "quantity") return { 146, 4 };
		throw(std::invalid_argument("Invalid Book information"));
	}
	int insert() {
		std::fstream file("bookData", std::ios::binary | std::ios::in | std::ios::out);
		file.seekp(0, std::ios::end);
		int pos = file.tellp();
		std::string nil;
		nil.clear();
		writeString(file, nil, 150);
		file.close();
		return pos;
	}
	void modify(int pos, std::string c, std::string &val) {
		auto tmp = getPos(c);
		pos += tmp.first;
		std::fstream file("bookData", std::ios::binary | std::ios::in | std::ios::out);
		file.seekp(pos);
		file.write(val.c_str(), tmp.second);
		file.close();
	}
	std::string query(int pos, std::string c) {
		auto tmp = getPos(c);
		pos += tmp.first;
		std::fstream file("bookData", std::ios::binary | std::ios::in);
		file.seekg(pos);
		std::string ret;
		readString(file, ret, tmp.second);
		file.close();
		return ret;
	}
	int queryq(int pos) {
		pos += 146;
		std::fstream file("bookData", std::ios::binary | std::ios::in);
		file.seekg(pos);
		int ret;
		readInt(file, ret);
		file.close();
		return ret;
	}
	void modifyq(int pos, int val) {
		pos += 146;
		std::fstream file("bookData", std::ios::binary | std::ios::in | std::ios::out);
		file.seekp(pos);
		writeInt(file, val);
		file.close();
	}
	std::string getISBN(int pos) {
		std::fstream file("bookData", std::ios::binary | std::ios::in);
		file.seekg(pos);
		std::string s;
		readString(file, s, 20);
		file.close();
		return s;
	}
	void display(int pos) {
		std::fstream file("bookData", std::ios::binary | std::ios::in);
		std::string s;
		file.seekg(pos);
		readString(file, s, 20);
		std::cout << s << "\t";	
		readString(file, s, 40);
		std::cout << s << "\t";	
		readString(file, s, 40);
		std::cout << s << "\t";	
		readString(file, s, 40);
		std::cout << s << "\t";
		readString(file, s, 6);
		if (s[0] == '\0') {
			std::cout << "0.00\t";
		}
		else {
			std::stringstream ss(s);
			double p;
			ss >> p;
			std::cout << p << "\t";
		}
		int q = 0;
		readInt(file, q);
		std::cout << q << "本\n";
		file.close();
	}
	std::vector<int> allList() {
		std::vector<int> c;
		std::fstream file("bookData", std::ios::binary | std::ios::in);
		file.seekg(0, std::ios::end);
		int u = file.tellg();
		for (int i = 0; i < u; i += 150) {
			c.push_back(i);
		}
		return c;
	}
}
