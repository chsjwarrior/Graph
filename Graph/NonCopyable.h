#pragma once
#include "Graph.h"

struct NonCopyable {
	NonCopyable() = default;
	virtual ~NonCopyable() = default;

	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

	virtual void print(const std::string& title) const = 0;
};