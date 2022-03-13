#include "Dijkstra.h"

//Construtor
Dijkstra::Dijkstra(const Graph& graph) noexcept(false) : graph(graph) {
	distance = new int[graph.AMOUNT_VERTEXES];
	predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
	visited = new bool[graph.AMOUNT_VERTEXES];
}

//Destructor
Dijkstra::~Dijkstra() {
	delete[] distance;
	delete[] predecessor;
	delete[] visited;
	distance = nullptr;
	predecessor = nullptr;
	visited = nullptr;
}

unsigned int Dijkstra::extractMin(std::list<unsigned int>& queue) {
	int lowerDistance = INF;
	unsigned int lowerVertex = NIL;

	for (const auto u : queue)
		if (distance[u] < lowerDistance) {//distance[u] <= lowerValue, verificar
			lowerDistance = distance[u];
			lowerVertex = u;
		}
	queue.remove(lowerVertex);
	return lowerVertex;
}

inline void Dijkstra::relax(const unsigned int u, const unsigned int v, const int w) {
	if (distance[v] > distance[u] + w) {
		distance[v] = distance[u] + w;
		predecessor[v] = u;
	}
}

void Dijkstra::print() const {
	PageTable table("Dijkstra:", 0, graph.AMOUNT_VERTEXES, PageTable::HeaderOrientation::ROW);
	table.setColumnsForPage(20);

	table.addHeader({ "Vi", "Di", "Pi" });
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i) {
		table.setColumnMaxWidth(i, 4);
		table.updateValueAt(0, i, graph.getVertexName(i));
		table.updateValueAt(1, i, distance[i]);
		table.updateValueAt(2, i, graph.getVertexName(predecessor[i]));
	}

	table.print();
}

void Dijkstra::dijkstra(const unsigned int source) {
	unsigned int u;
	std::list<unsigned int> queue;
	for (u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		distance[u] = INF;
		predecessor[u] = NIL;
		visited[u] = false;
		queue.push_back(u);
	}
	distance[source] = 0;

	while (!queue.empty()) {
		u = extractMin(queue);
		visited[u] = true;

		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (visited[*v] == false)
				relax(u, *v, graph.getWeigthFrom(u, *v));
		//if (graph.getWeigthFrom(u, *v) > 0)se o peso é negativo deveria gerar exceção.
	}
	print();
}