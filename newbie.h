#pragma once
#include "store.h"
class Newbie {
private:
	Store *store;
	void help();
public:
	static void peppa();
	static void displayTutorial();
	Newbie(Store &);
	void hitMoney();
	int operate();
	int friendly_operate();
};