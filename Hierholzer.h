#pragma once
#include <unordered_map>

class Hierholzer {
private:
	Graph graph;

public:
	Hierholzer() = delete;
	Hierholzer(const Graph& graph) : graph(graph) {}
	~Hierholzer() {}

	void hierholzer(const unsigned int& source) {
		std::stack<unsigned int> path;
		std::vector<unsigned int> circuit;

		path.push(source);
		unsigned int u = source;

		while (!path.empty()) {

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			if (!adjacences.empty()) {
				path.push(u);

				unsigned int v = *adjacences.crbegin();

				graph.removeEdge(u, v);

				u = v;
			} else {
				circuit.push_back(u);
				u = path.top();
				path.pop();
			}
		}

		for (auto i = circuit.crbegin(); i != circuit.crend(); ++i) {
			writeVertex(*i);
			if ((i + 1) != circuit.crend())
				write("->");
		}
		write("\n");
	}
};