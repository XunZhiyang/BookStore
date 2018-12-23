//#include "pch.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include "user.h"
#include "book.h"
#include "opfile.h"
#include "log.h"
#include "store.h"

Store::Store() {
	if (!exist("userData")) {
		std::ofstream userData("userData");
		userData.close();
		std::ofstream bookData("bookData");
		bookData.close();
		std::ofstream finance("finance");
		finance.close();	
		std::ofstream log("log");
		log.close();
		std::string root = "root", sjtu = "sjtu", BOSS = "BOSS";
		addUser(root, sjtu, BOSS, 7);
	}
	ISBN = BlockList("ISBN");
	name = BlockList("name");
	author = BlockList("author");
	keyword = BlockList("keyword");
	std::string root = "root";
	user = findUser(root);
}

BlockList &Store::ch(std::string listName) {
	if (listName == "ISBN") return ISBN;
	if (listName == "name") return name;
	if (listName == "author") return author;
	if (listName == "keyword") return keyword;
	throw(std::invalid_argument("Invalid"));
}

void Store::valid(int level) {
	if (user.level < level) throw(std::domain_error("Invalid"));
}

void Store::modify(std::string &command, int pos) {
	if (select == -1) throw(std::invalid_argument("Invalid"));
	for (;;) {
		int npos = command.find(" ", pos);
		if (npos == -1) break;
		auto &&_ = command.substr(pos, npos - pos);
		int quo = _.find("\"");
		std::string c, val;
		if (quo == -1) {
			int equ = _.find("=");
			c = _.substr(1, equ - 1);
			val = _.substr(equ + 1);
			pos = npos + 1;
		}
		else {
			c = _.substr(1, quo - 2);
			int quo2 = command.find("\"", pos + quo + 1);
			val = command.substr(pos + quo + 1, quo2 - (pos + quo + 1));
			pos = quo2 + 2;
		}
		if (c == "ISBN" && ISBN.find(val).size()) {
			throw(std::invalid_argument("Invalid"));
		}
		if (c != "price") {
			auto &&old = Book::query(select, c);
			int par = old.find("|");
			if (old[0] != '\0') {
				if (par == -1) ch(c).del(old, select);
				else {
					int ppos = 0;
					while (par != -1) {
						auto &&old1 = old.substr(ppos, par - ppos);
						ch(c).del(old1, select);
						ppos = par + 1;
						par = val.find("|", ppos);
					}
					auto &&old1 = old.substr(ppos);
					ch(c).del(old1, select);
				}
			}
		}
		int par = val.find("|");
		int ppos = 0;
		std::string val1;
		while (par != -1) {
			if (c != "keyword") throw(std::invalid_argument("Invalid"));
			val1 = val.substr(ppos, par - ppos);
			ch(c).insert(val1, select);
			ppos = par + 1;
			par = val.find("|", ppos);
		}
		val1 = val.substr(ppos);
		if (c != "price") ch(c).insert(val1, select);
		Book::modify(select, c, val);
	}
}

void Store::import(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	auto &&qua = command.substr(pos, npos - pos);
	std::stringstream ss(qua);
	int q = 0;
	ss >> q;
	double p = 0;
	std::stringstream sss(command.substr(npos + 1));
	sss >> p;
	std::fstream file("finance", std::ios::binary | std::ios::in | std::ios::out);
	file.seekp(0, std::ios::end);
	//std::cerr << file.tellp() << " " << -p << std::endl;
	writeDouble(file, -p);
	file.close();
	q += Book::queryq(select);
	Book::modifyq(select, q);
}

void Store::showFinance(std::string &command, int pos) {
	std::stringstream ss(command.substr(pos));
	int times = 0x3f3f3f3f;
	ss >> times;
	double income = 0, expense = 0;
	std::fstream file("finance", std::ios::binary | std::ios::in);
	file.seekg(0, std::ios::end);
	if (file.tellg() != 0) {
		int u = file.tellg();
		file.seekg(-1 * sizeof(double), std::ios::end);
		u = file.tellg();
		for (int i = 0; i < times; ++i) {
			u = file.tellg();
			double p = readDouble(file);
			//std::cerr << " " << file.tellg() << " " << p << std::endl;
			if (p > 0) income += p;
			else expense -= p;
			if (file.tellg() == sizeof(double)) break;
			file.seekg(-2 * sizeof(double), std::ios::cur);
		}
	}
	std::cout << "+ " << income << " - " << expense << "\n";
	file.close();
}

