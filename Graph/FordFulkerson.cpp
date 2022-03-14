#include "FordFulkerson.h"

//Constructor
FordFulkerson::FordFulkerson(const Graph& graph) noexcept(false) : graph(graph) {
	if (!graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser dirigido para o algoritmo de Ford-Fulkerson funcionar.");

	costMatrix = new int* [graph.AMOUNT_VERTEXES];
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i)
		costMatrix[i] = new int[graph.AMOUNT_VERTEXES];

	predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
	visited = new bool[graph.AMOUNT_VERTEXES];
}

//Destructor
FordFulkerson::~FordFulkerson() {
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i) {
		delete[] costMatrix[i];
		costMatrix[i] = nullptr;
	}
	delete[] costMatrix;
	delete[] predecessor;
	delete[] visited;
	costMatrix = nullptr;
	predecessor = nullptr;
	visited = nullptr;
}

void FordFulkerson::print(const std::string& title) const {}

bool FordFulkerson::bfsUtil(unsigned int u, const unsigned int k) {
	memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);

	std::queue<unsigned int> queue;
	queue.push(u);
	visited[u] = true;
	predecessor[u] = NIL;
	while (!queue.empty()) {
		u = queue.front();
		queue.pop();

		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
			if (visited[*v] == false) {
				queue.push(*v);
				predecessor[*v] = u;
				visited[*v] = true;
			}
		}
	}

	return visited[k];
}

void FordFulkerson::fordFulkerson(const unsigned int source, const unsigned int sink) {
	std::cout << "Ford-Fulkerson:" << std::endl;

	unsigned int u, v;
	int maxFlow = 0;
	for (u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		predecessor[u] = NIL;
		for (v = 0; v < graph.AMOUNT_VERTEXES; ++v)
			costMatrix[u][v] = graph.getWeigthFrom(u, v);
	}

	while (bfsUtil(source, sink)) {
		int pathFlow = INF;

		for (v = sink; v != source; v = predecessor[v]) {
			u = predecessor[v];
			pathFlow = std::min(pathFlow, graph.getWeigthFrom(u, v));
		}

		for (v = sink; v != source; v = predecessor[v]) {
			u = predecessor[v];
			costMatrix[u][v] -= pathFlow;
			costMatrix[v][u] += pathFlow;
		}

		maxFlow += pathFlow;
	}
	std::cout << "O fluxo maximo possivel e: " << maxFlow << std::endl;
}