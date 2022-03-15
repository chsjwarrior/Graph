#include "CheapestLink.h"

//Constructor
CheapestLink::CheapestLink(const Graph& graph) noexcept(false) : NonCopyable(), graph(graph) {
	if (graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser nao dirigido para o algoritmo de da ligacao mais economica funcionar.");

	std::multiset<Edge> set = graph.getEdges();
	for (auto e = set.cbegin(); !set.empty(); e = set.erase(e))
		edges.emplace(e->U, e->V, e->WEIGHT);
	degrees = new unsigned int[graph.AMOUNT_VERTEXES];
	visited = new bool[graph.AMOUNT_VERTEXES];
	//selected.reserve(edges.size());
}

//Destructor
CheapestLink::~CheapestLink() {
	delete[] degrees;
	delete[] visited;
	degrees = nullptr;
	visited = nullptr;
	selected.clear();
}

bool CheapestLink::cyclic_recursive(const unsigned int vertex, const  unsigned int predecessor) {
	bool cycle_found = false;
	visited[vertex] = true;
	for (auto e = selected.cbegin(); e != selected.cend() && !cycle_found; ++e) {
		if (e->U == vertex || e->V == vertex) {
			const unsigned int neighbour = e->U == vertex ? e->V : e->U;
			if (visited[neighbour] == false) {
				cycle_found = cyclic_recursive(neighbour, vertex);
			} else if (neighbour != predecessor) {
				cycle_found = true;
			}
		}
	}
	return cycle_found;
}

bool CheapestLink::cyclic() {
	memset(visited, false, sizeof(visited));
	return cyclic_recursive(0, 0);
}

void CheapestLink::cheapestLink() {
	print("Ligacao mais economica:\n");

	memset(degrees, 0, sizeof(unsigned int) * graph.AMOUNT_VERTEXES);

	selected.emplace_back(edges.cbegin()->U, edges.cbegin()->V, edges.cbegin()->WEIGHT);
	degrees[edges.cbegin()->U]++;
	degrees[edges.cbegin()->V]++;
	print(graph.getEdgeName(*edges.cbegin()));
	//graph.writeEdge(*edges.cbegin());
	std::cout << '=' << edges.cbegin()->WEIGHT;
	print(" entry\n");
	edges.erase(edges.cbegin());

	//bool hasZeroDegree = true;
	while (!edges.empty()) {

		if (degrees[edges.cbegin()->U] < 2 && degrees[edges.cbegin()->V] < 2) {
			selected.emplace_back(edges.cbegin()->U, edges.cbegin()->V, edges.cbegin()->WEIGHT);
			if (cyclic() == false) {
				degrees[edges.cbegin()->U]++;
				degrees[edges.cbegin()->V]++;
				print(graph.getEdgeName(*edges.cbegin()));
				//graph.writeEdge(*edges.cbegin());
				std::cout << '=' << edges.cbegin()->WEIGHT;
				print(" entry\n");
				//hasZeroDegree = std::any_of(degrees, degrees + graph.AMOUNT_VERTEXES, [](unsigned int d) { return d == 0; });
			} else
				selected.pop_back();
		}

		edges.erase(edges.cbegin());
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