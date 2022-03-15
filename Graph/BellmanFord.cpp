#include "BellmanFord.h"

//Constructor
BellmanFord::BellmanFord(const Graph& graph) noexcept(false) : NonCopyable(), graph(graph) {
	if (!graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser dirigido para o algoritmo Bellman - Ford funcionar.");

	distance = new int[graph.AMOUNT_VERTEXES];
	predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
}

//Destructor
BellmanFord::~BellmanFord() {
	delete[] distance;
	delete[] predecessor;
	distance = nullptr;
	predecessor = nullptr;
}

void BellmanFord::print(const std::string& text) const {
	PageTable table(text, PageTable::HeaderOrientation::ROW);
	table.setColumnsForPage(20);

	table.addHeader({ "Vi","Di","Pi" });
	table.setColumnCount(graph.AMOUNT_VERTEXES);
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i) {
		table.setColumnMaxWidth(i, 4);
		table.updateValueAt(0, i, graph.getVertexName(i));
		table.updateValueAt(1, i, distance[i]);
		table.updateValueAt(2, i, graph.getVertexName(predecessor[i]));
	}

	table.print();
}

void BellmanFord::bellmanFord(const unsigned int source) {
	unsigned int u;
	for (u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		distance[u] = INF;
		predecessor[u] = NIL;
	}

	distance[source] = 0;
	//esse algoritmo garante a menor distancia
	std::multiset<Edge> edges = graph.getEdges();
	for (u = 0; u < graph.AMOUNT_VERTEXES; ++u)
		for (const auto& e : edges)
			if (distance[e.U] != INF && distance[e.U] + e.WEIGHT < distance[e.V]) {
				distance[e.V] = distance[e.U] + e.WEIGHT;
				predecessor[e.V] = e.U;
			}

	//esse algoritmo verifica se o grafo possui ciclo negativo
	for (const auto& e : edges)
		if (distance[e.U] != INF && distance[e.U] + e.WEIGHT < distance[e.V]) {
			std::cout << "O Grafo contem ciclo com peso negativo" << std::endl;
			break;
		}

	edges.clear();
	print("Bellman-Ford:");
}