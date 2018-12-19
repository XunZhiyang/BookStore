//#include "pch.h"
#include <fstream>
#include "opfile.h"

bool exist(const std::string &name) {
	std::ifstream test(name);
	if (test.good()) {
		test.close();
		return true;
	}
	return false;
}
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
	stream.read(ss, _size);
	s = ss;
	delete []ss;
}

void writeString(std::fstream &stream, std::string &s, int _size) {
	int len = s.length();
	for (int i = len; i < _size; ++i) s += '\0';
	stream.write(s.c_str(), _size);
}

void writeDouble(std::fstream &stream, double t) {
	stream.write(reinterpret_cast<char *>(&t), sizeof(double));
}

double readDouble(std::fstream &stream) {
	double t;
	stream.read(reinterpret_cast<char *>(&t), sizeof(double));
	return t;
}