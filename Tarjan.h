#pragma once

/*
Parcialmente funcionando
*/

class Tarjan {
private:
	const Graph& graph;
	int* discovery;
	int* low;
	bool* onStack;
	int time;
	std::stack<int> stack;

	void strongConnected(const unsigned int& u) {
		discovery[u] = low[u] = ++time;
		stack.push(u);
		onStack[u] = true;

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
			if (discovery[*v] == NIL) {
				strongConnected(*v);
				low[*v] = std::min(low[u], low[*v]);
			} else if (onStack[*v])
				low[u] = std::min(low[u], discovery[*v]);
		}

		if (low[u] == discovery[u]) {
			int w;
			while (stack.top() != u) {
				w = stack.top();
				writeVertex(w);
				write(' ');
				onStack[w] = false;
				stack.pop();
			}
			w = stack.top();
			writeVertex(w);
			onStack[w] = false;
			stack.pop();
			write("\n");
		}
	}

public:
	Tarjan() = delete;
	Tarjan(const Graph& graph) : graph(graph) {
		discovery = new int[graph.AMOUNT_VERTEXES];
		low = new int[graph.AMOUNT_VERTEXES];
		onStack = new bool[graph.AMOUNT_VERTEXES];
		time = NULL;
	}

	~Tarjan() {
		delete[] discovery;
		delete[] low;
		delete[] onStack;
		discovery = nullptr;
		low = nullptr;
		onStack = nullptr;
		time = NULL;
	}

	void tarjan() {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			discovery[u] = NIL;
			low[u] = NIL;
			onStack[u] = false;
		}

		time = 0;
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (discovery[u] == NIL)
				strongConnected(u);
	}
};