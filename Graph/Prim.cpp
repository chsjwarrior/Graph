#include "Prim.h"

//Constructor
Prim::Prim(const Graph& graph) noexcept(false) : graph(graph) {
	if (graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser nao dirigido para o algoritmo Prim funcionar.");

	key = new int[graph.AMOUNT_VERTEXES];
	predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
	visited = new bool[graph.AMOUNT_VERTEXES];
}

//Destructor
Prim::~Prim() {
	delete[] key;
	delete[] predecessor;
	delete[] visited;
	key = nullptr;
	predecessor = nullptr;
	visited = nullptr;
}

void Prim::print(const std::string& title) const {
	PageTable table(title, PageTable::HeaderOrientation::ROW);
	table.setColumnsForPage(20);

	table.addHeader({ "Vi", "Ki", "Pi" });
	table.setColumnCount(graph.AMOUNT_VERTEXES);
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i) {
		table.setColumnMaxWidth(i, 4);
		table.updateValueAt(0, i, graph.getVertexName(i));
	}
	table.addRow(key, graph.AMOUNT_VERTEXES);
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i)
		table.updateValueAt(2, i, graph.getVertexName(predecessor[i]));

	table.print();
}

unsigned int Prim::extractMin(std::list<unsigned int>& queue) {
	int lowerDistance = INF;
	unsigned int lowerVertex = NIL;
	for (const auto& u : queue)
		if (key[u] < lowerDistance) {
			lowerDistance = key[u];
			lowerVertex = u;
		}
	queue.remove(lowerVertex);
	return lowerVertex;
}

inline void Prim::relax(const unsigned int u, const unsigned int v, const int w) {
	if (graph.getWeigthFrom(u, v) < key[v]) {
		predecessor[v] = u;
		key[v] = w;
	}
}

void Prim::prim(const unsigned int source) {
	unsigned int u;
	std::list<unsigned int> queue;
	for (u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		key[u] = INF;
		predecessor[u] = NIL;
		visited[u] = false;
		queue.push_back(u);
	}
	key[source] = 0;

	while (!queue.empty()) {
		u = extractMin(queue);
		visited[u] = true;

		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (visited[*v] == false)
				relax(u, *v, graph.getWeigthFrom(u, *v));
	}
	print("Prim:");
}