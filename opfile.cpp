#include "pch.h"
#include <fstream>
#include "opfile.h"

void readInt(std::fstream &stream, int &t) {
	stream.read(reinterpret_cast<char *>(&t), 4);
	//std::cerr << stream.gcount() << std::endl;
}

void writeInt(std::fstream &stream, int t) {
	stream.write(reinterpret_cast<char *>(&t), 4);
}

void readString(std::fstream &stream, std::string &s, int _size) {
	char *ss = new char[_size + 1];
	ss[_size] = '\0';
	stream.read(ss, 40);
	s = ss;
}

void writeString(std::fstream &stream, std::string &s, int _size) {
	int len = s.length();
	for (int i = len; i < _size; ++i) s += '\0';
	stream.write(s.c_str(), _size);
}