#include "DepthFirstSearch.h"

//Constructor
DepthFirstSearch::DepthFirstSearch(const Graph& graph) noexcept(false) : graph(graph) {
	discovery = new unsigned int[graph.AMOUNT_VERTEXES];
	close = new unsigned int[graph.AMOUNT_VERTEXES];
	visited = new bool[graph.AMOUNT_VERTEXES];
	time = NULL;
}

//Destructor
DepthFirstSearch::~DepthFirstSearch() {
	delete[] discovery;
	delete[] close;
	delete[] visited;
	discovery = nullptr;
	close = nullptr;
	visited = nullptr;
	time = NULL;
}

void DepthFirstSearch::print(const std::string& title) const {
	PageTable table(title, 0, graph.AMOUNT_VERTEXES, PageTable::HeaderOrientation::ROW);
	table.setColumnsForPage(20);

	table.addHeader({ "Vi","Di", "Ci" });
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i) {
		table.setColumnMaxWidth(i, 4);
		table.updateValueAt(0, i, graph.getVertexName(i));
		table.updateValueAt(1, i, discovery[i]);
		table.updateValueAt(2, i, close[i]);
	}

	table.print();
}

void DepthFirstSearch::dfsVisitRecursive(const unsigned int u) {
	visited[u] = true;
	discovery[u] = ++time;

	std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
	for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
		if (visited[*v] == false)
			dfsVisitRecursive(*v);

	close[u] = ++time;
}

void DepthFirstSearch::dfsVisitIterative(unsigned int u) {
	std::stack<unsigned int> stack;

	stack.push(u);
	while (!stack.empty()) {
		u = stack.top();

		if (visited[u] == false) {
			visited[u] = true;
			discovery[u] = ++time;

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.crbegin(); v != adjacences.crend(); ++v)
				if (visited[*v] == false)
					stack.push(*v);

			adjacences.clear();
		} else {
			if (close[u] == NIL)
				close[u] = ++time;
			stack.pop();
		}
	}
}

void DepthFirstSearch::dfs(const unsigned int source, const bool isRecursive) {
	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		discovery[u] = NIL;
		close[u] = NIL;
		visited[u] = false;
	}

	time = 0;
	for (unsigned int u = 0, v = source; u < graph.AMOUNT_VERTEXES; ++u) {
		if (visited[v] == false)
			if (isRecursive)
				dfsVisitRecursive(v);
			else
				dfsVisitIterative(v);
		v = u;
	}

	if (isRecursive)
		print("Busca em profundidade recursiva:");
	else
		print("Busca em profundidade iterativa:");
}