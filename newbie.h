#pragma once
#include "store.h"
class Newbie {
private:
	Store *store;
	void displayTutorial();
public:
	Newbie(Store &);
	int operate();
};