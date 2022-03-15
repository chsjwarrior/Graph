#include "CloserNeighbor.h"

//Constructor
CloserNeighbor::CloserNeighbor(const Graph& graph) noexcept(false) : NonCopyable(), graph(graph) {
	visited = new bool[graph.AMOUNT_VERTEXES];
	total = NULL;
}

//Destructor
CloserNeighbor::~CloserNeighbor() {
	delete[] visited;
	visited = nullptr;
	total = NULL;
}

void CloserNeighbor::closerNeighborR(const unsigned int u) {
	visited[u] = true;
	print(graph.getVertexName(u));
	//graph.writeVertex(u);

	int lowerWeight = INF;
	unsigned int lowerVertex = NIL;
	std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
	for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
		if (visited[*v] == false && graph.getWeigthFrom(u, *v) < lowerWeight) {
			lowerVertex = *v;
			lowerWeight = graph.getWeigthFrom(u, *v);
		}
	if (lowerVertex != NIL) {
		print("->");
		total += graph.getWeigthFrom(u, lowerVertex);
		closerNeighborR(lowerVertex);
	}
}

void CloserNeighbor::closerNeighbor(const unsigned int source) {
	print("Vizinho mais proximo:\n");

	memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
	total = 0;
	closerNeighborR(source);

	if (std::all_of(visited, visited + graph.AMOUNT_VERTEXES, [](const bool& x) { return x == true; })) {
		print("->" + graph.getVertexName(source));
	}
	std::cout << "= " << total << std::endl;
}

void CloserNeighbor::closerNeighborRepetitive() {
	print("Vizinho mais proximo repetitivo:\n");

	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
		total = 0;
		closerNeighborR(u);

		if (std::all_of(visited, visited + graph.AMOUNT_VERTEXES, [](const bool& x) { return x == true; })) {
			print("->" + graph.getVertexName(u));
		}
		std::cout << "= " << total << std::endl;
	}
}