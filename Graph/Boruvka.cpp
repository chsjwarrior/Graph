#include "Boruvka.h"

//Constructor
Boruvka::Boruvka(const Graph& graph) noexcept(false) : graph(graph) {
	if (graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser nao dirigido para o algoritmo Boruvka funcionar.");

	cheapest = new unsigned int[graph.AMOUNT_VERTEXES];
	subsets = new std::pair<unsigned int, unsigned int>[graph.AMOUNT_VERTEXES];
}

//Destructor
Boruvka::~Boruvka() {
	delete cheapest;
	cheapest = nullptr;
	delete[] subsets;
	subsets = nullptr;
}

unsigned int Boruvka::find(const unsigned int u) {
	if (subsets[u].first != u)
		subsets[u].first = find(subsets[u].first);
	return subsets[u].first;
}

void Boruvka::makeUnion(const unsigned int u, const unsigned int v) {
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

void Boruvka::makeSet() {
	std::multiset<Edge> set = graph.getEdges();

	for (auto e = set.cbegin(); !set.empty(); e = set.erase(e))
		edges.emplace_back(e->U, e->V, e->WEIGHT);
}

void Boruvka::boruvka() {
	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		subsets[u].first = u;
		subsets[u].second = 0;
	}

	makeSet();

	int numTrees = graph.AMOUNT_VERTEXES;
	int MSTweight = 0;

	std::cout << "Boruvka:" << std::endl;
	while (numTrees > 1) {
		memset(cheapest, NIL, sizeof(unsigned int) * graph.AMOUNT_VERTEXES);

		for (unsigned int i = 0; i < edges.size(); ++i) {
			unsigned int set1 = find(edges[i].U);
			unsigned int set2 = find(edges[i].V);

			if (set1 != set2) {
				if (cheapest[set1] == NIL ||
					edges[cheapest[set1]].WEIGHT > edges[i].WEIGHT)
					cheapest[set1] = i;

				if (cheapest[set2] == -1 ||
					edges[cheapest[set2]].WEIGHT > edges[i].WEIGHT)
					cheapest[set2] = i;
			}
		}

		// Consider the above picked cheapest edges and add them to MST 
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i) {
			// Check if cheapest for current set exists 
			if (cheapest[i] != -1) {
				int set1 = find(edges[cheapest[i]].U);
				int set2 = find(edges[cheapest[i]].V);

				if (set1 != set2) {
					MSTweight += edges[cheapest[i]].WEIGHT;
					graph.writeEdge(edges[cheapest[i]]);
					std::cout << std::endl;
					// Do a union of set1 and set2 and decrease number 
					// of trees 
					makeUnion(set1, set2);
					numTrees--;
				}
			}
		}
	}
	std::cout << "Weight of MST is " << MSTweight << std::endl;
	return;
}
