#pragma once
#include "Graph.h"

using namespace Scanner;

class Kruskal {
private:
    const Graph& graph;

    struct Comparator{
	    const bool operator()(const Edge& lhs, const Edge& rhs) const {
	        return lhs.WEIGHT < rhs.WEIGHT;
	    }
	};

    std::priority_queue<Edge, std::deque<Edge> ,Comparator> edges;
	std::pair<unsigned int, unsigned int>* subSets;
	//pair.first = parent;
	//pair.second = rank;

	const unsigned int find(const unsigned int& u) const {
		if(subSets[u].first != u)
			subSets[u].first = find(subSets[u].first);
		return subSets[u].first;
	}

	void makeUnion(const unsigned int& u, const unsigned int& v) const {
		const unsigned int uRoot = find(u);
		const unsigned int vRoot = find(v);

		if(subSets[uRoot].second < subSets[vRoot].second)
			subSets[uRoot].first = vRoot;
		else if(subSets[uRoot].second > subSets[vRoot].second)
			subSets[vRoot].first = uRoot;
		else {
			subSets[vRoot].first = uRoot;
			subSets[uRoot].second++;
		}
	}

public:
    Kruskal() = delete;
	Kruskal(const Graph& graph) : graph(graph) {
	    std::multiset<Edge> set = graph.getEdges();
	    for (auto e = set.cbegin(); e != set.cend(); e = set.erase(e))
            edges.push(*e);
		subSets = new std::pair<unsigned int, unsigned int>[graph.AMOUNT_VERTICES];
	}

	~Kruskal() {
		delete[] subSets;
		subSets = nullptr;
	}

	void kruskal() {
		writeln("Kruskal:");
		for(unsigned int u = 0; u < graph.AMOUNT_VERTICES; u++) {
			subSets[u].first = u;
			subSets[u].second = 0;
		}

		while (!edges.empty()) {
		    Edge e = edges.top();
		    edges.pop();

			unsigned int x = find(e.U);
			unsigned int y = find(e.V);

			if(x != y) {
				makeUnion(e.U, e.V);
				e.print();
				write("\n");
			}
		}
	}
};