void Store::intersect(std::vector<int> &a, std::vector<int> b) {
	std::sort(b.begin(), b.end());
	std::vector<int> c;
	int j = 0;
	if (b.size() == 0) {
		a.clear();
		return;
	}
	for (int i = 0; i < a.size(); ++i) {
		while (j < b.size() - 1 && b[j] < a[i]) j++;
		if (b[j] == a[i]) c.push_back(a[i]);
	}
	a = c;
}
bool ISBNcmp(int x, int y) {
	return Book::getISBN(x) < Book::getISBN(y);
}
void Store::show(std::string &command, int pos) {
	bool flag = true;
	std::vector<int> ans;
	for (;;) {
		int npos = command.find(" ", pos);
		if (npos == -1) break;
		auto &&_ = command.substr(pos, npos - pos);
		int quo = _.find("\"");
		std::string c, val;
		if (quo == -1) {
			int equ = _.find("=");
			c = _.substr(1, equ - 1);
			val = _.substr(equ + 1);
			pos = npos + 1;
		}
		else {
			c = _.substr(1, quo - 2);
			int quo2 = command.find("\"", pos + quo + 1);
			val = command.substr(pos + quo + 1, quo2 - quo - pos - 1);
			pos = quo2 + 2;
		}
		if (flag) {
			ans = ch(c).find(val);
			std::sort(ans.begin(), ans.end());
			flag = false;
		}
		else {
			intersect(ans, ch(c).find(val));
		}
	}
	std::sort(ans.begin(), ans.end(), ISBNcmp);
	for (int i : ans) {
		Book::display(i);
	}
}

void Store::buy(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	auto &&isbn = command.substr(pos, npos - pos);
	auto &&now = ISBN.find(isbn);
	if (now.size() == 0) throw(std::invalid_argument("Invalid"));
	int sel = now[0];
	int q = Book::queryq(sel);
	auto &&p = Book::query(sel, "price");
	std::stringstream sss(p);
	double price = 0;
	sss >> price;
	std::stringstream ss(command.substr(npos + 1));
	int tq;
	ss >> tq;
	if (tq > q) throw(std::invalid_argument("Invalid"));
	std::fstream file("finance", std::ios::in | std::ios::out | std::ios::binary);
	file.seekp(0, std::ios::end);
	//std::cerr << file.tellp() << " " << price * tq << std::endl;
	writeDouble(file, price * tq);
	file.close();
	Book::modifyq(sel, q - tq);
}

void Store::su(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	std::string username = command.substr(pos, npos - pos);
	pos = npos + 1;
	npos = command.find(" ", pos);
	std::string password = command.substr(pos, npos - pos);
	auto &&nuser = findUser(username);
	if (password == nuser.password) {
		user = nuser;
		std::cerr << "Hello, " << user.name << "\n";
	}
	else throw(std::invalid_argument("Invalid"));
}

void Store::useradd(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	std::string username = command.substr(pos, npos - pos);
	pos = npos + 1;
	npos = command.find(" ", pos);
	std::string password = command.substr(pos, npos - pos);
	pos = npos + 1;
	char level = command[pos] - '0';
	//std::cout << (int)level << std::endl;
	pos += 2;
	npos = command.find(" ", pos);
	std::string name = command.substr(pos, npos - pos);
	if (level >= user.level) throw(std::domain_error("Invalid"));
	addUser(username, password, name, level);
}

void Store::reg(std::string &command, int pos) {
	if (pos == command.length()) throw(std::invalid_argument("Invalid"));
	int npos = command.find(" ", pos);
	std::string username = command.substr(pos, npos - pos);
	pos = npos + 1;
	if (pos == command.length()) throw(std::invalid_argument("Invalid"));
	npos = command.find(" ", pos);
	std::string password = command.substr(pos, npos - pos);
	pos = npos + 1;
	if (pos == command.length()) throw(std::invalid_argument("Invalid"));
	npos = command.find(" ", pos);
	std::string name = command.substr(pos, npos - pos);
	if (npos + 1 != command.length()) throw(std::invalid_argument("Invalid"));
	addUser(username, password, name, 1);
}

