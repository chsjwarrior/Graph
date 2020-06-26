#pragma once

class Kruskal {
private:
	const unsigned int AMOUNT_VERTEXES;

	struct LessWeight {
		const bool operator()(const Edge& lhs, const Edge& rhs) const {
			return lhs.WEIGHT < rhs.WEIGHT;
		}
	};

	std::multiset<Edge, LessWeight> edges;
	std::pair<unsigned int, unsigned int>* subSets;
	//pair.first = parent;
	//pair.second = rank;

	const unsigned int find(const unsigned int& u) const {
		if (subSets[u].first != u)
			subSets[u].first = find(subSets[u].first);
		return subSets[u].first;
	}

	void makeUnion(const unsigned int& u, const unsigned int& v) const {
		const unsigned int uRoot = find(u);
		const unsigned int vRoot = find(v);

		if (subSets[uRoot].second < subSets[vRoot].second)
			subSets[uRoot].first = vRoot;
		else if (subSets[uRoot].second > subSets[vRoot].second)
			subSets[vRoot].first = uRoot;
		else {
			subSets[vRoot].first = uRoot;
			subSets[uRoot].second++;
		}
	}

public:
	Kruskal() = delete;
	Kruskal(const Graph& graph) : AMOUNT_VERTEXES(graph.AMOUNT_VERTEXES) {
		std::multiset<Edge> set = graph.getEdges();
		for (auto e = set.cbegin(); !set.empty(); e = set.erase(e))
			edges.emplace(e->U, e->V, e->WEIGHT);
		subSets = new std::pair<unsigned int, unsigned int>[graph.AMOUNT_VERTEXES];
	}

	~Kruskal() {
		delete[] subSets;
		subSets = nullptr;
	}

	void kruskal() {
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			subSets[u].first = u;
			subSets[u].second = 0;
		}

		writeln("Kruskal:");
		while (!edges.empty()) {

			unsigned int x = find(edges.cbegin()->U);
			unsigned int y = find(edges.cbegin()->V);

			if (x != y) {
				makeUnion(edges.cbegin()->U, edges.cbegin()->V);
				edges.cbegin()->print();
				write("\n");
			}

			edges.erase(edges.cbegin());
		}
	}
};