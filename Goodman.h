#pragma once
#include <list>

/*
O algoritmo de Goodman serve para avaliar a conexidade em grafos não dirigidos.

falhou no seguinte grafo:
8 8 0
1 3 3
2 3 2
3 4 4
3 5 5
4 7 3
5 7 5
5 6 1
5 8 7
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
		unsigned int i = 0;
		for (auto set = sets.cbegin(); set != sets.cend(); set++) {
			write("Conjunto ", ++i, ':');
			for (auto u = set->cbegin(); u != set->cend(); u++) {
				writeVertex(*u);
				write('+');
			}
			write('|');
		}
		write("\n");
	}

public:
	Goodman() = delete;
	Goodman(const Graph& graph) : graph(graph) {
		if (graph.IS_DIGRAPH)
			throw std::exception("O Grafo precisa ser nao dirigido para o algoritmo de Goodman funcionar.");
	}

	~Goodman() {
		vertices.clear();
		for (auto set = sets.begin(); set != sets.end(); set++)
			set->clear();
		sets.clear();
	}

	void goodman() {
		writeln("Goodman:");
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
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
};