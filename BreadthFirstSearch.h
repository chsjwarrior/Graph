#pragma once
#include <queue>

/*
O algoritmo da busca em largura calcula a distância (menor número de arestas)
desde o vértice S (raiz) até tdos os vértices acessíveis.
funcionando.
*/

class BreadthFirstSearch {
private:
	const Graph& graph;
	unsigned int* discovery;
	int* predecessor;
	bool* visited;

	void print() const {
		writeln("Busca em largura:");
		write("Vi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
		}
		write("\ndi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeValue(discovery[i]);
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
	BreadthFirstSearch() = delete;
	BreadthFirstSearch(const Graph& graph) : graph(graph) {
		discovery = new unsigned int[graph.AMOUNT_VERTEXES];
		predecessor = new int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~BreadthFirstSearch() {
		delete[] discovery;
		delete[] predecessor;
		delete[] visited;
		discovery = nullptr;
		predecessor = nullptr;
		visited = nullptr;
	}

	void bfs(const unsigned int& source) const {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			discovery[u] = MAX_WEIGHT;
			predecessor[u] = NIL;
			visited[u] = false;
		}

		std::queue<unsigned int> queue;
		unsigned int u = source;
		discovery[u] = 0;
		visited[u] = true;
		queue.push(u);
		while (!queue.empty()) {
			u = queue.front();
			queue.pop();

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (!visited[*v]) {
					queue.push(*v);
					discovery[*v] = discovery[u] + 1;
					predecessor[*v] = u;
					visited[*v] = true;
				}
		}
		print();
	}
};