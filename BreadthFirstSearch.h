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
	unsigned int* predecessor;
	bool* visited;

	void bfsRecursive(std::queue<unsigned int>& queue) {
		if (queue.empty())
			return;

		unsigned int u = queue.front();
		queue.pop();

		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (visited[*v] == false) {
				queue.push(*v);
				discovery[*v] = discovery[u] + 1;
				predecessor[*v] = u;
				visited[*v] = true;
			}

		bfsRecursive(queue);
	}

	void bfsIterative(std::queue<unsigned int>& queue) {
		unsigned int u;
		while (!queue.empty()) {
			u = queue.front();
			queue.pop();

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (visited[*v] == false) {
					queue.push(*v);
					discovery[*v] = discovery[u] + 1;
					predecessor[*v] = u;
					visited[*v] = true;
				}
		}
	}

	void print() const {
		write("Vi  |");
		unsigned int i;
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
		}
		write("\ndi  |");
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeValue(discovery[i]);
			write('|');
		}
		write("\npi  |");
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(predecessor[i]);
			write('|');
		}
		write("\n");
	}

public:
	BreadthFirstSearch() = delete;
	BreadthFirstSearch(const Graph& graph) : graph(graph) {
		discovery = new unsigned int[graph.AMOUNT_VERTEXES];
		predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
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

	void bfs(const unsigned int& source, const bool& isRecursive) {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			discovery[u] = NIL;
			predecessor[u] = NIL;
			visited[u] = false;
		}

		std::queue<unsigned int> queue;
		discovery[source] = 0;
		visited[source] = true;
		queue.push(source);

		if (isRecursive) {
			bfsRecursive(queue);
			writeln("Busca em largura recursiva:");
		} else {
			bfsIterative(queue);
			writeln("Busca em largura iterativa:");
		}
		print();
	}
};