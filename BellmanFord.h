#pragma once
/*
O Algoritmo de Bellman-Ford é um algoritmo de busca de caminho minimo em um digrafo (grafo orientado ou dirigido) e ponderado, inclusive negativo.
O Algoritmo de Dijkstra resolve o mesmo problema, num tempo menor, porém exige que todas as arestas tenham pesos positivos.
Assim como o algoritmo de Dijkstra, o algoritmo de Bellman-Ford utiliza a técnica de relaxamento.
A principal diferença entre Dijkstra e Bellman-Ford é que no algoritmo de Bellman-Ford se relaxa todas as arestas.
*/
class BellmanFord {
private:
	const Graph& graph;
	int* distance;
	unsigned int* predecessor;

	void print() const {
		std::cout << std::left << std::setw(4) << "Vi";
		std::cout << std::right;
		unsigned int i;
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			std::cout << '|' << std::setw(4);
			graph.writeVertex(i);
		}
		std::cout << std::endl << std::left << std::setw(4) << "di";
		std::cout << std::right;
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			std::cout << '|' << std::setw(4);
			graph.writeValue(distance[i]);
		}
		std::cout << std::endl << std::left << std::setw(4) << "pi";
		std::cout << std::right;
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			std::cout << '|' << std::setw(4);
			graph.writeVertex(predecessor[i]);
		}
		std::cout << std::endl;
	}

public:
	BellmanFord() = delete;
	BellmanFord(const Graph& graph) : graph(graph) {
		if (!graph.IS_DIGRAPH)
			throw std::exception("O Grafo precisa ser dirigido para o algoritmo Bellman - Ford funcionar.");
		distance = new int[graph.AMOUNT_VERTEXES];
		predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
	}

	~BellmanFord() {
		delete[] distance;
		delete[] predecessor;
		distance = nullptr;
		predecessor = nullptr;
	}

	void bellmanFord(const unsigned int& source) {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			distance[u] = INF;
			predecessor[u] = NIL;
		}

		distance[source] = 0;
		//esse algoritmo garante a menor distancia
		std::multiset<Edge> edges = graph.getEdges();
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			for (auto e = edges.cbegin(); e != edges.cend(); e++)
				if (distance[e->U] != INF && distance[e->U] + e->WEIGHT < distance[e->V]) {
					distance[e->V] = distance[e->U] + e->WEIGHT;
					predecessor[e->V] = e->U;
				}

		std::cout << "Bellman-Ford:" << std::endl;
		//esse algoritmo verifica se o grafo possui ciclo negativo
		for (auto e = edges.cbegin(); e != edges.cend(); e++)
			if (distance[e->U] != INF && distance[e->U] + e->WEIGHT < distance[e->V]) {
				std::cout << "O Grafo contem ciclo com peso negativo" << std::endl;
				e = edges.cend();
			}

		edges.clear();
		print();
	}
};