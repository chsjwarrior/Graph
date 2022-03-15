#pragma once
#include "NonCopyable.h"
/*
O algoritmo de Fleury � utilizado para a identifica��o de um ciclo euleriano em um grafo.

//tem que descobrir se o algoritmo de Fleury funciona em grafo dirigidos ou n�o.
 funcionando, mas � preciso testar de outras maneiras ainda.
 funcionou com seguinte grafo:
4 5 0
1 2 0
1 4 0
2 3 0
2 3 0
2 4 0
4 4 0
*/
class Fleury : private NonCopyable {
private:
	Graph graph;
	bool* visited;

	bool isConnected();

	const std::pair<unsigned int, unsigned int> validateGraph();

	unsigned int dfsUtil(const unsigned int u);

	bool isBridge(const unsigned int u, const unsigned int v);

	void fleuryR(const unsigned int u);

public:
	Fleury() = delete;
	Fleury(const Graph& graph) noexcept(false);
	~Fleury();

	void fleury();
};