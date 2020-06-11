#pragma once

/*
O algoritmodo do vizinho mais próximo realiza um tipo de uma busca em profundidade escolhendo o vértice de menor custo.
pode encontrar um ciclo hamiltoniano.
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
		int lowerWeight = MAX_WEIGHT;
		unsigned int lowerVertex = 0;
		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (!visited[*v] && graph.getWeigthFrom(u, *v) < lowerWeight) {
				found = true;
				lowerVertex = *v;
				lowerWeight = graph.getWeigthFrom(u, *v);
			}
		if (found) {
			write("->");
			closerNeighborR(lowerVertex);
		}
	}

public:
	CloserNeighbor() = delete;
	CloserNeighbor(const Graph& graph) : graph(graph) {
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~CloserNeighbor() {
		delete[] visited;
		visited = nullptr;
	}

	void closerNeighbor(const unsigned int source) const {
		writeln("Vizinho mais proximo:");

		memset(visited, false, sizeof(visited));
		closerNeighborR(source);

		if (std::all_of(visited, visited + graph.AMOUNT_VERTEXES, [](bool x) { return x == true; })) {
			write("->");
			writeVertex(source);
		}
		write("\n");
	}

	void closerNeighborRepetitive() const {
		writeln("Vizinho mais proximo repetitivo:");

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			memset(visited, false, sizeof(visited));
			closerNeighborR(u);

			if (std::all_of(visited, visited + graph.AMOUNT_VERTEXES, [](bool x) { return x == true; })) {
				write("->");
				writeVertex(u);
			}
			write("\n");
		}
	}
};