#pragma once
#include "NonCopyable.h"
#include <list>

/*
O algoritmo de Dijkstra soluciona o problema do caminho mais curto num grafo dirigido ou n�o dirigido com arestas de peso n�o negativo.
O algoritmo que serve para resolver o mesmo problema em um grafo com pesos negativos � o algoritmo de Bellman-Ford, que possui maior tempo de execu��o que o Dijkstra.
*/
class Dijkstra : private NonCopyable {
	const Graph& graph;
	int* distance;
	unsigned int* predecessor;
	bool* visited;

	void print(const std::string& text) const override;

	unsigned int extractMin(std::list<unsigned int>& queue);

	inline void relax(const unsigned int u, const unsigned int v, const int w);

public:
	Dijkstra() = delete;
	Dijkstra(const Graph& graph) noexcept(false);
	~Dijkstra();

	void dijkstra(const unsigned int source);
};