#pragma once
#include "Graph.h"

class NonCopyable {
protected:
	NonCopyable() = default;
	virtual ~NonCopyable() = default;

	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

	virtual void print(const std::string& text) const;
};

