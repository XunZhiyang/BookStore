// Bookstore.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <fstream>
#include<string>
#include <iostream>
#include "blocklist.h"

int main() {
	BlockList test = BlockList("hahaha");
	test.insert("qqq", 1);
	printf("%d\n", test.find("qqq"));
	return 0;
}