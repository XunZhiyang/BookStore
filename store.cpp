//#include "pch.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include "user.h"
#include "book.h"
#include "opfile.h"
#include "store.h"

Store::Store() {
	if (!exist("userData")) {
		std::ofstream userData("userData");
		userData.close();
		std::ofstream bookData("bookData");
		bookData.close();
		addUser("root", "sjtu", "BOSS", 7);
	}
	ISBN = BlockList("ISBN");
	name = BlockList("name");
	author = BlockList("author");
	keyword = BlockList("keyword");
	user = findUser("root");
}	

BlockList &Store::ch(std::string listName) {
	if (listName == "ISBN") return ISBN;
	if (listName == "name") return name;
	if (listName == "author") return author;
	if (listName == "keyword") return keyword;
	throw(std::invalid_argument("Invalid blocklist"));
}

void Store::valid(int level) {
	if (user.level < level) throw(std::domain_error("Invalid level"));
}

void Store::modify(std::string &command, int pos) {
	if (select == -1) throw(std::invalid_argument("Invalid not selected"));
	for (;;) {
		int npos = command.find(" ", pos);
		if (npos == -1) break;
		auto _ = command.substr(pos, npos - pos);
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

		auto old = Book::query(select, c);
		int par = old.find("|");
		if (old[0] != '\0') {
			if (par == -1) ch(c).del(old, select);
			else {
				int ppos = 0;
				while (par != -1) {
					auto old1 = old.substr(ppos, par - ppos);
					ch(c).del(old1, select);
					ppos = par + 1;
					par = val.find("|", ppos);
				}
				auto old1 = old.substr(ppos);
				ch(c).del(old1, select);
			}
		}

		par = val.find("|");
		int ppos = 0;
		std::string val1;
		while (par != -1) {
			if (c != "keyword") throw(std::invalid_argument("Invalid with |"));
			val1 = val.substr(ppos, par - ppos);
			ch(c).insert(val1, select);
			ppos = par + 1;
			par = val.find("|", ppos);
		}
		val1 = val.substr(ppos);
		ch(c).insert(val1, select);
		Book::modify(select, c, val);
	}
}

void Store::import(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	auto qua = command.substr(pos, npos - pos);
	std::stringstream ss(qua);
	int q = 0;
	ss >> q;
	double p = 0;
	std::stringstream sss(command.substr(npos + 1));
	sss >> p;
	stack.push(-p * q);
	q += Book::queryq(select);
	Book::modifyq(select, q);
}

void Store::showFinance(std::string &command, int pos) {
	std::stringstream ss(command.substr(pos));
	int times = 0x3f3f3f3f;
	ss >> times;
	double income = 0, expense = 0;
	for (int i = 0; i < times; ++i) {
		if (stack.empty()) break;
		double p = stack.top();
		stack.pop();
		if (p > 0) income += p;
		else expense -= p;
	}
	std::cout << "+ " << income << " - " << expense << "\n";
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
		auto _ = command.substr(pos, npos - pos);
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
	auto isbn = command.substr(pos, npos - pos);
	auto now = ISBN.find(isbn);	
	if (now.size() == 0) throw(std::invalid_argument("Invalid no such book to be bought"));
	int sel = now[0];
	int q = Book::queryq(sel);
	auto p = Book::query(sel, "price");
	std::stringstream sss(p);
	double price;
	sss >> price;
	std::stringstream ss(command.substr(npos + 1));
	int tq;
	ss >> tq;
	if(tq > q) throw(std::invalid_argument("Invalid not enough books"));
	stack.push(price * tq);
	Book::modifyq(select, q - tq);
}

void Store::su(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	std::string username = command.substr(pos, npos - pos);
	pos = npos + 1;
	npos = command.find(" ", pos);
	std::string password = command.substr(pos, npos - pos);
	auto nuser = findUser(username);
	if (password == nuser.password) {
		user = nuser;
		std::cerr << "Hello, " << user.name << "\n";
	}
	else throw(std::invalid_argument("Invalid wrong password"));
}

void Store::useradd(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	std::string username = command.substr(pos, npos - pos);
	pos = npos + 1;
	npos = command.find(" ", pos);
	std::string password = command.substr(pos, npos - pos);
	pos = npos + 1;
	char level = command[pos] - '0';
	pos += 2;
	npos = command.find(" ", pos);
	std::string name = command.substr(pos, npos - pos);
	if(level > user.level) throw(std::domain_error("Invalid create user"));
	addUser(username, password, name, level);
}

void Store::reg(std::string &command, int pos) {
	int npos = command.find(" ", pos);
	std::string username = command.substr(pos, npos - pos);
	pos = npos + 1;
	npos = command.find(" ", pos);
	std::string password = command.substr(pos, npos - pos);
	pos = npos + 1;
	npos = command.find(" ", pos);
	std::string name = command.substr(pos, npos - pos);
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
	if (user.level == 7) {
		user.password = password1;
		deleteUser(user.username);
		addUser(user.username, user.password, user.name, user.level);
	}
	else {
		if (password1 != user.password) throw(std::invalid_argument("Invalid wrong passwd"));
		pos = npos + 1;
		npos = command.find(" ", pos);
		std::string passwd = command.substr(pos, npos - pos);
		user.password = passwd;
		deleteUser(user.username);
		addUser(user.username, user.password, user.name, user.level);
	}
}

int Store::execute(std::string &command) {
	command += " ";
	int pos = command.find(" ");
	std::string t = command.substr(0, pos);
	if (t == "select") {
		++pos;
		valid(3);
		t = command.substr(pos, command.length() - pos - 1);
		auto _ = ISBN.find(t);
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
		import(command, pos + 1);
	}
	else if (t == "show") {
		int npos = command.find(" ", pos);
		if (command.substr(pos, npos - pos) == "finance") {
			valid(7);
			showFinance(command, npos + 1);
		}
		else {
			valid(1);
			show(command, pos + 1);
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
		user = User("", "", "", 0);
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
	else if (t == "exit") {
		return 0;
	}
	else throw(std::invalid_argument("Invalid option"));
	return 1;
}

int Store::load(std::string fileName) {
	std::ifstream loadFile(fileName, std::ios::binary);
	if (!loadFile.good()) throw(std::invalid_argument("Invalid"));
	char s[201];
	s[200] = '\0';
	for (;;) {
		loadFile.getline(s, 200);
		std::string str = s;
		try {
			int p = execute(str);
			if (p == 0) break;
		}
		catch (std::invalid_argument p) {
			std::cout << p.what() << "\n";
		}
		catch (std::domain_error p) {
			std::cout << p.what() << "\n";
		}
	}
	loadFile.close();
}