#pragma once
#include "Graph.h"

/*O algoritmo de Prim */

class Prim {
private:
	const Graph& graph;
	int* key;
	int* pi;
	bool* visited;

	const unsigned int extractSmaller() const {
		int lowerValue = MAX_WEIGHT;
		unsigned int lowWeightVertex = 0;
		for (int unsigned u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (visited[u] == false && key[u] < lowerValue) {
				lowerValue = key[u];
				lowWeightVertex = u;
			}
		return lowWeightVertex;
	}

	void relax(const unsigned int& u, const unsigned int& v) const {
		if (graph.getWeigthFrom(u, v) < key[v]) {
			pi[v] = u;
			key[v] = graph.getWeigthFrom(u, v);
		}
	}

	void print() const {
		writeln("Prim:");
		write("Vi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
		}
		write("\nki  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeValue(key[i]);
			write('|');
		}
		write("\npi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(pi[i]);
			write('|');
		}
		write("\n");
	}

public:
	Prim() = delete;
	Prim(const Graph& graph) : graph(graph) {
		key = new int[graph.AMOUNT_VERTEXES];
		pi = new int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~Prim() {
		delete[] key;
		delete[] pi;
		delete[] visited;
		key = nullptr;
		pi = nullptr;
		visited = nullptr;
	}

	void prim(const unsigned int& origin)const {
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			key[i] = MAX_WEIGHT;
			pi[i] = NIL;
			visited[i] = false;
		}
		key[origin] = 0;
		int priorityQueue = graph.AMOUNT_VERTEXES;

		while (priorityQueue >= 0) {
			unsigned int u = extractSmaller();
			priorityQueue--;
			visited[u] = true;

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (visited[*v] == false)
					relax(u, *v);
		}
		print();
	}
};
