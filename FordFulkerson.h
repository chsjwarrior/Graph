#pragma once

class FordFulkerson {
private:
	const Graph& graph;
	int** costMatrix;
	unsigned int* predecessor;
	bool* visited;

	const bool bfsUtil(unsigned int u, const unsigned int& k) {
		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);

		std::queue<unsigned int> queue;
		queue.push(u);
		visited[u] = true;
		predecessor[u] = NIL;
		while (!queue.empty()) {
			u = queue.front();
			queue.pop();

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
				if (!visited[*v]) {
					queue.push(*v);
					predecessor[*v] = u;
					visited[*v] = true;
				}
			}
		}

		return visited[k];
	}

public:
	FordFulkerson() = delete;
	FordFulkerson(const Graph& graph) : graph(graph) {
		costMatrix = new int* [graph.AMOUNT_VERTEXES];
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
			costMatrix[i] = new int[graph.AMOUNT_VERTEXES];

		predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}
	~FordFulkerson() {
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			delete[] costMatrix[i];
			costMatrix[i] = nullptr;
		}
		delete[] costMatrix;
		delete[] predecessor;
		delete[] visited;
		costMatrix = nullptr;
		predecessor = nullptr;
		visited = nullptr;
	}

	void fordFulkerson(const unsigned int& source, const unsigned int& sink) {
		if (!graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser dirigido para o algoritmo de Ford-Fulkerson funcionar.");
			return;
		}

		writeln("Ford-Fulkerson:");

		unsigned int u, v;
		int maxFlow = 0;
		for (u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			predecessor[u] = NIL;
			for (v = 0; v < graph.AMOUNT_VERTEXES; v++)
				costMatrix[u][v] = graph.getWeigthFrom(u, v);
		}

		while (bfsUtil(source, sink)) {
			int pathFlow = INF;

			for (v = sink; v != source; v = predecessor[v]) {
				u = predecessor[v];
				pathFlow = std::min(pathFlow, graph.getWeigthFrom(u, v));
			}

			for (v = sink; v != source; v = predecessor[v]) {
				u = predecessor[v];
				costMatrix[u][v] -= pathFlow;
				costMatrix[v][u] += pathFlow;
			}

			maxFlow += pathFlow;
		}

		write("O fluxo maximo possivel e: ", maxFlow, "\n");
	}
};