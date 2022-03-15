#pragma once
#include "NonCopyable.h"
#include <stack>
/*
O algoritmo da busca em profundidade (Depth-First Search - DFS)  e utilizado para realizar uma busca em estrutura de dados do tipo arvore.
O algoritmo começa em um vertice raiz e explora tanto quanto possível cada um dos seus ramos, antes de retroceder (backtracking).
*/
class DepthFirstSearch : private NonCopyable {
private:
	const Graph& graph;
	unsigned int* discovery;
	unsigned int* close;
	bool* visited;
	unsigned int time;

	void print(const std::string& text) const override;

	void dfsVisitRecursive(const unsigned int u);

	void dfsVisitIterative(unsigned int u);	

public:
	DepthFirstSearch() = delete;
	explicit DepthFirstSearch(const Graph& graph) noexcept(false);
	~DepthFirstSearch();

	void dfs(const unsigned int source, const bool isRecursive);
};