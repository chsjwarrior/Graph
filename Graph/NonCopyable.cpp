#include "NonCopyable.h"

void NonCopyable::print(const std::string& text) const {
	std::cout << text;
}