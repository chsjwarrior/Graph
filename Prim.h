#pragma once

/*O algoritmo de Prim */

class Prim {
private:
	const Graph& graph;
	int* key;
	int* predecessor;
	bool* visited;

	const unsigned int extractMin() const {
		int lowerDistance = MAX_WEIGHT;
		unsigned int lowerVertex = 0;
		for (int unsigned u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (!visited[u] && key[u] < lowerDistance) {
				lowerDistance = key[u];
				lowerVertex = u;
			}
		return lowerVertex;
	}

	inline void relax(const unsigned int& u, const unsigned int& v) const {
		if (graph.getWeigthFrom(u, v) < key[v]) {
			predecessor[v] = u;
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
			writeVertex(predecessor[i]);
			write('|');
		}
		write("\n");
	}

public:
	Prim() = delete;
	Prim(const Graph& graph) : graph(graph) {
		key = new int[graph.AMOUNT_VERTEXES];
		predecessor = new int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~Prim() {
		delete[] key;
		delete[] predecessor;
		delete[] visited;
		key = nullptr;
		predecessor = nullptr;
		visited = nullptr;
	}

	void prim(const unsigned int& source)const {
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			key[i] = MAX_WEIGHT;
			predecessor[i] = NIL;
			visited[i] = false;
		}
		key[source] = 0;
		unsigned int queue = 0;

		while (queue < graph.AMOUNT_VERTEXES) {
			unsigned int u = extractMin();
			queue++;
			visited[u] = true;

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (!visited[*v])
					relax(u, *v);
		}
		print();
	}
};
