#pragma once
#include <stack>

/*
O Algoritmo Kosaraju detecta componentes fortemente conectadas.
*/

class Kosaraju {
private:
	Graph graph;
	bool* visited;
	std::stack<int> stack;

	void fillOrder(const unsigned int& u) {
		visited[u] = true;

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (!visited[*v])
				fillOrder(*v);

		stack.push(u);
	}

	void graphTranspose() {
		std::multiset<Edge> edges = graph.getEdges();

		const int amountVertexes = graph.AMOUNT_VERTEXES;
		const bool isDigraph = graph.IS_DIGRAPH;
		graph = Graph(amountVertexes, isDigraph);

		for (auto e = edges.cbegin(); !edges.empty(); e = edges.erase(e))
			graph.insertEdge(e->V, e->U, e->WEIGHT);
	}

	void dfs(int u) {		
		writeVertex(u);
		write(" ");

		visited[u] = true;

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (!visited[*v])
				dfs(*v);
	}

public:
	Kosaraju() = delete;
	Kosaraju(Graph& graph) : graph(graph) {
		visited = new bool[graph.AMOUNT_VERTEXES];
	}
	~Kosaraju() {
		delete[] visited;
		visited = nullptr;
	}

	void kosaraju() {
		memset(visited, false, sizeof(visited));

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (!visited[u])
				fillOrder(u);

		graphTranspose();

		memset(visited, false, sizeof(visited));

		writeln("Kosaraju:");
		unsigned int c = 1;
		while (!stack.empty()) {
			int u = stack.top();
			stack.pop();

			if (!visited[u]) {
				write("Conjunto", c++, ": {");
				dfs(u);
				write("}\n");
			}
		}
	}
};