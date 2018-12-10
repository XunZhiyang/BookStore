// Bookstore.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <fstream>
#include<string>
#include <iostream>
#include "blocklist.h"

int main() {
	BlockList test = BlockList("hahaha");
	test.insert("aba", 578237);
	test.insert("ffq", 155);
	test.insert("ava", 155);
	test.insert("aca", 5782370);
	test.insert("qqiiyyy", 1550);
	test.insert("vfdbf", 34243240);
	printf("%d\n", test.find("ava")[0]);
	return 0;
}