#pragma once
/*
O algoritmo de DisjointAssebblies serve para avaliar a conexidade em grafos não dirigidos.
funcionando
*/
class DisjointAssemblies {
private:
	const Graph& graph;
	std::multiset<Edge> edges;
	std::list<std::set<unsigned int>> sets;

	void sameComponent(const unsigned int u, const unsigned int v) {
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
		std::cout << '|';
		print();
	}

	void makeSet(const unsigned int u) {
		std::set<unsigned int, std::less<unsigned int>> set;
		set.insert(u);
		sets.push_back(set);
	}

	void print() const {
		for (auto set = sets.cbegin(); set != sets.cend(); set++) {
			for (auto u = set->cbegin(); u != set->cend(); u++)
				graph.writeVertex(*u);
			std::cout << '\t';
		}
		std::cout << std::endl;
	}

public:
	DisjointAssemblies() = delete;
	DisjointAssemblies(const Graph& graph) : graph(graph) {
		edges = graph.getEdges();
	}

	~DisjointAssemblies() {
		edges.clear();
		for (auto set = sets.begin(); set != sets.end(); set = sets.erase(set))
			set->clear();
		sets.clear();
	}

	void connectedComponents() {
		std::cout << "Conjuntos disjuntos:" << std::endl;
		std::cout << '\t' << '|';
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			makeSet(u);
			graph.writeVertex(u);
			std::cout << '\t';
		}
		std::cout << std::endl;
		for (auto e = edges.cbegin(); !edges.empty(); e = edges.erase(e))
			sameComponent(e->U, e->V);
	}
};
