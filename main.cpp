#include <fstream>
#include <string>
#include <iostream>
#include "opfile.h"
#include "store.h"
#include "log.h"
#include "newbie.h"

int main() {
	std::cout.setf(std::ios::fixed);
	std::cout.precision(2);
	Store Bookstore;
	std::cerr << "Welcome to the bookstore administration system!\n";
	std::cerr << "           _____ __  __   ____   ____   ____  _  __ _____ _______ ____  _____  ______ \n     /\\   / ____|  \\/  | |  _ \\ / __ \\ / __ \\| |/ // ____|__   __/ __ \\|  __ \\|  ____|\n    /  \\ | |    | \\  / | | |_) | |  | | |  | | ' /| (___    | | | |  | | |__) | |__   \n   / /\\ \\| |    | |\\/| | |  _ <| |  | | |  | |  <  \\___ \\   | | | |  | |  _  /|  __|  \n  / ____ \\ |____| |  | | | |_) | |__| | |__| | . \\ ____) |  | | | |__| | | \\ \\| |____ \n /_/    \\_\\_____|_|  |_| |____/ \\____/ \\____/|_|\\_\\_____/   |_|  \\____/|_|  \\_\\______|\n";


	if (exist("command.txt")) {
		if (Bookstore.load("command.txt") == 0)  return 0;
	}
	std::cerr << "Do you know how to operate this system with command line?\n";
	std::cerr << "1 - Yes, I am an expert.\n";
	std::cerr << "2 - No, I am a newbie.\n";
	for (;;) {
		int ch = 5;
		std::string s;
		std::getline(std::cin, s, '\n');
		if (s[0] == '1') break;
		if (s[0] == '2') {
			int tmp = Newbie(Bookstore).friendly_operate();
			if (tmp == 0) return 0;
			else break;
		}
		std::cerr << "Please enter 1 or 2.\n";
	}
	char s[201];
	s[200] = '\0';
	int cntcnt = 0;
	for (;;) {
		if (Bookstore.user.username != "")
			std::cerr << Bookstore.user.name << "@" << Bookstore.user.username << ":";
		else std::cerr << "guest:";
		std::cin.getline(s, 200);
		if (!std::cin.good()) {
			std::cin.clear();
			std::cin.ignore(2147483644, '\n');
		}
		std::string str = s;
		if (str == "help") Newbie::displayTutorial();
		else if (str == "peppa") Newbie::peppa();
		else if (Bookstore.mainExecute(str) == 0) return 0;
	}
}
