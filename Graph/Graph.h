#pragma once
#include "ConsolePageTable.h"
#include <iomanip>
#include <algorithm>
#include <set>

inline constexpr unsigned int NIL = UINT_MAX;

inline constexpr int INF = 10000;

struct Edge {
	const unsigned int U, V;
	const int WEIGHT;

	Edge() = delete;

	explicit Edge(const unsigned int u, const unsigned int v, const int w);
	explicit Edge(const Edge& other);
	~Edge();

	bool operator<(const Edge& other) const;

	bool operator>(const Edge& other) const;

	Edge& operator=(const Edge&) = delete;	
};

class Graph {
private:
	mutable std::multiset<unsigned int> adjacences;
	std::multiset<Edge> edges;
	/*
	O conjunto de arestas do grafo armazena apenas as aresta u->v de um grafo não dirigido.
	Significa que as arestas v->u são encontradas pela conta-parte u->v.
	*/

public:
	const unsigned int AMOUNT_VERTEXES;
	const bool IS_DIGRAPH;

	Graph() = delete;

	explicit Graph(const unsigned int amountVertexes, const bool isDigraph) noexcept(false);
	explicit Graph(const Graph& other);
	~Graph();

	bool isValidVertex(const unsigned int v) const noexcept;

	bool isValidWeight(const int w) const noexcept;

	void insertEdge(const unsigned int u, const unsigned int v, const int weight = 1) noexcept(false);

	void removeEdge(const unsigned int u, const unsigned int v) noexcept(false);

	int getWeigthFrom(const unsigned int u, const unsigned int v) const noexcept(false);

	unsigned int getInDegreeFrom(const unsigned int v) const noexcept(false);

	//esse método tambem é usuado para grafos não dirigidos
	unsigned int getOutDegreeFrom(const unsigned int v) const noexcept(false);

	std::multiset<unsigned int>& getAdjacencesFrom(const unsigned int v) const noexcept(false);

	std::multiset<Edge> getEdges() const;

	size_t getAmountEdges() const;

	void transpose();

	void printAdjacencematrix() const;

	void printIncidenceMatrix() const;

	void printAdjacenceList() const;

	void printIncidenceList() const;

	void printCostMatrix() const;

	void printGraphInfo() const;

	void printVerticesToSelect() const;

	const std::string getVertexName(const unsigned int vertex) const;

	const std::string getFormatedWeight(const int weight) const;

	const std::string getEdgeName(const Edge& edge) const;

	void writeVertex(const unsigned int vertex) const;

	void writeEdge(const Edge& edge) const;

	void writeEdge(const unsigned int edge) const;

	void writeValue(const int value) const;
};