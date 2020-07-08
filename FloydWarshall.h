#pragma once

/*
O algoritmo de Floud-Warschall resolver o problema do caminho mínimo com várias origens em um grafo ponderado com valores positivos e negativos.
cada linha da matriz indica a mesma distancia do algoritmo de Dijkstra.
*/

class FloydWarshall {
	const Graph& graph;
	int** costMatrix;
	unsigned int** predecessor;

	void print() const {
		writeln("Floyd-Warshall:");
		write("Vi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
		}
		write("\n");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
			for (unsigned int j = 0; j < graph.AMOUNT_VERTEXES; j++) {
				writeValue(costMatrix[i][j]);
				write('|');
			}
			write("\n");
		}
		write("\nVi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
		}
		write("\n");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
			for (unsigned int j = 0; j < graph.AMOUNT_VERTEXES; j++) {
				writeVertex(predecessor[i][j]);
				write('|');
			}
			write("\n");
		}
	}

public:
	FloydWarshall() = delete;
	FloydWarshall(const Graph& graph) : graph(graph) {
		costMatrix = new int* [graph.AMOUNT_VERTEXES];
		predecessor = new unsigned int* [graph.AMOUNT_VERTEXES];

		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			costMatrix[i] = new int[graph.AMOUNT_VERTEXES];
			predecessor[i] = new unsigned int[graph.AMOUNT_VERTEXES];
		}
	}

	~FloydWarshall() {
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			delete[] costMatrix[i];
			delete[] predecessor[i];
			costMatrix[i] = nullptr;
			predecessor[i] = nullptr;
		}
		delete[] costMatrix;
		delete[] predecessor;
		costMatrix = nullptr;
		predecessor = nullptr;
	};

	void floydWarshall() {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			for (unsigned int v = 0; v < graph.AMOUNT_VERTEXES; v++) {
				costMatrix[u][v] = graph.getWeigthFrom(u, v);
				if (u != v && costMatrix[u][v] < INF)
					predecessor[u][v] = u;
				else
					predecessor[u][v] = NIL;
			}

		//esse algoritmo garante a menor distancia
		for (unsigned int k = 0; k < graph.AMOUNT_VERTEXES; k++)
			for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
				for (unsigned int j = 0; j < graph.AMOUNT_VERTEXES; j++)
					if (costMatrix[i][j] > costMatrix[i][k] + costMatrix[k][j]) {
						costMatrix[i][j] = costMatrix[i][k] + costMatrix[k][j];
						predecessor[i][j] = predecessor[k][j];
					}

		//esse algoritmo verifica se o grafo possui ciclo negativo
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
			if (costMatrix[i][i] < 0){
				writeln("O Grafo contem ciclo com peso negativo");
				i = graph.AMOUNT_VERTEXES;
			}

		print();
	}
};