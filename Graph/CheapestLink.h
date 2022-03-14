#pragma once
#include "NonCopyable.h"
/*
O algoritmo da ligação mais economica encontra um ciclo hamiltoniano no grafo passando pelas aresta com menor peso.
Essa implementação do algoritmo ainda não esta funcionando para grafos semi-hamiltoniano.
testado e funcionando com o seguinte grafo:
5 10 0
1 2 185
1 3 119
1 4 152
1 5 133
2 3 121
2 4 150
2 5 200
3 4 174
3 5 120
4 5 199
*/
class CheapestLink : private NonCopyable {
private:
	const Graph& graph;
	unsigned int* degrees;
	bool* visited;

	struct GreaterWeight {
		const bool operator()(const Edge& lhs, const Edge& rhs) const {
			return lhs.WEIGHT > rhs.WEIGHT;
		}
	};

	std::multiset<Edge, GreaterWeight> edges;
	std::vector<Edge> selected;

	void print(const std::string& title) const;

	bool cyclic_recursive(const unsigned int vertex, const  unsigned int predecessor);

	bool cyclic();	

public:
	CheapestLink() = delete;
	CheapestLink(const Graph& graph) noexcept(false);
	~CheapestLink();

	void cheapestLink();
};