#pragma once

/*
O algoritmo de Dijkstra soluciona o problema do caminho mais curto num grafo dirigido ou não dirigido com arestas de peso não negativo.
O algoritmo que serve para resolver o mesmo problema em um grafo com pesos negativos é o algoritmo de Bellman-Ford, que possui maior tempo de execução que o Dijkstra.

funcionando.
*/

class Dijkstra {
private:
	const Graph& graph;
	int* distance;
	int* pi;
	bool* visited;

	const unsigned int extractSmaller() const {
		int lowerValue = MAX_WEIGHT;
		unsigned int lowWeightVertex = 0;
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (visited[u] == false && distance[u] < lowerValue) {//distance[u] <= lowerValue, verificar
				lowerValue = distance[u];
				lowWeightVertex = u;
			}
		return lowWeightVertex;
	}

	inline void relax(const unsigned int& u, const unsigned int& v) const {
		if (distance[v] > distance[u] + graph.getWeigthFrom(u, v)) {
			distance[v] = distance[u] + graph.getWeigthFrom(u, v);
			pi[v] = u;
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
			writeVertex(pi[i]);
			write('|');
		}
		write("\n");
	}

public:
	Dijkstra() = delete;
	Dijkstra(const Graph& graph) : graph(graph) {
		distance = new int[graph.AMOUNT_VERTEXES];
		pi = new int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~Dijkstra() {
		delete[] distance;
		delete[] pi;
		delete[] visited;
		distance = nullptr;
		pi = nullptr;
		visited = nullptr;
	}

	void dijkstra(const unsigned int& origin) const {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			distance[u] = MAX_WEIGHT;
			pi[u] = NIL;
			visited[u] = false;
		}
		distance[origin] = 0;

		for (unsigned int vertex = 0; vertex < graph.AMOUNT_VERTEXES; vertex++) {
			unsigned int u = extractSmaller();
			visited[u] = true;

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (graph.getWeigthFrom(u, *v) > 0)//se o peso é negativo deveria anular o programa.
					relax(u, *v);
		}
		print();
	}
};