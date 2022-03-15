#include "BreadthFirstSearch.h"

//Constructor
BreadthFirstSearch::BreadthFirstSearch(const Graph& graph) noexcept(false) : NonCopyable(), graph(graph) {
	discovery = new unsigned int[graph.AMOUNT_VERTEXES];
	predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
	visited = new bool[graph.AMOUNT_VERTEXES];
}

//Destructor
BreadthFirstSearch::~BreadthFirstSearch() {
	delete[] discovery;
	delete[] predecessor;
	delete[] visited;
	discovery = nullptr;
	predecessor = nullptr;
	visited = nullptr;
}

void BreadthFirstSearch::print(const std::string& text) const {
	PageTable table(text, 0, graph.AMOUNT_VERTEXES, PageTable::HeaderOrientation::ROW);
	table.setColumnsForPage(20);

	table.addHeader({ "Vi", "Di", "Pi" });
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i) {
		table.setColumnMaxWidth(i, 4);
		table.updateValueAt(0, i, graph.getVertexName(i));
		table.updateValueAt(1, i, discovery[i]);
		table.updateValueAt(2, i, graph.getVertexName(predecessor[i]));
	}

	table.print();
}

void BreadthFirstSearch::bfsRecursive(std::queue<unsigned int>& queue) {
	if (queue.empty())
		return;

	unsigned int u = queue.front();
	queue.pop();

	std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
	for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
		if (visited[*v] == false) {
			queue.push(*v);
			discovery[*v] = discovery[u] + 1;
			predecessor[*v] = u;
			visited[*v] = true;
		}

	bfsRecursive(queue);
}

void BreadthFirstSearch::bfsIterative(std::queue<unsigned int>& queue) {
	unsigned int u;
	while (!queue.empty()) {
		u = queue.front();
		queue.pop();

		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (visited[*v] == false) {
				queue.push(*v);
				discovery[*v] = discovery[u] + 1;
				predecessor[*v] = u;
				visited[*v] = true;
			}
	}
}

void BreadthFirstSearch::bfs(const unsigned int source, const bool isRecursive) {
	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		discovery[u] = NIL;
		predecessor[u] = NIL;
		visited[u] = false;
	}

	std::queue<unsigned int> queue;
	discovery[source] = 0;
	visited[source] = true;
	queue.push(source);

	if (isRecursive) {
		bfsRecursive(queue);
		print("Busca em largura recursiva:");
	} else {
		bfsIterative(queue);
		print("Busca em largura iterativa:");
	}
}