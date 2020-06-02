#pragma once
#include "Graph.h"

using namespace Scanner;

/*
O algoritmo de Floud-Warschall resolver o problema do caminho mínimo com várias origens.
Esse algoritmo funciona com grafos valorados com valores positivos e negativos.
cada linha da matriz indica a mesma distancia do algoritmo de Dijkstra.
funcionando
*/

class FloydWarshall {
	const Graph& graph;
	int** costMatrix;
	int** pi;

	void print() const {
		writeln("Floyd & Warshall:");
		write("Vi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
		}
		write("\n");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
			for (unsigned int j = 0; j < graph.AMOUNT_VERTEXES; j++) {
				writeValue(costMatrix[i][j]);
				write("|");
			}
			write("\n");
		}
		write("\nVi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
		}
		write("\n");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
			for (unsigned int j = 0; j < graph.AMOUNT_VERTEXES; j++) {
				writeVertex(pi[i][j]);
				write("|");
			}
			write("\n");
		}
	}

public:
	FloydWarshall() = delete;
	FloydWarshall(const Graph& graph) : graph(graph) {
		costMatrix = new int* [graph.AMOUNT_VERTEXES];
		pi = new int* [graph.AMOUNT_VERTEXES];

		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			costMatrix[i] = new int[graph.AMOUNT_VERTEXES];
			pi[i] = new int[graph.AMOUNT_VERTEXES];
		}
	}

	~FloydWarshall() {
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			delete[] costMatrix[i];
			delete[] pi[i];
			costMatrix[i] = nullptr;
			pi[i] = nullptr;
		}
		delete[] costMatrix;
		delete[] pi;
		costMatrix = nullptr;
		pi = nullptr;
	};

	void floydWarshall() const {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			for (unsigned int v = 0; v < graph.AMOUNT_VERTEXES; v++) {
				costMatrix[u][v] = graph.getWeigthFrom(u, v);
				if (u != v && costMatrix[u][v] < MAX_WEIGHT)
					pi[u][v] = u;
				else
					pi[u][v] = -1;
			}

		for (unsigned int k = 0; k < graph.AMOUNT_VERTEXES; k++)
			for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
				for (unsigned int j = 0; j < graph.AMOUNT_VERTEXES; j++)
					if (costMatrix[i][j] > costMatrix[i][k] + costMatrix[k][j]) {
						costMatrix[i][j] = costMatrix[i][k] + costMatrix[k][j];
						pi[i][j] = pi[k][j];
					}
		print();
	}
};