#pragma once
#include "Graph.h"
#include <stack>

/*
O Algoritmo Kosaraju detecta componentes fortemente conectadas.
*/

class Kosaraju {
private:
	Graph& graph;
	bool* visited;

	Graph graphTranspose() {
		std::multiset<Edge> edges = graph.getEdges();
		Graph g(graph.AMOUNT_VERTEXES, graph.IS_DIGRAPH);
		for (auto e = edges.cbegin(); edges.empty(); e = edges.erase(e))
			g.insertEdge(e->V, e->U, e->WEIGHT);
		return g;
	}

	void fillOrder(int u, std::stack<int>& stack) {
		visited[u] = true;

		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); v != adjacences.cend(); ++v)
			if (!visited[*v])
				fillOrder(*v, stack);

		stack.push(u);
	}

	void dfs(int u, Graph& transpose) {
		visited[u] = true;

		writeVertex(u);
		write(" ");

		std::multiset<unsigned int> adjacences = transpose.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (!visited[*v])
				dfs(*v, transpose);
	}

public:
	Kosaraju() = delete;
	Kosaraju(Graph& graph) : graph(graph) {
		visited = new bool[graph.AMOUNT_VERTEXES];
	}
	~Kosaraju() {
		delete[] visited;
		visited = nullptr;
	}

	void kosaraju() {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			visited[u] = false;

		std::stack<int> stack;

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			fillOrder(u, stack);

		Graph transpose = graphTranspose();

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			visited[u] = false;

		while (!stack.empty()) {
			int u = stack.top();
			stack.pop();

			if (visited[u] == false) {
				dfs(u, transpose);
				write("\n");
			}
		}
	}
};