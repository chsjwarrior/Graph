#pragma once
#include "Graph.h"
#include <list>

/*
O algoritmo de Goodman serve para avaliar a conexidade em grafos não dirigidos.
*/

class Goodman {
private:
	const Graph& graph;
	std::set<unsigned int> vertices;
	std::list<std::list<unsigned int>> sets;

	const bool contains(const std::list<unsigned int>& set, const unsigned int& u) const {
		for(auto v = set.cbegin(); v != set.cend(); v++)
			if(*v == u)
				return true;
		return false;
	}

	void makeUnion(const unsigned int& u) {
		print();
		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for(auto v = adjacences.cbegin(); v != adjacences.cend(); v = adjacences.erase(v)) {
			if(!contains(sets.back(), *v)) {
				sets.back().push_back(*v);
				vertices.erase(*v);
				makeUnion(*v);
			}
		}
	}

	void makeSet(unsigned int& u) {
		std::list<unsigned int> set;
		set.push_back(u);
		sets.push_back(set);
	}

	void print() const {
		writeln("Goodman:");
		unsigned int i = 0;
		for(auto set = sets.begin(); set != sets.end(); set++) {
			write("Conjunto ", ++i, ":");
			for(auto u = set->begin(); u != set->end(); u++)
				writeVertex(*u);
			write("|");
		}
		write("\n");
	}

public:
    Goodman() = delete;
	Goodman(const Graph& graph) : graph(graph) {}

	~Goodman() {
		vertices.clear();
		for(auto set = sets.begin(); set != sets.end(); set++)
			set->clear();
		sets.clear();
	}

	void goodman() {
	    for (unsigned int u = 0; u < graph.AMOUNT_VERTICES; u++)
			vertices.insert(u);

		while(!vertices.empty()) {
			unsigned int u = *vertices.cbegin();
			makeSet(u);
			makeUnion(u);
		}
	}
};
