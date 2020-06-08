#pragma once
#include "Graph.h"

class FordFulkerson {
private:
	const Graph graph;
	unsigned int* parent;

	const bool bfs(const unsigned int& u, const unsigned int& t) {
		bool* visited = new bool[graph.AMOUNT_VERTEXES];
		memset(visited, 0, sizeof(visited));

		std::queue<unsigned int> queue;
		queue.push(u);
		visited[u] = true;
		parent[u] = -1;
		while (!queue.empty()) {
			int v = queue.front();
			queue.pop();
			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
				if (!visited[*v]) {
					queue.push(*v);
					parent[*v] = u;
					visited[*v] = true;
				}
			}
		}
		return (visited[t] == true);
	}

public:
	FordFulkerson() = delete;
	FordFulkerson(const Graph& graph) : graph(graph) {
		unsigned int* parent = new unsigned int[graph.AMOUNT_VERTEXES];
	}
	~FordFulkerson() {
		delete[] parent;
		parent = nullptr;
	}

	void fordFulkerson(const unsigned int& origin, const unsigned int& destiny) {
		writeln("Ford-Fulkerson:");
		if (!graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser dirigido para o algoritmo de Ford-Fulkerson funcionar.");
			return;
		}

		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
			parent[i] = 0;

		unsigned int u, v;
		int maxFlow = 0;

		while (bfs(origin, destiny)) {			
			int pathFlow = MAX_WEIGHT;

			for (v = destiny; v != origin; v = parent[v]) {
				u = parent[v];
				pathFlow = std::min(pathFlow, graph.getWeigthFrom(u, v));
			}			

			for (v = destiny; v != origin; v = parent[v]) {
				u = parent[v];
				//rGraph[u][v] -= pathFlow;
				//rGraph[v][u] += pathFlow;
			}
			
			maxFlow += pathFlow;
		}
		
		write("O fluxo maximo possivel e: ", maxFlow, "ln");
	}
};