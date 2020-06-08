#pragma once
#include "Graph.h"

using namespace Scanner;

/*
O Algoritmo de Bellman-Ford é um algoritmo de busca de caminho mínimo em um digrafo (grafo orientado ou dirigido) ponderado, inclusive negativo.
O Algoritmo de Dijkstra resolve o mesmo problema, num tempo menor, porém exige que todas as arestas tenham pesos positivos.
Assim como o algoritmo de Dijkstra, o algoritmo de Bellman-Ford utiliza a técnica de relaxamento.
A principal diferença entre Dijkstra e Bellman-Ford é que no algoritmo de Bellman-Ford se relaxa todas as arestas.
*/

class BellmanFord {
private:
	const Graph& graph;
	int* distance;
	int* pi;

	void print() const {
		writeln("Bellman-Ford:");
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
	BellmanFord() = delete;
	BellmanFord(const Graph& graph) : graph(graph) {
		distance = new int[graph.AMOUNT_VERTEXES];
		pi = new int[graph.AMOUNT_VERTEXES];
	}

	~BellmanFord() {
		delete[] distance;
		delete[] pi;
		distance = nullptr;
		pi = nullptr;
	}

	void bellmanFord(const unsigned int& origin) const {
		if (!graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser dirigido para o algoritmo de Bellman-Ford funcionar.");
			return;
		}

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			distance[u] = MAX_WEIGHT;
			pi[u] = NIL;
		}
		distance[origin] = 0;

		//esse algoritmo garante a menor distancia
		std::multiset<Edge> edges = graph.getEdges();
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			for (auto e = edges.cbegin(); e != edges.cend(); e++)
				if (distance[e->U] != MAX_WEIGHT && distance[e->U] + e->WEIGHT < distance[e->V]) {
					distance[e->V] = distance[e->U] + e->WEIGHT;
					pi[e->V] = e->U;
				}

		//esse algoritmo verifica se o grafo possui ciclo negativo
		for (auto e = edges.cbegin(); e != edges.cend(); e++)
			if (distance[e->U] != MAX_WEIGHT && distance[e->U] + e->WEIGHT < distance[e->V]) {
				writeln("O Grafo contem ciclo com peso negativo");
				return;
			}

		edges.clear();
		print();
	}
};