#include <fstream>
#include "user.h"
#include "store.h"
Store::Store() {
	std::ifstream test("userData");
	if (!test.good()) {
		//std::ofstream userData("userData");
		addUser("root", "sjtu", 7);
	}
	user = findUser("root");
}