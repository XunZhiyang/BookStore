#pragma once
#include "store.h"
class Newbie {
private:
	Store *store;
	static void peppa();
	void displayTutorial();
public:
	Newbie(Store &);
	int operate();
};