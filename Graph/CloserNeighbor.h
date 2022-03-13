#pragma once
#include "NonCopyable.h"
/*
O algoritmo do vizinho mais pr�ximo e usado para determinar uma solu��o para o problema do problema do caixeiro viajante.
Ele gera rapidamente um caminho curto, mas geralmente n�o o ideal.
O algoritmodo do vizinho mais pr�ximo realiza um tipo de uma busca em profundidade escolhendo o vertice de menor custo.
E pode encontrar um ciclo hamiltoniano.
*/
class CloserNeighbor : private NonCopyable {
private:
	const Graph& graph;
	bool* visited;
	int total;

	void closerNeighborR(const unsigned int u);

public:
	CloserNeighbor() = delete;
	CloserNeighbor(const Graph& graph) noexcept(false);
	~CloserNeighbor();

	void closerNeighbor(const unsigned int source);

	void closerNeighborRepetitive();
};