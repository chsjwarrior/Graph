#pragma once
/*
Parcialmente funcionando
*/
class Tarjan {
private:
	const Graph& graph;
	unsigned int* discovery;
	unsigned int* low;
	bool* onStack;
	unsigned int time;
	unsigned int setCount;
	std::stack<unsigned int> stack;

	void strongConnected(const unsigned int u) {
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
				graph.writeVertex(w);
				onStack[w] = false;
				stack.pop();
			} while (w != u);
		}
	}

public:
	Tarjan() = delete;
	Tarjan(const Graph& graph) noexcept(false) : graph(graph) {
		if (!graph.IS_DIGRAPH)
			throw std::invalid_argument("O Grafo precisa ser dirigido para o algoritmo Tarjan funcionar.");
		
		discovery = new unsigned int[graph.AMOUNT_VERTEXES];
		low = new unsigned int[graph.AMOUNT_VERTEXES];
		onStack = new bool[graph.AMOUNT_VERTEXES];
		time = NULL;
		setCount = time;
	}

	~Tarjan() {
		delete[] discovery;
		delete[] low;
		delete[] onStack;
		discovery = nullptr;
		low = nullptr;
		onStack = nullptr;
		time = NULL;
		setCount = NULL;
	}

	void tarjan() {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			discovery[u] = NIL;
			low[u] = NIL;
			onStack[u] = false;
		}

		std::cout << "Tajan:" << std::endl;
		time = 0;
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (discovery[u] == NIL)
				strongConnected(u);
	}
};