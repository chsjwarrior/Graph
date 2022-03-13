#include "Goodman.h"

//Constructor
Goodman::Goodman(const Graph& graph) noexcept(false) : graph(graph) {
	if (graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser nao dirigido para o algoritmo de Goodman funcionar.");
}

//Destructor
Goodman::~Goodman() {
	vertices.clear();
	for (auto set = sets.begin(); set != sets.end(); ++set)
		set->clear();
	sets.clear();
}

void Goodman::makeSet(const unsigned int u) {
	std::list<unsigned int> set;
	set.push_back(u);
	sets.push_back(set);
}

void Goodman::print() const {
	unsigned int i = 0;
	for (auto set = sets.cbegin(); set != sets.cend(); ++set) {
		std::cout << "Conjunto " << ++i << ": ";
		for (auto u = set->cbegin(); u != set->cend(); ++u) {
			graph.writeVertex(*u);
			std::cout << '+';
		}
		std::cout << '|';
	}
	std::cout << std::endl;
}

void Goodman::goodman() {
	std::cout << "Goodman:" << std::endl;
	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u)
		vertices.insert(u);

	while (!vertices.empty()) {
		unsigned int u = *vertices.rbegin();
		vertices.erase(u);
		makeSet(u);

		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		while (!adjacences.empty()) {
			unsigned int v = *adjacences.cbegin();
			adjacences.erase(adjacences.cbegin());
			graph.removeEdge(u, v);
			if (u == v)
				continue;
			sets.back().push_back(v);
			print();
			graph.printAdjacenceList();
			for (auto vv = adjacences.cbegin(); !adjacences.empty(); vv = adjacences.erase(vv)) {
				graph.insertEdge(v, *vv, graph.getWeigthFrom(u, *vv));
				graph.removeEdge(u, *vv);
			}
			graph.printAdjacenceList();
			u = v;
			vertices.erase(u);
			adjacences.clear();
			adjacences = graph.getAdjacencesFrom(u);
		}
	}
}