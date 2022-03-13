#pragma once
#include "NonCopyable.h"
#include <stack>
/*
O algoritmo da busca em profundidade (Depth-First Search - DFS)  e utilizado para realizar uma busca em estrutura de dados do tipo arvore.
O algoritmo come�a em um vertice raiz e explora tanto quanto poss�vel cada um dos seus ramos, antes de retroceder (backtracking).
*/
class DepthFirstSearch : private NonCopyable {
private:
	const Graph& graph;
	unsigned int* discovery;
	unsigned int* close;
	bool* visited;
	unsigned int time;

	void dfsVisitRecursive(const unsigned int u);

	void dfsVisitIterative(unsigned int u);

	void print(const std::string& title) const;

public:
	DepthFirstSearch() = delete;
	explicit DepthFirstSearch(const Graph& graph) noexcept(false);
	~DepthFirstSearch();

	void dfs(const unsigned int source, const bool isRecursive);
};