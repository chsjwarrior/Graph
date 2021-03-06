#pragma once
/*
O algoritmo de Floud-Warschall resolver o problema do caminho m?nimo com v?rias origens em um grafo ponderado com valores positivos e negativos.
cada linha da matriz indica a mesma distancia do algoritmo de Dijkstra.
*/
class FloydWarshall {
	const Graph& graph;
	int** costMatrix;
	unsigned int** predecessor;

	void print() const {
		PageTable table("Floyd-Warshall, cost matrix:", graph.AMOUNT_VERTEXES, graph.AMOUNT_VERTEXES + 1, PageTable::HeaderOrientation::COLUMN);
		table.setColumnsForPage(20);

		table.updateHeaderAt(0, "");
		unsigned int i;
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			table.setColumnMaxWidth(i, 4);
			table.updateHeaderAt(static_cast<size_t>(1) + i, graph.getVertexName(i));
			table.updateValueAt(i, 0, graph.getVertexName(i));
		}
		table.setColumnMaxWidth(table.getColumnCount() - 1, 4);

		for (i = 0; i < graph.AMOUNT_VERTEXES; i++)
			for (unsigned int j = 0; j < graph.AMOUNT_VERTEXES; j++)
				table.updateValueAt(i, static_cast<size_t>(1) + j, graph.getFormatedWeight(costMatrix[i][j]));

		table.print();

		table.setTitle("Floyd-Warshall, predecessor matrix:");
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++)
			for (unsigned int j = 0; j < graph.AMOUNT_VERTEXES; j++)
				table.updateValueAt(i, static_cast<size_t>(1) + j, graph.getVertexName(predecessor[i][j]));

		table.print();
	}

public:
	FloydWarshall() = delete;
	FloydWarshall(const Graph& graph) noexcept(false) : graph(graph) {
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

		std::cout << "Floyd-Warshall:" << std::endl;
		//esse algoritmo verifica se o grafo possui ciclo negativo
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
			if (costMatrix[i][i] < 0) {
				std::cout << "O Grafo contem ciclo com peso negativo" << std::endl;
				i = graph.AMOUNT_VERTEXES;
			}

		print();
	}
};