#pragma once
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
			if (visited[*v] == false)
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

	void dfs(const unsigned int& u) {
		writeVertex(u);
		write(' ');
		visited[u] = true;

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (visited[*v] == false)
				dfs(*v);
	}

public:
	Kosaraju() = delete;
	Kosaraju(Graph& graph) : graph(graph) {
		if (!graph.IS_DIGRAPH)
			throw std::exception("O Grafo precisa ser dirigido para o algoritmo Kosaraju funcionar.");

		visited = new bool[graph.AMOUNT_VERTEXES];
	}
	~Kosaraju() {
		delete[] visited;
		visited = nullptr;
	}

	void kosaraju() {
		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (visited[u] == false)
				fillOrder(u);

		graphTranspose();

		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);

		writeln("Kosaraju:");
		unsigned int c = 1;
		while (!stack.empty()) {
			int u = stack.top();
			stack.pop();

			if (!visited[u]) {
				write("C", c++, ": { ");
				dfs(u);
				write("}\n");
			}
		}
	}
};