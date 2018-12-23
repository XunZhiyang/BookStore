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
		std::fstream fpos("fpos", std::ios::binary | std::ios::in);
		std::fstream finance("finance", std::ios::binary | std::ios::in);
		std::string string;
		std::cout << std::showpos;
		int _;
		readInt(fpos, _);
		while (file.peek() != EOF) {
			if (_ == file.tellg()) {
				double c = readDouble(finance);
				readString(file, string, 300);
				std::cout << string << " " << c << "\n";
				if(fpos.peek() != EOF) readInt(fpos, _);
			}
			else {
				readString(file, string, 300);
				std::cout << string << "\n";
			}
		}
		std::cout << std::noshowpos;
		finance.close();
		fpos.close();
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
			if (flag) std::cout << tmp << "\n";
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
		std::fstream fpos("fpos", std::ios::binary | std::ios::in);
		std::fstream finance("finance", std::ios::binary | std::ios::in);
		std::string string;
		std::cout << std::showpos;
		while (fpos.peek() != EOF) {
			double c = readDouble(finance);
			int _;
			readInt(fpos, _);
			file.seekg(_);
			readString(file, string, 300);
			std::cout << string << " " << c << "\n";
		}
		std::cout << std::noshowpos;
		finance.close();
		fpos.close();
		file.close();
	}
	void addFpos() {
		std::fstream file("log", std::ios::binary | std::ios::in | std::ios::out);
		file.seekp(0, std::ios::end);
		int u = file.tellp();
		file.close();
		file.open("fpos", std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
		writeInt(file, u);
		file.close();
	}
}