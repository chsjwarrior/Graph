#pragma once
#include "Graph.h"

using namespace Scanner;

/*
O algoritmo de Dijkstra resolve o problema do caminho mínimo com uma origem.
Mas esse algoritmo só funciona com grafos valorados com valores positivos.
funcionando.
*/

class Dijkstra {
private:
	const Graph& graph;
	int* distance;
	int* pi;
	bool* visited;

	const unsigned int extractSmaller() const {
		int lowerValue = MAX_WEIGHT;
		unsigned int lowWeightVertex = 0;
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (visited[u] == false && distance[u] < lowerValue) {//distance[u] <= lowerValue, verificar
				lowerValue = distance[u];
				lowWeightVertex = u;
			}
		return lowWeightVertex;
	}

	void relax(const unsigned int& u, const unsigned int& v) const {
		if (distance[v] > distance[u] + graph.getWeigthFrom(u, v)) {
			distance[v] = distance[u] + graph.getWeigthFrom(u, v);
			pi[v] = u;
		}
	}

	void print() const {
		writeln("Dijkstra:");
		write("Vi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
		}
		write("\ndi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeValue(distance[i]);
			write("|");
		}
		write("\npi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(pi[i]);
			write("|");
		}
		write("\n");
	}

public:
	Dijkstra() = delete;
	Dijkstra(const Graph& graph) : graph(graph) {
		pi = new int[graph.AMOUNT_VERTEXES];
		distance = new int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~Dijkstra() {
		delete[] pi;
		delete[] distance;
		delete[] visited;
		pi = nullptr;
		distance = nullptr;
		visited = nullptr;
	}

	void dijkstra(const unsigned int& origin) const {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			distance[u] = MAX_WEIGHT;
			pi[u] = -1;
			visited[u] = false;
		}
		distance[origin] = 0;
		unsigned int priorityQueue = 0;

		while (priorityQueue < graph.AMOUNT_VERTEXES) {
			unsigned int u = extractSmaller();
			priorityQueue++;
			visited[u] = true;

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (graph.getWeigthFrom(u, *v) > 0)//se o peso é negativo deveria anular o programa.
					relax(u, *v);
		}
		print();
	}
};