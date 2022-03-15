#pragma once
#include "NonCopyable.h"

/*
O algoritmo de Floud-Warschall resolver o problema do caminho mínimo com várias origens em um grafo ponderado com valores positivos e negativos.
cada linha da matriz indica a mesma distancia do algoritmo de Dijkstra.
*/
class FloydWarshall : private NonCopyable {
	const Graph& graph;
	int** costMatrix;
	unsigned int** predecessor;

	void print(const std::string& text) const override;

public:
	FloydWarshall() = delete;
	FloydWarshall(const Graph& graph) noexcept(false);
	~FloydWarshall();

	void floydWarshall();
};