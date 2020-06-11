#pragma once
#include <list>

/*
O algoritmo de Dijkstra soluciona o problema do caminho mais curto num grafo dirigido ou não dirigido com arestas de peso não negativo.
O algoritmo que serve para resolver o mesmo problema em um grafo com pesos negativos é o algoritmo de Bellman-Ford, que possui maior tempo de execução que o Dijkstra.

funcionando.
*/

class Dijkstra {
private:
	const Graph& graph;
	int* distance;
	int* predecessor;

	const unsigned int extractMin(std::list<unsigned int>& queue) const {
		int lowerDistance = MAX_WEIGHT;
		unsigned int lowerVertex = 0;

		for (auto u = queue.cbegin(); u != queue.cend(); u++)
			if (distance[*u] < lowerDistance) {//distance[u] <= lowerValue, verificar
				lowerDistance = distance[*u];
				lowerVertex = *u;
			}
		queue.remove(lowerVertex);
		return lowerVertex;
	}

	inline void relax(const unsigned int& u, const unsigned int& v) const {
		if (distance[v] > distance[u] + graph.getWeigthFrom(u, v)) {
			distance[v] = distance[u] + graph.getWeigthFrom(u, v);
			predecessor[v] = u;
		}
	}

	void print() const {
		writeln("Dijkstra:");
		write("Vi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
		}
		write("\ndi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeValue(distance[i]);
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
	Dijkstra() = delete;
	Dijkstra(const Graph& graph) : graph(graph) {
		distance = new int[graph.AMOUNT_VERTEXES];
		predecessor = new int[graph.AMOUNT_VERTEXES];
	}

	~Dijkstra() {
		delete[] distance;
		delete[] predecessor;
		distance = nullptr;
		predecessor = nullptr;
	}

	void dijkstra(const unsigned int& source) const {
		std::list<unsigned int> queue;
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			distance[u] = MAX_WEIGHT;
			predecessor[u] = NIL;
			queue.push_back(u);
		}
		distance[source] = 0;

		while (!queue.empty()) {
			unsigned int u = extractMin(queue);

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (graph.getWeigthFrom(u, *v) > 0)//se o peso é negativo deveria anular o programa.
					relax(u, *v);
		}
		print();
	}
};