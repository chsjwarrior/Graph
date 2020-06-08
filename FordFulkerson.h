#pragma once
#include "Graph.h"

class FordFulkerson {
private:
	const Graph& graph;
	int** costMatrix;
	unsigned int* pi;

	const bool bfs(const unsigned int& u, const unsigned int& t) {
		bool* visited = new bool[graph.AMOUNT_VERTEXES];
		memset(visited, false, sizeof(visited));

		std::queue<unsigned int> queue;
		queue.push(u);
		visited[u] = true;
		pi[u] = NIL;
		while (!queue.empty()) {
			int v = queue.front();
			queue.pop();

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
				if (!visited[*v]) {
					queue.push(*v);
					pi[*v] = u;
					visited[*v] = true;
				}
			}
		}
		return (visited[t] == true);
	}

public:
	FordFulkerson() = delete;
	FordFulkerson(const Graph& graph) : graph(graph) {
		costMatrix = new int* [graph.AMOUNT_VERTEXES];
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
			costMatrix[i] = new int[graph.AMOUNT_VERTEXES];
		pi = new unsigned int[graph.AMOUNT_VERTEXES];
	}
	~FordFulkerson() {
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			delete[] costMatrix[i];
			costMatrix[i] = nullptr;
		}
		delete[] costMatrix;
		costMatrix = nullptr;
		delete[] pi;
		pi = nullptr;
	}

	void fordFulkerson(const unsigned int& origin, const unsigned int& destiny) {
		writeln("Ford-Fulkerson:");
		if (!graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser dirigido para o algoritmo de Ford-Fulkerson funcionar.");
			return;
		}

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			pi[u] = NIL;
			for (unsigned int v = 0; v < graph.AMOUNT_VERTEXES; v++)
				costMatrix[u][v] = graph.getWeigthFrom(u, v);
		}

		unsigned int u, v;
		int maxFlow = 0;

		while (bfs(origin, destiny)) {
			int pathFlow = MAX_WEIGHT;

			for (v = destiny; v != origin; v = pi[v]) {
				u = pi[v];
				pathFlow = std::min(pathFlow, graph.getWeigthFrom(u, v));
			}

			for (v = destiny; v != origin; v = pi[v]) {
				u = pi[v];
				costMatrix[u][v] -= pathFlow;
				costMatrix[v][u] += pathFlow;
			}

			maxFlow += pathFlow;
		}

		write("O fluxo maximo possivel e: ", maxFlow, "\n");
	}
};