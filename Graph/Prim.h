#pragma once
#include "NonCopyable.h"
#include <list>
/*
O algoritmo de Prim é empregado para encontrar uma arvore geradora minima (minimal spanning tree) num grafo conexo, valorado e não direcionado.
Isto significa que ele encontra um subgrafo que forma uma arvore que inclui todos os vertices,
onde o peso total é dado pela soma dos pesos das arestas da árvore de menor valor.
*/
class Prim : private NonCopyable {
private:
	const Graph& graph;
	int* key;
	unsigned int* predecessor;
	bool* visited;

	unsigned int extractMin(std::list<unsigned int>& queue);

	inline void relax(const unsigned int u, const unsigned int v, const int w);

	void print() const;

public:
	Prim() = delete;
	Prim(const Graph& graph) noexcept(false);
	~Prim();

	void prim(const unsigned int source);
};