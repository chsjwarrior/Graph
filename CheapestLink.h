#pragma once

/*
O algoritmo da ligação mais economica encontra um ciclo hamiltoniano no grafo passando pelas aresta com menor peso.
Essa implementação do algoritmo ainda não esta funcionando para grafos semi-hamiltoniano.
testado e funcionando com o seguinte grafo:
5 10 0
1 2 185
1 3 119
1 4 152
1 5 133
2 3 121
2 4 150
2 5 200
3 4 174
3 5 120
4 5 199
*/

class CheapestLink {
private:
	const Graph& graph;
	unsigned int* degrees;
	bool* visited;

	struct GreaterWeight {
		const bool operator()(const Edge& lhs, const Edge& rhs) const {
			return lhs.WEIGHT > rhs.WEIGHT;
		}
	};

	std::priority_queue<Edge, std::vector<Edge>, GreaterWeight> edges;
	std::vector<Edge> selected;

	bool cyclic_recursive(const unsigned int& vertex, const  unsigned int& predecessor) {
		bool cycle_found = false;
		visited[vertex] = true;
		for (auto e = selected.cbegin(); e != selected.cend() && !cycle_found; ++e) {
			if (e->U == vertex || e->V == vertex) {
				const unsigned int neighbour = e->U == vertex ? e->V : e->U;
				if (!visited[neighbour]) {
					cycle_found = cyclic_recursive(neighbour, vertex);
				} else if (neighbour != predecessor) {
					cycle_found = true;
				}
			}
		}
		return cycle_found;
	}

	bool cyclic() {
		memset(visited, false, sizeof(visited));
		return cyclic_recursive(0, 0);
	}

public:
	CheapestLink() = delete;
	CheapestLink(const Graph& graph) : graph(graph) {
		std::multiset<Edge> set = graph.getEdges();
		for (auto e = set.cbegin(); !set.empty(); e = set.erase(e))
			edges.push(*e);
		degrees = new unsigned int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
		selected.reserve(graph.AMOUNT_VERTEXES);
	}

	~CheapestLink() {
		delete[] degrees;
		delete[] visited;
		degrees = nullptr;
		visited = nullptr;
		selected.clear();
	}

	void cheaperConnection() {
		if (graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser nao dirigido para o algoritmo de da ligação mais economica funcionar.");
			return;
		}

		writeln("Ligacao mais economica:");

		memset(degrees, 0, sizeof(degrees));

		Edge lowerWeight = edges.top();
		selected.emplace_back(lowerWeight.U, lowerWeight.V, lowerWeight.WEIGHT);
		degrees[lowerWeight.U]++;
		degrees[lowerWeight.V]++;
		lowerWeight.print();
		write("=", lowerWeight.WEIGHT);
		write(" entry\n");
		edges.pop();

		//bool hasZeroDegree = true;
		while (!edges.empty()) {
			lowerWeight = edges.top();

			if (degrees[lowerWeight.U] < 2 && degrees[lowerWeight.V] < 2) {
				selected.emplace_back(lowerWeight.U, lowerWeight.V, lowerWeight.WEIGHT);
				if (!cyclic()) {
					degrees[lowerWeight.U]++;
					degrees[lowerWeight.V]++;
					lowerWeight.print();
					write("=", lowerWeight.WEIGHT);
					write(" entry\n");
					//hasZeroDegree = std::any_of(degrees, degrees + graph.AMOUNT_VERTEXES, [](unsigned int d) { return d == 0; });
				} else
					selected.pop_back();
			}

			edges.pop();
		}

		/*
		if (!hasZeroDegree) {//ainda é hamiltoniano
			while (!edges.empty()) {
				lowerWeight = edges.top();
				if (degree[lowerWeight.U] == 1)
					if (degree[lowerWeight.V] == 1)
						insertEdge(lowerWeight);
				edges.pop();
			}

			hasZeroDegree = true;//usando como variavel auxiliar
			for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
				if (degree[i] != 2)
					hasZeroDegree = false;

			if (hasZeroDegree) //se todos vertices iguais a 2;
				writeln("O grafo e hamiltoniano.");
		} else {
			writeln("O grafo nao e hamiltoniano.");
		}
		*/
	}
};