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
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~CloserNeighbor() {
		delete[] visited;
		visited = nullptr;
	}

	void closerNeighbor(const unsigned int origin) const {
		writeln("Vizinho mais proximo:");

		memset(visited, false, sizeof(visited));
		closerNeighborR(origin);

		if (std::all_of(visited, visited + graph.AMOUNT_VERTEXES, [](bool x) { return x == true; })) {
			write("->");
			writeVertex(origin);
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