void Store::del(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	std::string username = command.substr(pos, npos - pos);
	deleteUser(username);
}

void Store::passwd(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	std::string username = command.substr(pos, npos - pos);
	pos = npos + 1;
	npos = command.find(" ", pos);
	std::string password1 = command.substr(pos, npos - pos);
	User tmp = findUser(username);
	if (user.level == 7) {
		//if(username == roo)user.password = password1;
		deleteUser(username);
		addUser(username, password1, tmp.name, tmp.level);
	}
	else {
		if (password1 != tmp.password) throw(std::invalid_argument("Invalid"));
		pos = npos + 1;
		npos = command.find(" ", pos);
		std::string passwd = command.substr(pos, npos - pos);
		deleteUser(username);
		addUser(username, passwd, tmp.name, tmp.level);
	}
}

void showall() {
	std::vector<int> &&a = Book::allList();
	std::sort(a.begin(), a.end(), ISBNcmp);
	for (int i : a) Book::display(i);
}

int Store::execute(std::string &command) {
	command += " ";
	int pos = command.find(" ");
	std::string t = command.substr(0, pos);
	if (t == "select") {
		++pos;
		valid(3);
		t = command.substr(pos, command.length() - pos - 1);
		auto &&_ = ISBN.find(t);
		if (_.size()) select = _[0];
		else {
			select = Book::insert();
			Book::modify(select, "ISBN", t);
			ISBN.insert(t, select);
		}
	}
	else if (t == "modify") {
		valid(3);
		modify(command, pos + 1);
	}
	else if (t == "import") {
		valid(3);
		if (select == -1) throw(std::invalid_argument("Invalid"));
		import(command, pos + 1);
	}
	else if (t == "show") {
		int npos = command.find(" ", pos + 1);
		if (command.substr(pos + 1, npos - pos - 1) == "finance") {
			valid(7);
			showFinance(command, npos + 1);
		}
		else {
			if (pos == command.length() - 1) {
				valid(1);
				showall();
			}
			else {
				valid(1);
				show(command, pos + 1);
			}
		}
	}
	else if (t == "buy") {
		valid(1);
		buy(command, pos + 1);
	}
	else if (t == "su") {
		su(command, pos + 1);
	}
	else if (t == "logout") {
		valid(1);
		std::string tmp;
		tmp.clear();
		user = User(tmp, tmp, tmp, 0);
	}
	else if (t == "useradd") {
		valid(3);
		useradd(command, pos + 1);
	}
	else if (t == "register") {
		reg(command, pos + 1);
	}
	else if (t == "delete") {
		valid(7);
		del(command, pos + 1);
	}
	else if (t == "passwd") {
		valid(1);
		passwd(command, pos + 1);
	}
	else if (t == "report") {
		int npos = command.find(" ", pos + 1);
		std::string str = command.substr(pos + 1, npos - pos - 1);
		pos = npos;
		if (str == "myself") {
			valid(3);
			Log::query(user.username);
		}
		else if (str == "finance") {
			valid(7);
		}
		else if (str == "employee") {
			valid(7);
			Log::queryall();
		}
		else {
			throw std::invalid_argument("Invalid");
		}
	}
	else if (t == "exit") {
		return 0;
	}
	else throw(std::invalid_argument("Invalid"));
	return 1;
}

int Store::load(std::string fileName) {
	std::ifstream loadFile(fileName);
	if (!loadFile.good()) throw(std::invalid_argument("Invalid"));
	char s[201];
	s[200] = '\0';
	while (loadFile.peek() != EOF) {
		loadFile.getline(s, 200);
		//std::cerr << (int)user.level << std::endl;
		std::string str = s;
		try {
			int p = execute(str);
			if (p == 0) {
				loadFile.close();
				return 0;
			}
		}
		catch (std::invalid_argument p) {
			std::cout << p.what() << "\n";
		}
		catch (std::domain_error p) {
			std::cout << p.what() << "\n";
		}
	}
	loadFile.close();
	return 1;
}