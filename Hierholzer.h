#pragma once

/*
O algoritmo de Hierholzer é utilizado para a identificação de um ciclo euleriano em um grafo.
*/

class Hierholzer {
private:
	Graph graph;

public:
	Hierholzer() = delete;
	Hierholzer(const Graph& graph) : graph(graph) {}
	~Hierholzer() {}

	void hierholzer(const unsigned int& source) {
		if (!graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser dirigido para o algoritmo Hierholzer funcionar.");
			return;
		}

		std::stack<unsigned int> path;
		std::vector<unsigned int> circuit;

		path.push(source);
		unsigned int u, v;

		while (!path.empty()) {
			u = path.top();
			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);

			if (!adjacences.empty()) {
				v = *adjacences.crbegin();
				graph.removeEdge(u, v);
				path.push(v);
			} else {
				circuit.push_back(path.top());
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