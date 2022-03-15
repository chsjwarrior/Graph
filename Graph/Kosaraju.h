#pragma once
#include "NonCopyable.h"
#include <stack>
/*
O Algoritmo Kosaraju detecta componentes fortemente conectadas.
*/
class Kosaraju : private NonCopyable {
private:
	Graph graph;
	bool* visited;
	std::stack<int> stack;

	void fillOrder(const unsigned int u);

	void dfs(const unsigned int u);

public:
	Kosaraju() = delete;
	Kosaraju(Graph& graph) noexcept(false);
	~Kosaraju();

	void kosaraju();
};