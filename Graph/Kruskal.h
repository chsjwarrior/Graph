#pragma once
#include "NonCopyable.h"
/*
O algoritmo de Kruskal é um algoritmo em teoria dos grafos que busca uma árvore geradora mínima (minimal spanning tree) em um grafo conexo ponderado.
Isto significa que ele encontra um subconjunto das arestas que forma uma arvore que inclui todos os vertices,
onde o peso total é dado pela soma dos pesos das arestas da árvore de menor valor.
Se o grafo não for conexo, então ele encontra uma floresta geradora mínima (uma árvore geradora mínima para cada componente conexo do grafo).
O algoritmo de Kruskal é um exemplo de um algoritmo guloso (também conhecido como ganancioso ou greedy).
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