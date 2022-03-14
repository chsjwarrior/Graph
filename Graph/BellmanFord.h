#pragma once
#include "NonCopyable.h"
/*
O Algoritmo de Bellman-Ford é um algoritmo de busca de caminho minimo em um digrafo (grafo orientado ou dirigido) e ponderado, inclusive negativo.
O Algoritmo de Dijkstra resolve o mesmo problema, num tempo menor, porém exige que todas as arestas tenham pesos positivos.
Assim como o algoritmo de Dijkstra, o algoritmo de Bellman-Ford utiliza a técnica de relaxamento.
A principal diferença entre Dijkstra e Bellman-Ford é que no algoritmo de Bellman-Ford se relaxa todas as arestas.
*/
class BellmanFord : private NonCopyable {
private:
	const Graph& graph;
	int* distance;
	unsigned int* predecessor;

	void print(const std::string& title) const;

public:
	BellmanFord() = delete;
	BellmanFord(const Graph& graph) noexcept(false);
	~BellmanFord();

	void bellmanFord(const unsigned int source);
};