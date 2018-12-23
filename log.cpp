#include <string>
#include <iostream>
#include <fstream>
#include "opfile.h"
namespace Log {
	void record(std::string &&string) {
		std::fstream file("log", std::ios::binary | std::ios::in | std::ios::out);
		file.seekp(0, std::ios::end);
		writeString(file, string, 300);
		file.close();
	}

	void queryall() {
		std::fstream file("log", std::ios::binary | std::ios::in);
		std::string tmp;
		while (file.peek() != EOF) {
			readString(file, tmp, 300);
			std::cout << tmp << "\n";
		}
		file.close();
	}
	void query(std::string username) {
		std::fstream file("log", std::ios::binary | std::ios::in);
		std::string tmp;
		while (file.peek() != EOF) {
			readString(file, tmp, 300);
			bool flag = true;
			for (int i = 0; i < username.length(); ++i) {
				if (username[i] != tmp[i]) {
					flag = false;
					break;
				}
			}
			if(flag) std::cout << tmp << "\n";
		}
		file.close();
	}
	void queryEmployee() {
		std::fstream file("log", std::ios::binary | std::ios::in);
		std::string tmp;
		while (file.peek() != EOF) {
			readString(file, tmp, 300);
			bool flag = true;
			std::string username = "root";
			for (int i = 0; i < 4; ++i) {
				if (username[i] != tmp[i]) {
					flag = false;
					break;
				}
			}
			if (!flag) std::cout << tmp << "\n";
		}
		file.close();
	}
	void finance() {
		std::fstream file("log", std::ios::binary | std::ios::in);
		file.seekg(0, std::ios::end);
		std::string tmp;
		while (file.peek() != EOF) {
			readString(file, tmp, 300);
			std::cout << tmp << "\n";
		}
		file.close();
	}
}