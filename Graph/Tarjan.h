#pragma once
#include "NonCopyable.h"
#include <stack>
/*
Parcialmente funcionando
*/
class Tarjan : private NonCopyable {
private:
	const Graph& graph;
	unsigned int* discovery;
	unsigned int* low;
	bool* onStack;
	unsigned int time;
	unsigned int setCount;
	std::stack<unsigned int> stack;

	void strongConnected(const unsigned int u);

public:
	Tarjan() = delete;
	Tarjan(const Graph& graph) noexcept(false);
	~Tarjan();

	void tarjan();
};