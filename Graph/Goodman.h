#pragma once
#include "NonCopyable.h"
#include <list>
/*
O algoritmo de Goodman serve para avaliar a conexidade em grafos não dirigidos.

falhou no seguinte grafo:
8 8 0
1 3 3
2 3 2
3 4 4
3 5 5
4 7 3
5 7 5
5 6 1
5 8 7
*/
class Goodman : private NonCopyable {
private:
	Graph graph;
	std::set<unsigned int> vertices;
	std::list<std::list<unsigned int>> sets;

	void print(const std::string& text) const override;

	void makeSet(const unsigned int u);
	
public:
	Goodman() = delete;
	Goodman(const Graph& graph) noexcept(false);
	~Goodman();

	void goodman();
};