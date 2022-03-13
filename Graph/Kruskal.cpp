#include "Kruskal.h"

//Constructor
Kruskal::Kruskal(const Graph& graph) noexcept(false) : graph(graph) {
	if (graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser nao dirigido para o algoritmo Kruskal funcionar.");

	subsets = new std::pair<unsigned int, unsigned int>[graph.AMOUNT_VERTEXES];
}

//Destructor
Kruskal::~Kruskal() {
	delete[] subsets;
	subsets = nullptr;
}

unsigned int Kruskal::find(const unsigned int u) {
	if (subsets[u].first != u)
		subsets[u].first = find(subsets[u].first);
	return subsets[u].first;
}

void Kruskal::makeUnion(const unsigned int u, const unsigned int v) {
	const unsigned int uRoot = find(u);
	const unsigned int vRoot = find(v);

	if (subsets[uRoot].second < subsets[vRoot].second)
		subsets[uRoot].first = vRoot;
	else if (subsets[uRoot].second > subsets[vRoot].second)
		subsets[vRoot].first = uRoot;
	else {
		subsets[vRoot].first = uRoot;
		subsets[uRoot].second++;
	}
}

inline void Kruskal::makeSet(const unsigned int v) {
	subsets[v].first = v;
	subsets[v].second = 0;
}

std::multiset<Edge, Kruskal::LessWeight> Kruskal::getEdgesLessWeight() {
	std::multiset<Edge> set = graph.getEdges();
	std::multiset<Edge, LessWeight> edges(set.cbegin(), set.cend());
	return edges;
}

void Kruskal::kruskal() {
	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u)
		makeSet(u);

	std::multiset<Edge, LessWeight> edges(getEdgesLessWeight());

	PageTable table("Kruskal", PageTable::HeaderOrientation::COLUMN);
	table.addHeader({ "Edge", "C(e)", "" });

	while (!edges.empty()) {
		unsigned int u = find(edges.cbegin()->U);
		unsigned int v = find(edges.cbegin()->V);

		if (u != v)
			makeUnion(edges.cbegin()->U, edges.cbegin()->V);

		table.setRowCount(table.getRowCount() + 1);
		table.updateValueAt(table.getRowCount() - 1, 0, graph.getEdgeName(*edges.cbegin()));
		table.updateValueAt(table.getRowCount() - 1, 1, edges.cbegin()->WEIGHT);
		table.updateValueAt(table.getRowCount() - 1, 2, u != v);

		edges.erase(edges.cbegin());
	}

	table.print();
}