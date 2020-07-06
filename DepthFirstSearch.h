#pragma once
#include <stack>

/*
O algoritmo da busca em profundidade é um algoritmo para caminha no grafo.
Seu núcleo se concentra em buscar sempre que possível o maif fundo no grafo.
funcionando.
*/

class DepthFirstSearch {
private:
	const Graph& graph;
	unsigned int* discovery;
	unsigned int* close;
	bool* visited;
	unsigned int time;

	void dfsVisitRecursive(const unsigned int& u) {
		visited[u] = true;
		discovery[u] = ++time;

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (!visited[*v])
				dfsVisitRecursive(*v);

		close[u] = ++time;
	}

	void dfsVisitIterative(unsigned int u) {
		std::stack<unsigned int> stack;

		stack.push(u);
		while (!stack.empty()) {
			u = stack.top();

			if (!visited[u]) {
				visited[u] = true;
				discovery[u] = ++time;

				std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
				for (auto v = adjacences.crbegin(); v != adjacences.crend(); ++v)
					if (!visited[*v])
						stack.push(*v);
				adjacences.clear();

			} else {
				if (close[u] == NIL)
					close[u] = ++time;
				stack.pop();
			}
		}
	}

	void print() const {
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
		write("\nci  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeValue(close[i]);
			write('|');
		}
		write("\n");
	}

public:
	DepthFirstSearch() = delete;
	DepthFirstSearch(const Graph& graph) : graph(graph) {
		discovery = new unsigned int[graph.AMOUNT_VERTEXES];
		close = new unsigned int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
		time = NULL;
	}

	~DepthFirstSearch() {
		delete[] discovery;
		delete[] close;
		delete[] visited;
		discovery = nullptr;
		close = nullptr;
		visited = nullptr;
		time = NULL;
	}

	void dfs(const unsigned int& source, const bool& isRecursive) {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			discovery[u] = NIL;
			close[u] = NIL;
			visited[u] = false;
		}

		time = 0;
		for (unsigned int u = 0, v = source; u < graph.AMOUNT_VERTEXES; u++) {
			if (visited[v] == false)
				if (isRecursive) {
					dfsVisitRecursive(v);
					writeln("Busca em profundidade recursiva:");
				} else {
					dfsVisitIterative(v);
					writeln("Busca em profundidade iterativa:");
				}
			v = u;
		}
		print();
	}
};