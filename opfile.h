#pragma once
#include <fstream>

bool exist(std::string name);

void readInt(std::fstream &stream, int &t);

void readString(std::fstream &stream, std::string &s, int _size = 40);

void writeInt(std::fstream &stream, int t);

void writeString(std::fstream &stream, std::string &s, int _size = 40);