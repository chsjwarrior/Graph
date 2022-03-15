#include "Tarjan.h"

//Constructor
Tarjan::Tarjan(const Graph& graph) noexcept(false) : NonCopyable(), graph(graph) {
	if (!graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser dirigido para o algoritmo Tarjan funcionar.");

	discovery = new unsigned int[graph.AMOUNT_VERTEXES];
	low = new unsigned int[graph.AMOUNT_VERTEXES];
	onStack = new bool[graph.AMOUNT_VERTEXES];
	time = NULL;
	setCount = time;
}

//Destructor
Tarjan::~Tarjan() {
	delete[] discovery;
	delete[] low;
	delete[] onStack;
	discovery = nullptr;
	low = nullptr;
	onStack = nullptr;
	time = NULL;
	setCount = NULL;
}

void Tarjan::strongConnected(const unsigned int u) {
	discovery[u] = low[u] = ++time;
	stack.push(u);
	onStack[u] = true;

	std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
	for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
		if (discovery[*v] == NIL) {
			strongConnected(*v);
			low[u] = std::min(low[u], low[*v]);
		} else if (onStack[*v])
			low[u] = std::min(low[u], discovery[*v]);
	}

	if (low[u] == discovery[u]) {
		int w;
		do {
			w = stack.top();
			print(graph.getVertexName(w));
			onStack[w] = false;
			stack.pop();
		} while (w != u);
	}
}

void Tarjan::tarjan() {
	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		discovery[u] = NIL;
		low[u] = NIL;
		onStack[u] = false;
	}

	print("Tajan:\n");
	time = 0;
	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u)
		if (discovery[u] == NIL)
			strongConnected(u);
}