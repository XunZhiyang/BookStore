#include "newbie.h"
#include "store.h"
#include <iostream>
Newbie::Newbie(Store &_store) : store(&_store) {}
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
		std::cerr << "Please enter a number:\n";
		int ch;
		std::cin >> ch;
		getchar();
		switch (ch) {
		case(0):
			return 0;
			break;
		case(1):
			displayTutorial();
			break;
		case(2):
			return 1;
			break;
		default:
			break;
		}
	}
}