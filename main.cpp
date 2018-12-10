// Bookstore.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <fstream>
#include <string>
#include <iostream>
#include "blocklist.h"
#include "store.h"


int main() {
	Store Bookstore;
	std::ifstream test("command.txt");
	if (test.good()) {
		if (Bookstore.load("command.txt") == 0)  return 0;
	}
}
//
//int main() {
//	BlockList test = BlockList("hahaha");
//	test.insert("aba", 578237);
//	test.insert("ffq", 155);
//	test.insert("aca", 5782370);
//	test.insert("qqiiyyy", 1550);
//	test.insert("aha", 155);
//	test.insert("vfdbf", 34243240);
//	printf("%d\n", test.find("aha")[0]);
//	return 0;
//}