#pragma once
/*
O algoritmo de Fleury é utilizado para a identificação de um ciclo euleriano em um grafo.

//tem que descobrir se o algoritmo de Fleury funciona em grafo dirigidos ou não.
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

	const bool isConnected() {
		unsigned int u;
		for (u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (graph.getOutDegreeFrom(u) != 0)
				break;

		if (u == graph.AMOUNT_VERTEXES)
			return true;

		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
		dfsUtil(u);

		for (u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (visited[u] == false && graph.getOutDegreeFrom(u) > 0)
				return false;
		return true;
	}

	const std::pair<unsigned int, unsigned int> validateGraph() {
		unsigned int degree;
		unsigned int amountOddVertexes = 0;
		unsigned int firstOddVertex = NIL;

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			degree = graph.getOutDegreeFrom(u);//para digrafo tambem usa-se grau de saída
			if (degree % 2 != 0) {
				amountOddVertexes++;
				if (firstOddVertex == NIL)
					firstOddVertex = u;
			}
		}

		if (firstOddVertex == NIL)
			firstOddVertex = 0;
		return std::make_pair(amountOddVertexes, firstOddVertex);
	}

	const unsigned int dfsUtil(const unsigned int u) {
		visited[u] = true;
		unsigned int count = 1;

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (visited[*v] == false)
				count += dfsUtil(*v);
		return count;
	}

	const bool isBridge(const unsigned int u, const unsigned int v) {
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

	void fleuryR(const unsigned int u) {
		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (isBridge(u, *v) == false) {
				graph.writeVertex(u);
				std::cout << "->";
				graph.writeVertex(*v);
				std::cout << std::endl;
				graph.removeEdge(u, *v);
				fleuryR(*v);
				break;
			}
	}

public:
	Fleury() = delete;
	Fleury(const Graph& graph) noexcept(false) : graph(graph) {
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~Fleury() {
		delete[] visited;
		visited = nullptr;
	}

	void fleury() {
		std::cout << "Fleury:" << std::endl;

		/*
		se o número de vertices com grau impar for:
		+ maior que 2 entao o grafo nao e euleriano.
		+ igual a 0 entao o grafo e euleriano.
		+ igual a 2 entao o grafo e semi-euleriano.
		Observe que a contagem impar nunca pode ser 1 para grafo nao direcionado.
		*/

		if (isConnected()) {
			const std::pair<unsigned int, unsigned int> pair = validateGraph();

			if (pair.first > 2) {
				std::cout << pair.first << " vertices tem grau impar" << std::endl << "O Grafo nao e euleriano" << std::endl;
			} else {
				if (pair.first == 0)
					std::cout << "Todos os vertices tem grau par" << std::endl << "E possivel encontrar um caminho euleriano." << std::endl;
				else if (pair.first == 2)
					std::cout << "Dois vertices tem grau impar" << std::endl << "E possivel encontrar um caminho semi-euleriano." << std::endl;
				fleuryR(pair.second);
			}
		} else
			std::cout << "O grafo é desconexo e nao e euleriano" << std::endl;
	}
};