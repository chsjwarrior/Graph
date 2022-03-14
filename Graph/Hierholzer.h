#pragma once
#include "NonCopyable.h"
#include <stack>
/*
O algoritmo de Hierholzer � utilizado para a identifica��o de um ciclo euleriano em um grafo.
*/
class Hierholzer : private NonCopyable {
private:
	Graph graph;

	void print(const std::string& title) const;

	const std::pair<unsigned int, std::pair<unsigned int, unsigned int>> validateGraph();

	void hierholzer(const unsigned int source, const unsigned int sink);

public:
	Hierholzer() = delete;
	Hierholzer(const Graph& graph) noexcept(false);
	~Hierholzer();

	void hierholzer();
};