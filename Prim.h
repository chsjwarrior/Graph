#pragma once

/*
O algoritmo de Prim é empregado para encontrar uma arvore geradora minima (minimal spanning tree) num grafo conexo, valorado e não direcionado.
Isto significa que ele encontra um subgrafo que forma uma arvore que inclui todos os vertices,
onde o peso total é dado pela soma dos pesos das arestas da árvore de menor valor.
*/

class Prim {
private:
	const Graph& graph;
	int* key;
	unsigned int* predecessor;
	bool* visited;

	const unsigned int extractMin(std::list<unsigned int>& queue) {
		int lowerDistance = INF;
		unsigned int lowerVertex = NIL;
		for (auto u = queue.cbegin(); u != queue.cend(); ++u)
			if (key[*u] < lowerDistance) {
				lowerDistance = key[*u];
				lowerVertex = *u;
			}
		queue.remove(lowerVertex);
		return lowerVertex;
	}

	inline void relax(const unsigned int& u, const unsigned int& v, const int& w) {
		if (graph.getWeigthFrom(u, v) < key[v]) {
			predecessor[v] = u;
			key[v] = w;
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
		predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
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

	void prim(const unsigned int& source) {
		if (graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser nao dirigido para o algoritmo Prim funcionar.");
			return;
		}

		std::list<unsigned int> queue;
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			key[i] = INF;
			predecessor[i] = NIL;
			visited[i] = false;
			queue.push_back(i);
		}
		key[source] = 0;

		while (!queue.empty()) {
			unsigned int u = extractMin(queue);
			visited[u] = true;

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (!visited[*v])
					relax(u, *v, graph.getWeigthFrom(u, *v));
		}
		print();
	}
};