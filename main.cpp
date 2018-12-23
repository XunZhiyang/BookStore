// Bookstore.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <fstream>
#include <string>
#include <iostream>
#include "opfile.h"
#include "store.h"
#include "log.h"


int main() {
	std::cout.setf(std::ios::fixed);
	std::cout.precision(2);
	Store Bookstore;
	std::cerr << "Welcome to the bookstore administration system!\n";
	if(exist("command.txt")){
		if (Bookstore.load("command.txt") == 0)  return 0;
	}
	char s[201];
	s[200] = '\0';
	int cntcnt = 0;
	for (;;) {
		std::cin.getline(s, 200);
		if (!std::cin.good()) {
			std::cin.clear();
			std::cin.ignore(2147483644, '\n');
		}
		std::string str = s;
		bool flag = true;
		try {
			int p = Bookstore.execute(str);
			if (p == 0) return 0;
		}
		catch (std::invalid_argument p) {
			flag = false;
			std::cout << p.what() << "\n";
		}
		catch (std::domain_error p) {
			flag = false;
			std::cout << p.what() << "\n";
		}
		if (flag) {
			if(Bookstore.user.username != "")
			    Log::record(Bookstore.user.username + "(" + Bookstore.user.name + ") : " + str);
			else {
				Log::record("guest : " + str);
			}
		}
	}
}
