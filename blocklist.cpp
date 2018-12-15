//#include "pch.h"
#include "blocklist.h"
#include "opfile.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include<fstream>


BlockList::BlockList(std::string _name) : name(_name) {
	if (exist(name)) return;
	std::fstream file(name, std::ios::binary | std::ios::out);
	writeInt(file, 1);
	writeInt(file, 0);
	writeInt(file, 0);
	file.close();
}


//void BlockList::locate(std::ifstream &stream, int thisBlock) {
//	stream.seekp(4 + thisBlock * blockSize);
//}
//
//void BlockList::nextBlock(std::ifstream &stream, int thisBlock) {
//	locate(stream, thisBlock);
//	int pos;
//	readInt(stream, pos);
//}

std::vector<int> BlockList::find(std::string index) {
	std::fstream file(name, std::ios::binary | std::ios::in | std::ios::out);
	//std::cerr << file.tellg() << std::endl;
	int blockNum;
	//file.seekp(0, std::ios::end);
	//std::cerr << file.tellg() << std::endl;
	file.seekp(0);
	//std::cerr << file.tellg() << std::endl;
	readInt(file, blockNum);
	//std::cerr << file.tellg() << std::endl;
	// strings + mapped int + pointer + count element in each block;
	std::string tmp;
	int thisBlock;
	int start = -1, end = -1;
	int lastPos = 4, thisPos = 4;
	for (thisBlock = 0; thisBlock < blockNum; ++thisBlock) {
		//std::cerr << file.tellg() << std::endl;
		file.seekp(4, std::ios::cur);
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
		file.seekp(thisPos);
		readInt(file, thisPos);
		file.seekp(thisPos);
	}
	if (start == -1) start = 4;
	//if (end == -1) end = lastPos;
	std::vector<int> res;
	file.seekp(start);
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
		file.seekp(nextPos);
	}
	file.close();
	return res;
}
void BlockList::del(std::string index, int key) {
	std::fstream file(name, std::ios::binary | std::ios::in | std::ios::out);
	//std::ofstream file(namee)
	int blockNum;
	//std::cerr << file.tellg() << std::endl;
	readInt(file, blockNum);
	// strings + mapped int + pointer + count element in each block;
	//std::cerr << file.gcount() << std::endl;
	//std::cerr << file.tellg() << std::endl;
	std::string tmp;
	int thisBlock;
	int start = -1, end = -1;
	int lastPos = 4, thisPos = 4;
	for (thisBlock = 0; thisBlock < blockNum; ++thisBlock) {
		file.seekg(4, std::ios::cur);
		//std::cerr << file.tellg() << std::endl;
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
		file.seekp(thisPos);
		readInt(file, thisPos);
		file.seekp(thisPos);
	}
	if (start == -1) start = 4;
	//if (end == -1) end = lastPos;
	file.seekp(start);
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
				file.close();
				return;
			}
		}
		file.seekp(nextPos);
	}
	file.close();
}

void BlockList::insert(std::string index, int key) {
	std::fstream file(name, std::ios::binary | std::ios::in | std::ios::out);
	int blockNum;
	readInt(file, blockNum);
	// strings + mapped int + pointer + count element in each block;
	std::string tmp;
	int thisBlock;
	int start = -1;
	int lastPos = 4, thisPos = 4;
	for (thisBlock = 0; thisBlock < blockNum; ++thisBlock) {
		file.seekp(4, std::ios::cur);
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
		file.seekp(thisPos);
		readInt(file, thisPos);
		file.seekp(thisPos);
	}
	if (start == -1) start = lastPos;
	file.seekp(start);
	int next;
	readInt(file, next);
	int cnt;
	readInt(file, cnt);
	if (cnt == size) {
		int end = 4 + blockNum * blockSize;
		file.seekp(0);
		writeInt(file, blockNum + 1);
		file.seekp(start);
		int next;
		readInt(file, next);
		file.seekp(start);
		writeInt(file, end);
		file.seekp(end);
		writeInt(file, next);
		writeInt(file, size / 2);
		int to = file.tellg();
		int from = start + 8 + (size / 2) * (40 + 4);
		file.seekp(start + 4);
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
		file.seekp(end + 8);
		std::string tmp;
		readString(file, tmp);
		if (index >= tmp) start = end;
	}
	file.seekp(start);
	readInt(file, next);
	readInt(file, cnt);
	for (int i = 1; i <= cnt; ++i) {
		std::string p;
		readString(file, p);
		file.seekp(-40, std::ios::cur);
		if (p > index) {
			int now = file.tellg();
			file.seekp(start + 8 + cnt * 44);
			for (;;) {
				//std::cerr << file.tellp() << std::endl;
				if (file.tellg() == now) break;
				file.seekp(-44, std::ios::cur);
				char s[100];
				for (int i = 0; i < 100; ++i) s[i] = '\0';
				int _ = file.tellg();
				file.read(s, 44);
				//std::cerr.write(s, 44) << std::endl;
				file.seekp(_ + 44);
				file.write(s, 44);
				//file.seekg(-44, std::ios::cur);
				//file.read(s, 44);
				//std::cerr.write(s, 44) << std::endl << std::endl;
				file.seekp(-88, std::ios::cur);
			}
			break;
		}
		file.seekp(44, std::ios::cur);
	}
	int __ = file.tellg();
	//file.seekp(start+ 8);
	//for (int i = 0; i < cnt; ++i) {
	//	std::string _;
	//	int ___;
	//	readString(file, _);
	//	//std::cerr << _ << " ";
	//	readInt(file, ___);
	//}
	//std::cerr << std::endl;
	file.seekp(__);
	int p = file.tellg();
	//file.seekp(-40, std::ios::cur);
	writeString(file, index);
	writeInt(file, key);
	int q = file.tellg();
	file.seekp(start + 4);
	writeInt(file, cnt + 1);
	//std::cerr << cnt + 1 << " " << q << std::endl;
	file.close();
}