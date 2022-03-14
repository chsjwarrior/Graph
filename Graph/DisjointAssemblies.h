#pragma once
#include "NonCopyable.h"
#include <list>
/*
O algoritmo de DisjointAssebblies serve para avaliar a conexidade em grafos não dirigidos.
funcionando
*/
class DisjointAssemblies : private NonCopyable {
private:
	const Graph& graph;
	std::multiset<Edge> edges;
	std::list<std::set<unsigned int>> sets;

	void print(const std::string& title) const;

	void sameComponent(const unsigned int u, const unsigned int v);

	void makeSet(const unsigned int u);	

public:
	DisjointAssemblies() = delete;
	DisjointAssemblies(const Graph& graph);
	~DisjointAssemblies();

	void connectedComponents();
};