#pragma once

/*
O algoritmo de Fleury é utilizado para a identificação de um ciclo euleriano em um grafo.

 funcionando, mas é preciso testar de outras maneiras ainda.
 funcionou com seguinte grafo:
4 5 0
1 2 0
1 4 0
2 3 0
2 3 0
2 4 0
4 4 0
*/

class Fleury {
private:
	Graph graph;
	bool* visited;

	const std::pair<unsigned int, unsigned int> validateGraph() const {
		unsigned int degree;
		unsigned int amountOddVertex = 0, firstOddVertex = graph.AMOUNT_VERTEXES;
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			degree = graph.getOutDegreeFrom(u);//para digrafo tambem usa-se grau de saída
			if (degree % 2 != 0) {
				amountOddVertex++;
				if (firstOddVertex == graph.AMOUNT_VERTEXES)
					firstOddVertex = u;
			}
		}
		return std::make_pair(amountOddVertex, firstOddVertex == graph.AMOUNT_VERTEXES ? 0 : firstOddVertex);
	}

	const unsigned int dfsUtil(const unsigned int& u) const {
		visited[u] = true;
		unsigned int count = 1;

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (!visited[*v])
				count += dfsUtil(*v);
		return count;
	}

	const bool isBridge(const unsigned int& u, const unsigned int& v) {
		if (graph.getOutDegreeFrom(u) == 1)
			return false;

		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
		unsigned int bridgeCount = dfsUtil(v);

		graph.removeEdge(u, v);

		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
		unsigned int nonBridge = dfsUtil(v);

		graph.insertEdge(u, v);

		return nonBridge < bridgeCount;
	}

	void fleuryR(const unsigned int& u) {
		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (!isBridge(u, *v)) {
				writeVertex(u);
				write("->");
				writeVertex(*v);
				write("\n");
				graph.removeEdge(u, *v);
				fleuryR(*v);
				break;
			}
	}

public:
	Fleury() = delete;
	Fleury(const Graph& graph) : graph(graph) {
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~Fleury() {
		delete[] visited;
		visited = nullptr;
	}

	void fleury() {
		writeln("Fleury:");
		const std::pair<unsigned int, unsigned int> pair = validateGraph();

		if (pair.first > 2) {
			write(pair.first);
			writeln(" vertices tem grau impar", "O Grafo nao e euleriano");
		}
		else {
			if (pair.first == 0)
				writeln("Todos os vertices tem grau par", "e possivel encontrar um caminho euleriano.");
			else if (pair.first == 2)
				writeln("Dois vertices tem grau impar", "e possivel encontrar um caminho semi-euleriano.");
			fleuryR(pair.second);
		}
	}
};