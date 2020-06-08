#pragma once
#include "Graph.h"

using namespace Scanner;

/*
O algoritmo da ligação mais economica encontra um ciclo hamiltoniano no grafo passando pelas aresta com menor peso.
Essa implementação do  algoritmo não funciona para grafos semi-hamiltoniano.
testado e funcionando com o seguinte grafo:
5 10 0
1 2 185
1 3 119
1 4 152
1 5 133
2 3 121
2 4 150
2 5 200
3 4 174
3 5 120
4 5 199
*/

class CheaperConnection {
private:
	Graph graph;
	unsigned int* degree;
	bool* visited;

	struct Comparator {
		const bool operator()(const Edge& lhs, const Edge& rhs) const {
			return lhs.WEIGHT > rhs.WEIGHT;
		}
	};

	std::priority_queue<Edge, std::deque<Edge>, Comparator> edges;

	const bool bfs(unsigned int u, const unsigned int& k) {
		std::queue<unsigned int> queue;
		visited[u] = true;
		queue.push(u);
		while (!queue.empty() && !visited[k]) {
			u = queue.front();
			queue.pop();

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty() && !visited[k]; v = adjacences.erase(v))
				if (!visited[*v]) {
					queue.push(*v);
					visited[*v] = true;
				}
		}
		return visited[k];
	}

	inline void insertEdge(const Edge& edge) {
		graph.insertEdge(edge.U, edge.V, edge.WEIGHT);
		degree[edge.U]++;
		degree[edge.V]++;
		edge.print();
		write("=", edge.WEIGHT);
		write(" entry\n");
	}

public:
	CheaperConnection() = delete;
	CheaperConnection(const Graph& graph) : graph(graph.AMOUNT_VERTEXES, graph.IS_DIGRAPH) {
		std::multiset<Edge> set = graph.getEdges();
		for (auto e = set.cbegin(); !set.empty(); e = set.erase(e))
			edges.push(*e);
		degree = new unsigned int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~CheaperConnection() {
		delete[] degree;
		degree = nullptr;
		delete[] visited;
		visited = nullptr;
	}

	void cheaperConnection() {
		writeln("Ligacao mais economica:");

		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			degree[i] = 0;
			visited[i] = false;
		}

		Edge lowerWeight = edges.top();
		insertEdge(lowerWeight);
		edges.pop();

		bool hasZeroDegree = true;
		while (hasZeroDegree) {//enquanto existir vertices não descobertos
			lowerWeight = edges.top();

			if (degree[lowerWeight.U] < 2 && degree[lowerWeight.V] < 2) {
				if (!bfs(lowerWeight.U, lowerWeight.V)) {
					insertEdge(lowerWeight);

					hasZeroDegree = false;
					for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
						if (degree[i] == 0)
							hasZeroDegree = true;
						visited[i] = false;
					}
				}
			}

			edges.pop();
		}

		if (!hasZeroDegree) {//ainda é hamiltoniano
			while (!edges.empty()) {
				lowerWeight = edges.top();
				if (degree[lowerWeight.U] == 1)
					if (degree[lowerWeight.V] == 1)
						insertEdge(lowerWeight);
				edges.pop();
			}

			hasZeroDegree = true;//usando como variavel auxiliar
			for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
				if (degree[i] != 2)
					hasZeroDegree = false;

			if (hasZeroDegree) //se todos vertices iguais a 2;
				writeln("O grafo e hamiltoniano.");
		}
		else {
			writeln("O grafo nao e hamiltoniano.");
		}
	}
};