#include "DisjointAssemblies.h"

//Constructor
DisjointAssemblies::DisjointAssemblies(const Graph& graph) : graph(graph) {
	edges = graph.getEdges();
}

//Destructor
DisjointAssemblies::~DisjointAssemblies() {
	edges.clear();
	for (auto set = sets.begin(); set != sets.end(); set = sets.erase(set))
		set->clear();
	sets.clear();
}

void DisjointAssemblies::print(const std::string& title) const {
	std::cout << title;
	for (auto set = sets.cbegin(); set != sets.cend(); ++set) {
		for (auto u = set->cbegin(); u != set->cend(); ++u)
			graph.writeVertex(*u);
		std::cout << '\t';
	}
	std::cout << std::endl;
}

void DisjointAssemblies::sameComponent(const unsigned int u, const unsigned int v) {
	auto set = sets.begin(), setU = sets.end(), setV = sets.end();
	while (set != sets.end() && (setU == sets.end() || setV == sets.end())) {
		if (setU == sets.end() && set->find(u) != set->cend())
			setU = set;
		if (setV == sets.end() && set->find(v) != set->cend())
			setV = set;
		set++;
	}

	if (setU != setV) {
		setU->insert(setV->cbegin(), setV->cend());
		sets.erase(setV);
	}
	graph.writeVertex(u);
	graph.writeVertex(v);
	print("|");
}

void DisjointAssemblies::makeSet(const unsigned int u) {
	std::set<unsigned int, std::less<unsigned int>> set;
	set.insert(u);
	sets.push_back(set);
}

void DisjointAssemblies::connectedComponents() {
	std::cout << "Conjuntos disjuntos:" << std::endl;
	std::cout << '\t' << '|';
	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		makeSet(u);
		graph.writeVertex(u);
		std::cout << '\t';
	}
	std::cout << std::endl;
	for (auto e = edges.cbegin(); !edges.empty(); e = edges.erase(e))
		sameComponent(e->U, e->V);
}
