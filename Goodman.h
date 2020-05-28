#pragma once
#include "Graph.h"
#include <list>

/*
O algoritmo de Goodman serve para avaliar a conexidade em grafos não dirigidos.
*/

class Goodman {
private:
	Graph graph;
	std::set<unsigned int> vertices;
	std::list<std::list<unsigned int>> sets;

	void makeSet(unsigned int& u) {
		std::list<unsigned int> set;
		set.push_back(u);
		sets.push_back(set);
	}

	void print() const {
		writeln("Goodman:");
		unsigned int i = 0;
		for (auto set = sets.cbegin(); set != sets.cend(); set++) {
			write("Conjunto ", ++i, ":");
			for (auto u = set->cbegin(); u != set->cend(); u++) {
				writeVertex(*u);
				write("+");
			}
			write("|");
		}
		write("\n");
	}

public:
	Goodman() = delete;
	Goodman(const Graph& graph) : graph(graph) {}

	~Goodman() {
		vertices.clear();
		for (auto set = sets.begin(); set != sets.end(); set++)
			set->clear();
		sets.clear();
	}

	void goodman() {
		if (graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser nao dirigido para o algoritmo de Goodman funcionar.");
			return;
		}

		for (unsigned int u = 0; u < graph.AMOUNT_VERTICES; u++)
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
				for (auto vv = adjacences.cbegin(); !adjacences.empty(); vv = adjacences.erase(vv)) {
					graph.insertEdge(v, *vv, graph.getWeigthFrom(u, *vv));
					graph.removeEdge(u, *vv);
				}
				u = v;
				vertices.erase(u);
				adjacences = graph.getAdjacencesFrom(u);
			}
		}
	}
};