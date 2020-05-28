#pragma once
#include "Graph.h"

using namespace Scanner;

/*
funcionando.
*/

class CloserNeighbor {
private:
	const Graph& graph;
	bool* visited;

	void closerNeighborR(const unsigned int& u) const {
		visited[u] = true;
		writeVertex(u);

		bool found = false;
		unsigned int v = 0;
		int weight = MAX_WEIGHT;
		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto vv = adjacences.cbegin(); !adjacences.empty(); vv = adjacences.erase(vv))
			if (!visited[*vv])
				if (graph.getWeigthFrom(u, *vv) < weight) {
					found = true;
					v = *vv;
					weight = graph.getWeigthFrom(u, *vv);
				}
		if (found) {
			write("->");
			closerNeighborR(v);
		}
	}

public:
	CloserNeighbor() = delete;
	CloserNeighbor(const Graph& graph) : graph(graph) {
		visited = new bool[graph.AMOUNT_VERTICES];
	}

	~CloserNeighbor() {
		delete[] visited;
		visited = nullptr;
	}

	void closerNeighbor(const unsigned int origin) const {
		for (unsigned int i = 0; i < graph.AMOUNT_VERTICES; i++)
			visited[i] = false;
		writeln("Vizinho mais proximo:");
		closerNeighborR(origin);
		write("\n");
	}

	void closerNeighborRepetitive() const {
		writeln("Vizinho mais proximo repetitivo:");
		for (unsigned int u = 0; u < graph.AMOUNT_VERTICES; u++) {
			for (unsigned int i = 0; i < graph.AMOUNT_VERTICES; i++)
				visited[i] = false;
			closerNeighborR(u);
			write("\n");
		}
	}
};