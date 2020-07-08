#pragma once
#include <list>

/*
O algoritmo de Dijkstra soluciona o problema do caminho mais curto num grafo dirigido ou não dirigido com arestas de peso não negativo.
O algoritmo que serve para resolver o mesmo problema em um grafo com pesos negativos é o algoritmo de Bellman-Ford, que possui maior tempo de execução que o Dijkstra.
*/

class Dijkstra {
private:
	const Graph& graph;
	int* distance;
	unsigned int* predecessor;
	bool* visited;

	const unsigned int extractMin(std::list<unsigned int>& queue) {
		int lowerDistance = INF;
		unsigned int lowerVertex = NIL;
		for (auto u = queue.cbegin(); u != queue.cend(); ++u)
			if (distance[*u] < lowerDistance) {//distance[u] <= lowerValue, verificar
				lowerDistance = distance[*u];
				lowerVertex = *u;
			}
		queue.remove(lowerVertex);
		return lowerVertex;
	}

	inline void relax(const unsigned int& u, const unsigned int& v, const int& w) {
		if (distance[v] > distance[u] + w) {
			distance[v] = distance[u] + w;
			predecessor[v] = u;
		}
	}

	void print() const {
		writeln("Dijkstra:");
		write("Vi  |");
		unsigned int i;
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
		}
		write("\ndi  |");
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeValue(distance[i]);
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
	Dijkstra() = delete;
	Dijkstra(const Graph& graph) : graph(graph) {
		distance = new int[graph.AMOUNT_VERTEXES];
		predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~Dijkstra() {
		delete[] distance;
		delete[] predecessor;
		delete[] visited;
		distance = nullptr;
		predecessor = nullptr;
		visited = nullptr;
	}

	void dijkstra(const unsigned int& source) {
		std::list<unsigned int> queue;
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			distance[i] = INF;
			predecessor[i] = NIL;
			visited[i] = false;
			queue.push_back(i);
		}
		distance[source] = 0;

		while (!queue.empty()) {
			unsigned int u = extractMin(queue);
			visited[u] = true;

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (visited[*v] == false)//if (graph.getWeigthFrom(u, *v) > 0)se o peso é negativo deveria anular o programa.
					relax(u, *v, graph.getWeigthFrom(u, *v));
		}
		print();
	}
};