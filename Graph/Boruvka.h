#pragma once
#include "NonCopyable.h"
/*
O algoritmo de Boruvka serve para encontrar a arvore geradora m�nima (minimal spanning tree) em um grafo n�o direcionado e ponderado.
Isto significa que ele encontra um subconjunto das arestas que forma uma arvore que inclui todos os vertices,
onde o peso total � dado pela soma dos pesos das arestas da �rvore de menor valor.
Outros algoritmos conhecidos para encontrar �rvores geradoras m�nimas s�o o algoritmo de Kruskal e algoritmo de Prim.
Enquanto o algoritmo de Prim e o algor�tmo de Kruskal precisam de um grafo conexo para funciona, o algoritmo de Boruvka pode ser empregado em grafos desconexos.
*/
class Boruvka : private NonCopyable {
private:
	const Graph& graph;
	unsigned int* cheapest;
	std::pair<unsigned int, unsigned int>* subsets;
	//pair.first = parent;
	//pair.second = rank;
	std::vector<Edge> edges;

	void print(const std::string& title) const;

	unsigned int find(const unsigned int u);

	void makeUnion(const unsigned int u, const unsigned int v);

	void makeSet();	

public:
	Boruvka() = delete;
	Boruvka(const Graph& graph) noexcept(false);
	~Boruvka();

	void boruvka();
};