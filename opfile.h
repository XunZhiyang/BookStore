#pragma once
#include <fstream>

void readInt(std::fstream &stream, int &t);

void readString(std::fstream &stream, std::string &s, int _size = 40);

void writeInt(std::fstream &stream, int t);

void writeString(std::fstream &stream, std::string &s, int _size = 40);