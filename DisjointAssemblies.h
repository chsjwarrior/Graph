#pragma once
#include "Graph.h"

using namespace Scanner;

/*
funcionando
*/

class DisjointAssemblies {
private:
	const unsigned int AMOUNT_VERTEXES;
	std::multiset<Edge> edges;
	std::list<std::set<unsigned int>> sets;

	void sameComponent(const unsigned int& u, const unsigned int& v) {
		auto set = sets.begin(), setU = sets.end(), setV = sets.end();
		while(set != sets.end() && (setU == sets.end() || setV == sets.end())) {
			if(setU == sets.end() && set->find(u) != set->cend())
				setU = set;
			if(setV == sets.end() && set->find(v) != set->cend())
				setV = set;
			set++;
		}

		if(setU != setV) {
			setU->insert(setV->cbegin(), setV->cend());
			sets.erase(setV);
		}
		writeVertex(u);
		writeVertex(v);
		write("|");
		print();
	}

	void makeSet(unsigned int& u) {
		std::set<unsigned int, std::less<unsigned int>> set;
		set.insert(u);
		sets.push_back(set);
	}

	void print() const {
		for(auto set = sets.cbegin(); set != sets.cend(); set++) {
			for(auto u = set->cbegin(); u != set->cend(); u++)
				writeVertex(*u);
			write("\t");;
		}
		write("\n");
	}

public:
    DisjointAssemblies() = delete;
	DisjointAssemblies(const Graph& graph) : AMOUNT_VERTEXES(graph.AMOUNT_VERTEXES) {
		edges = graph.getEdges();
	}

	~DisjointAssemblies() {
		edges.clear();
		for(auto set = sets.begin(); set != sets.end(); set = sets.erase(set))
			set->clear();
		sets.clear();
	}

	void connectedComponents() {
		writeln("Conjuntos disjuntos:");
		write("\t", "|");
		for(unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			makeSet(u);
			writeVertex(u);
			write("\t");
		}
		write("\n");
		for(auto e = edges.cbegin(); e != edges.cend(); e = edges.erase(e))
			sameComponent(e->U, e->V);
	}
};
