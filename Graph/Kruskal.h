#pragma once
#include "NonCopyable.h"
/*
O algoritmo de Kruskal � um algoritmo em teoria dos grafos que busca uma �rvore geradora m�nima (minimal spanning tree) em um grafo conexo ponderado.
Isto significa que ele encontra um subconjunto das arestas que forma uma arvore que inclui todos os vertices,
onde o peso total � dado pela soma dos pesos das arestas da �rvore de menor valor.
Se o grafo n�o for conexo, ent�o ele encontra uma floresta geradora m�nima (uma �rvore geradora m�nima para cada componente conexo do grafo).
O algoritmo de Kruskal � um exemplo de um algoritmo guloso (tamb�m conhecido como ganancioso ou greedy).
*/
class Kruskal : private NonCopyable {
private:
	const Graph& graph;

	struct LessWeight {
		const bool operator()(const Edge& lhs, const Edge& rhs) const {
			return lhs.WEIGHT < rhs.WEIGHT;
		}
	};

	std::pair<unsigned int, unsigned int>* subsets;
	//pair.first = parent;
	//pair.second = rank;

	void print(const std::string& title) const;

	unsigned int find(const unsigned int u);

	void makeUnion(const unsigned int u, const unsigned int v);

	inline void makeSet(const unsigned int v);

	std::multiset<Edge, LessWeight> getEdgesLessWeight();

public:
	Kruskal() = delete;
	Kruskal(const Graph& graph) noexcept(false);
	~Kruskal();

	void kruskal();
};