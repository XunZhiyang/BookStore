#pragma once
#include <string>
namespace Log {
	void record(std::string &&);

	void queryall();

	void query(std::string username);
}