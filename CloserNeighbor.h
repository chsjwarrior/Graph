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
	int total;

	void closerNeighborR(const unsigned int& u) {
		visited[u] = true;
		writeVertex(u);

		int lowerWeight = INF;
		unsigned int lowerVertex = NIL;
		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (visited[*v] == false && graph.getWeigthFrom(u, *v) < lowerWeight) {
				lowerVertex = *v;
				lowerWeight = graph.getWeigthFrom(u, *v);
			}
		if (lowerVertex != NIL) {
			write("->");
			total += graph.getWeigthFrom(u, lowerVertex);
			closerNeighborR(lowerVertex);
		}
	}

public:
	CloserNeighbor() = delete;
	CloserNeighbor(const Graph& graph) : graph(graph) {
		visited = new bool[graph.AMOUNT_VERTEXES];
		total = NULL;
	}

	~CloserNeighbor() {
		delete[] visited;
		visited = nullptr;
		total = NULL;
	}

	void closerNeighbor(const unsigned int source) {
		writeln("Vizinho mais proximo:");

		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
		total = 0;
		closerNeighborR(source);

		if (std::all_of(visited, visited + graph.AMOUNT_VERTEXES, [](const bool& x) { return x == true; })) {
			write("->");
			writeVertex(source);
		}
		write("= ", total, "\n");
	}

	void closerNeighborRepetitive() {
		writeln("Vizinho mais proximo repetitivo:");

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
			total = 0;
			closerNeighborR(u);

			if (std::all_of(visited, visited + graph.AMOUNT_VERTEXES, [](const bool& x) { return x == true; })) {
				write("->");
				writeVertex(u);
			}
			write("= ", total, "\n");
		}
	}
};