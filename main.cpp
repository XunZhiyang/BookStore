// Bookstore.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <fstream>
#include <string>
#include <iostream>
//#include "blocklist.h"
#include "opfile.h"
#include "store.h"

    
int main() {
	std::cout.setf(std::ios::fixed);
	std::cout.precision(2);
	Store Bookstore;

	if(exist("command.txt")){
		if (Bookstore.load("command.txt") == 0)  return 0;
	}
	char s[201];
	s[200] = '\0';
	for (;;) {
		std::cin.getline(s, 200);
		std::string str = s;
		try {
			int p = Bookstore.execute(str);
			if (p == 0) return 0;
		}
		catch (std::invalid_argument p) {
			std::cout << p.what() << "\n";
		}
		catch (std::domain_error p) {
			std::cout << p.what() << "\n";
		}
	}
}
//std::string randstring() {
//	std::string S;
//	for (int i = 1; i <= 4; ++i) {
//		S += 'a' + rand() % 26;
//	}
//	return S;
//}
//int main() {
//	BlockList test = BlockList("hahaha");
//	for (int i = 1; i <= 1000; ++i) {
//		std::string s = randstring();
//		//std::cerr << s << std::endl;
//		test.insert(randstring(), i);
//		if(i % 1000 == 0)
//			printf("%d\n", i);
//	}
//		std::cerr << "grsghslkgesrgklerhgliesghewlighesghlieghesrig" << std::endl;
//
//	for (int i = 1; i <= 3000; ++i) {
//		auto c = test.find(randstring());
//		for (int j = 0; j < c.size(); ++j) printf("%d\n", i);
//	}
//	//test.insert("aba", 578237);
//	test.insert("aha", 155);
//	test.insert("ffq", 156665);
//	test.insert("aca", 57482370);
//	test.del("aha", 155);
//	test.insert("qqiiyyy", 1550);
//	test.insert("aha", 1565);
//	test.del("qqiiyyy", 1550);
//	test.insert("vfdbf", 34243240);
//	printf("%d\n", test.find("aha")[0]);
//	return 0;
//}