#pragma once
#include <fstream>

bool exist(const std::string &name);

void readInt(std::fstream &stream, int &t);

void readString(std::fstream &stream, std::string &s, int _size = 40);

void writeInt(std::fstream &stream, int t);

void writeString(std::fstream &stream, std::string &s, int _size = 40);

void writeDouble(std::fstream &stream, double t);

double readDouble(std::fstream &stream);
