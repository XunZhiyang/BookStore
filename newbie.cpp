#include "newbie.h"
#include "store.h"
#include <string>
#include <iostream>
Newbie::Newbie(Store &_store) : store(&_store) {}
void Newbie::hitMoney() {
	std::cerr << "=@@@@@@@@@@@@@^ ,@^   =@@@^ =@@@^       O@@@` =@@@. =@@@@@@@@@@@@O\n";
	std::cerr << "=@O         =@^ .@^       =@@@@@@@^ =@^ O@^   =@@@. =@.         @O\n";
	std::cerr << "=@O =@@@@@^ =@^ .@@@@@@@^   =@^ =@@@@@@@@@@@.       =@. =@@@@@. @O\n";
	std::cerr << "=@O =@@@@@^ =@^       =@@@^   =@@@^   =@. =@@@^ =@. =@. =@@@@@. @O\n";
	std::cerr << "=@O =@@@@@^ =@^         =@^ =@^   =@@@^     O@^     =@. =@@@@@. @O\n";
	std::cerr << "=@O         =@^ .@@@@@@@^ =@@@^ =@@@^   O@@@. =@@@. =@.         @O\n";
	std::cerr << "=@@@@@@@@@@@@@^ .@^ =@^ =@^ =@^ =@^ =@^ O@^ O@^ =@. =@@@@@@@@@@@@O\n";
	std::cerr << ".@^       =@^ =@@@@@^ =@@@@@@@@@^                 \n";
	std::cerr << "=@@@@@^ =@^ .@^ =@^   =@@@^   =@^ =@.     =@^ @@@@@@^   @@@@@O\n";
	std::cerr << ".@^ .@@@^   =@O =@@@@@^               O@@@@@@@^         O@      \n";
	std::cerr << ".@@@@@@@^ =@@@@@^ =@@@^ =@@@@@@@^ =@@@. =@.   =@.       O@@@.   \n";
	std::cerr << "=@@@^         =@O       =@^   =@^ =@@@^   =@@@@@@@. =@.     @@@@@O\n";
	std::cerr << ".@^ .@@@^ =@@@O =@^   =/]]]]]]]]]]]]/]/@@@.   =@@@^ O@^   @@@@@O\n";
	std::cerr << ".@@@^           =@^O@@@@@@@@@@@@@@@^^ O@^ =@    O@^ O@  /@@O\n";
	std::cerr << ".@^ .@@@@@@@@@@@^   =@^O@@@/......,@@@@^=@@@^     =@@@^   @@.   \n";
	std::cerr << "=@O     =@^   =@O =@^    O@@^.......*=@@@^^ O@^ =@@@^ O@@@@@@@. @O\n";
	std::cerr << "=@@@^ =@@@^ .@^ =@@@^O@@\\\\]...,..\\O@@^  O@@@^ @@^     O@@@@@  \n";
	std::cerr << "=@O   .@@@@@^       =@^ .O@@@@\\`....=O@@@^=@.     @@^ O@^   @@. @O\n";
	std::cerr << "=@@@@@^ =@@@O   =@^ .O@@@@O[,*O@@@@@@^=@@@@@^ @@^ O@^ O@@@.   \n";
	std::cerr << "=@O =@O   =@^     =@@@^ ,O@@@@@@@@@@@@@@@\\^ O@^     =@@@^       @O\n";
	std::cerr << ".@@@O =@@@@@@@O =@@@@@@\\/[[[[[[[[[[[[[.     =@@@. =@@@@@.     @O\n";
	std::cerr << "=@@@^   =@^     .@@@@@@@@@@@@@@@@@@@@@@@@@^ O@^ =@.     =@@@      \n";
	std::cerr << "=@O     =@^ =@^     =@^ =@@@@@@@@@@@@@@@@@^     =@@@^   =@.   O@@O\n";
	std::cerr << "=@O =@@@^ =@^     =@^ =@^ =@^   =@^   =@@@^     =@  =@.     @@@@  \n";
	std::cerr << "=@O     =@^ =@@@O   =@^ =@@@@@^ =@@@@@@@. =@@@^ =@@@@@@@@@@@  O@@O\n";
	std::cerr << ".@@@@@^   =@^   =@^ =@^     O@^ =@      =@@@@@.   \n";
	std::cerr << "=@@@@@@@@@@@@@^           =@@@^ =@^ =@@@.   O@@@@@. =@. =@.     @O\n";
	std::cerr << "=@O         =@^   =@@@@@@@@@@@@@@@^ =@^ O@^     =@.     =@. @@@@  \n";
	std::cerr << "=@O =@@@@@^ =@^ .@^   =@^   =@`       =@. =@@@@@@@@@@@@@@@.   O@@\\\n";
	std::cerr << "=@O =@@@@@^ =@^ .@^ =@^ =@@@@@@@@@@@^     =@.   =@    O@@@. @@@@  \n";
	std::cerr << "=@O =@@@@@^ =@^ .@^ =@@@@@^ =@@@^ =@^   O@^ O@@@^ @@@@.           \n";
	std::cerr << "=@O         ,@^       =@@@@@@@^ =@^   =@@@@@@@^   @@^ O@@@@@@@. @\\\n";
	std::cerr << "=@@@@@@@@@@@@@^   =@^ =@^             =@. =@@@@@@@.   O@@@.       \n";
}
void Newbie::peppa() {
	std::cerr << " \n";
	std::cerr << "                                    //==\\\\\n";
	std::cerr << "                                   /.....|\n";
	std::cerr << "                                  |......|\n";
	std::cerr << "                                  |......|         ==\\\n";
	std::cerr << "     //=...\\\\\\=......=========    |...../       /....\\|\n";
	std::cerr << "   //........\\\\................===\\\\..//       /......|\n";
	std::cerr << " //...........||......./===\\........\\\\\\\\      |......|\n";
	std::cerr << " ||.@@.........|.....//     \\\\..........\\\\\\  |....../\n";
	std::cerr << " |........@@..||.....|   @@  |.//   \\\\\\....=\\|\\...//\n";
	std::cerr << " ||.........../......\\\\  @  //||      ||.......\\\\\\\n";
	std::cerr << "  \\\\........//.........\\===/..||  @@@ ||..........\\\\\n";
	std::cerr << "    \\\\====//...................\\\\\\ =///............\\\\\n";
	std::cerr << "       \\\\\\...........................................\\\\\n";
	std::cerr << "         \\\\\\..........................................\\\\\n";
	std::cerr << "            \\\\\\\\..............................!!!!!....|\n";
	std::cerr << "                ||..........................!!!!!!!!!..||\n";
	std::cerr << "                |..........................!!!!!!!!!!!..|\n";
	std::cerr << "                |....|.....................!!!!!!!!!!!..|\n";
	std::cerr << "                |..........................!!!!!!!!!!...|\n";
	std::cerr << "                ||....\\\\....................!!!!!!!....||\n";
	std::cerr << "                 |......\\\\........../..................|\n";
	std::cerr << "                 \\\\.......\\======/....................//\n";
	std::cerr << "                  \\\\.................................//\n";
	std::cerr << "                    \\\\.............................//\n";
	std::cerr << "                     \\\\...........................//\n";
	std::cerr << "                       \\\\\\.....................///\n";
	std::cerr << "                          \\\\\\=.............=///\n";
	std::cerr << "                               ===========\n";
}
void Newbie::displayTutorial() {
	std::cerr << "You should register/login before any of your operations.\n";
	getchar();
	std::cerr << "register [user©\id] [passwd] [name] : register a customer account.\n";
	std::cerr << "su [user©\id] [passwd] : sign in to an account.\n";
	getchar();
	std::cerr << "Then you can do the operations below.\n";
	getchar();
	std::cerr << "logout : Sign out of your account.\n";
	std::cerr << "passwd [user©\id] [old©\passwd] [new©\passwd] £ºChange password.\n";
	std::cerr << "show ©\ISBN=[ISBN] ©\name=[name] ©\author=[author] ©\keyword=[keyword] : Show books requiring those conditions.\n";
	std::cerr << "buy [ISBN] [quantity] : Buy a book!\n";
	getchar();
	peppa();
	getchar();
}
int Newbie::operate() {
	std::cerr << "Welcome to the tutorial!\n";
	getchar();
	displayTutorial();
	for (;;) {
		std::cerr << "0 - exit   1 - display tutorial again   2 - access full version\n";
		std::cerr << "Please enter a number:";
		std::string s;
		std::getline(std::cin, s, '\n');
		switch (s[0]) {
		case('0'):
			return 0;
			break;
		case('1'):
			displayTutorial();
			break;
		case('2'):
			return 1;
			break;
		default:
			break;
		}
	}
}
void Newbie::help() {
	std::cerr << "0 - login \n1 - register \n2 - logout\n3 - change password\n";
	std::cerr << "4 - retrieve book information \n5 - select a book \n6 - purchase a book\n";
	std::cerr << "7 - watch expert version tutorial \n8 - access expert version\n9 - exit\n";
}
int Newbie::friendly_operate() {
	help();
	for (;;) {
		std::cerr << "Please enter a number:";
		std::string s;
		std::getline(std::cin, s, '\n');
		std::string command;
		bool flag = true;
		if (s == "help") help();
		else if (s == "money") hitMoney();
		else {
			switch (s[0]) {
			case('0'): {
				int p = 0;
				std::string username, password;
				std::cerr << "Username:";
				std::getline(std::cin, username, '\n');
				std::cerr << "Password:";
				std::getline(std::cin, password, '\n');
				command = "su " + username + " " + password;
				break;
			}
			case('1'): {
				std::string username, password, name;
				std::cerr << "Username:";
				std::getline(std::cin, username, '\n');
				std::cerr << "Password:";
				std::getline(std::cin, password, '\n');
				std::cerr << "Name:";
				std::getline(std::cin, name, '\n');
				command = "register " + username + " " + password + " " + name;
				break;
			}
			case('2'):
				command = "logout";
				break;
			case('3'): {
				command = "passwd";
				std::string info;
				std::cerr << "username = ";
				std::getline(std::cin, info, '\n');
				command += " " + info;
				std::cerr << "old password = ";
				std::getline(std::cin, info, '\n');
				command += " " + info;
				std::cerr << "new password = ";
				std::getline(std::cin, info, '\n');
				command += " " + info;
				break;
			}
			case('4'): {
				command = "show";
				std::string info;
				std::cerr << "ISBN = ";
				std::getline(std::cin, info, '\n');
				if (info != "") command += " -ISBN=" + info;
				std::cerr << "name = ";
				std::getline(std::cin, info, '\n');
				if (info != "") command += " -name=\"" + info + "\"";
				std::cerr << "author = ";
				std::getline(std::cin, info, '\n');
				if (info != "") command += " -author=\"" + info + "\"";
				std::cerr << "keyword = ";
				std::getline(std::cin, info, '\n');
				if (info != "") command += " -keyword=\"" + info + "\"";
				break;
			}
			case('5'): {
				std::string info;
				std::cerr << "ISBN = ";
				std::getline(std::cin, info, '\n');
				command = "select " + info;
				break;
			}
			case('6'): {
				command = "buy ";
				std::string info;
				std::cerr << "ISBN = ";
				std::getline(std::cin, info, '\n');
				command += info;
				std::cerr << "quantity you want to buy: ";
				std::getline(std::cin, info, '\n');
				command += " " + info;
				break;
			}
			case('7'):
				displayTutorial();
				flag = false;
				break;
			case('8'):
				return 1;
				break;
			case('9'):
				return 0;
				break;
			default:
				std::cerr << "Please enter a number between zero and seven.\n\n";
				flag = false;
			}
			if (flag) store->mainExecute(command);
		}
	}
}