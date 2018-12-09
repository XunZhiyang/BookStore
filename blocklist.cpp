#include "pch.h"
#include "blocklist.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include<fstream>

void BlockList::readInt(std::fstream &stream, int &t) {
	stream.read(reinterpret_cast<char *>(&t), 4);
	//std::cerr << stream.gcount() << std::endl;
}

void BlockList::writeInt(std::fstream &stream, int t) {
	stream.write(reinterpret_cast<char *>(&t), 4);
}

void BlockList::readString(std::fstream &stream, std::string &s) {
	char *ss = new char[41];
	ss[41] = '\0';
	stream.read(ss, 40);
	s = ss;
}

void BlockList::writeString(std::fstream &stream, std::string &s) {
	int len = s.length();
	for (int i = len; i < 40; ++i) s += '\0';
	stream.write(s.c_str(), 40);
}

BlockList::BlockList(std::string _name) : name(_name) {
	std::fstream file(name, std::ios::out);
	writeInt(file, 1);
	writeInt(file, 0);
	writeInt(file, 0);
	file.close();
}


//void BlockList::locate(std::ifstream &stream, int thisBlock) {
//	stream.seekg(4 + thisBlock * blockSize);
//}
//
//void BlockList::nextBlock(std::ifstream &stream, int thisBlock) {
//	locate(stream, thisBlock);
//	int pos;
//	readInt(stream, pos);
//}

std::vector<int> BlockList::find(std::string index) {
	std::fstream file(name);
	//std::cerr << file.tellg() << std::endl;
	int blockNum;
	//file.seekg(0, std::ios::end);
	//std::cerr << file.tellg() << std::endl;
	file.seekg(0);
	//std::cerr << file.tellg() << std::endl;
	readInt(file, blockNum);
	//std::cerr << file.tellg() << std::endl;
//int blockSize = 41 * size + 4 * size + 2 * 4;
// strings + mapped int + pointer + count element in each block;
	std::string tmp;
	int thisBlock;
	int start = -1, end = -1;
	int lastPos = 4, thisPos = 4;
	for (thisBlock = 0; thisBlock < blockNum; ++thisBlock) {
		//std::cerr << file.tellg() << std::endl;
		file.seekg(4, std::ios::cur);
		int cnt;
		//std::cerr << file.tellg() << std::endl;
		readInt(file, cnt);
		//std::cerr << cnt << std::endl;
		if (cnt > 0) {
			readString(file, tmp);
			if (index > tmp) start = lastPos;
			if (index < tmp) {
				end = thisPos;
				break;
			}
			lastPos = thisPos;
		}
		file.seekg(thisPos);
		readInt(file, thisPos);
		file.seekg(thisPos);
	}
	if (start == -1) start = 4;
	//if (end == -1) end = lastPos;
	std::vector<int> res;
	file.seekg(start);
	while (file.tellg() != end && file.tellg() != 0) {
		int nextPos, cnt;
		readInt(file, nextPos);
		readInt(file, cnt);
		for (int i = 1; i <= cnt; ++i) {
			std::string tmp;
			readString(file, tmp);
			int _;
			readInt(file, _);
			if (_ != -1 && tmp == index) {
				res.push_back(_);
			}
		}
		file.seekg(nextPos);
	}
	return res;
	file.close();
}
void BlockList::del(std::string index, int key) {
	std::fstream file(name);
	//std::ofstream file(namee)
	int blockNum;
	readInt(file, blockNum);
	// strings + mapped int + pointer + count element in each block;
	std::string tmp;
	int thisBlock;
	int start = -1, end = -1;
	int lastPos = 4, thisPos = 4;
	for (thisBlock = 0; thisBlock < blockNum; ++thisBlock) {
		file.seekg(4, std::ios::cur);
		int cnt;
		readInt(file, cnt);
		if (cnt > 0) {
			readString(file, tmp);
			if (index > tmp) start = lastPos;
			if (index < tmp) {
				end = thisPos;
				break;
			}
			lastPos = thisPos;
		}
		file.seekg(thisPos);
		readInt(file, thisPos);
		file.seekg(thisPos);
	}
	if (start == -1) start = 4;
	//if (end == -1) end = lastPos;
	file.seekg(start);
	while (file.tellg() != end && file.tellg() != 0) {
		int nextPos, cnt;
		readInt(file, nextPos);
		readInt(file, cnt);
		for (int i = 1; i <= cnt; ++i) {
			std::string tmp;
			readString(file, tmp);
			int _;
			readInt(file, _);
			if (tmp == index && _ == key) {
				file.seekp(-4, std::ios::cur);
				writeInt(file, -1);
			}
		}
		file.seekg(nextPos);
	}
	file.close();
}

void BlockList::insert(std::string index, int key) {
	std::fstream file(name);
	int blockNum;
	readInt(file, blockNum);
	// strings + mapped int + pointer + count element in each block;
	std::string tmp;
	int thisBlock;
	int start = -1;
	int lastPos = 4, thisPos = 4;
	for (thisBlock = 0; thisBlock < blockNum; ++thisBlock) {
		file.seekg(4, std::ios::cur);
		int cnt;
		readInt(file, cnt);
		if (cnt > 0) {
			readString(file, tmp);
			if (index < tmp) {
				start = lastPos;
				break;
			}
		}
		lastPos = thisPos;
		file.seekg(thisPos);
		readInt(file, thisPos);
		file.seekg(thisPos);
	}
	if (start == -1) start = lastPos;
	file.seekg(start);
	int next;
	readInt(file, next);
	int cnt;
	readInt(file, cnt);
	if (cnt == size) {
		int end = 4 + blockNum * blockSize;
		file.seekg(0);
		writeInt(file, blockNum + 1);
		file.seekg(start);
		int next;
		readInt(file, next);
		file.seekg(start);
		writeInt(file, end);
		file.seekg(end);
		writeInt(file, next);
		writeInt(file, size / 2);
		int to = file.tellg();
		int from = start + 8 + (size / 2) * (40 + 4);
		file.seekg(start + 4);
		writeInt(file, size / 2);
		while (from != start + blockSize) {
			char t;
			file.seekp(from);
			file.read(&t, 1);
			from++;
			file.seekp(to);
			file.write(&t, 1);
			to++;
		}
		file.seekg(end + 8);
		string tmp;
		readString(file, tmp);
	}
	file.seekg(start);
	readInt(file, next);
	readInt(file, cnt);
	for (int i = 1; i <= cnt; ++i) {
		std::string p;
		readString(file, p);
		file.seekg(-40, std::ios::cur);
		if (p > index) {
			int now = file.tellg();
			file.seekg(start + 8 + cnt * 44);
			for (;;) {
				if (file.tellg() == now) break;
				char s[44];
				file.seekg(-44, std::ios::cur);
				file.read(s, 44);
				file.write(s, 44);
				file.seekg(-88, std::ios::cur);
				//file.seekg(-40, std::ios::cur);
			}
			break;
		}
		file.seekg(44, std::ios::cur);
	}
	int p = file.tellg();
	//file.seekg(-40, std::ios::cur);
	writeString(file, index);
	writeInt(file, key);
	int q = file.tellg();
	file.seekg(start + 4);
	writeInt(file, cnt + 1);
	std::cerr << cnt + 1 << " " << q << std::endl;
	file.close();
}