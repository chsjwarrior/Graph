#pragma once
/*
O algoritmo de Kruskal é um algoritmo em teoria dos grafos que busca uma árvore geradora mínima (minimal spanning tree) em um grafo conexo ponderado.
Isto significa que ele encontra um subconjunto das arestas que forma uma arvore que inclui todos os vertices,
onde o peso total é dado pela soma dos pesos das arestas da árvore de menor valor.
Se o grafo não for conexo, então ele encontra uma floresta geradora mínima (uma árvore geradora mínima para cada componente conexo do grafo).
O algoritmo de Kruskal é um exemplo de um algoritmo guloso (também conhecido como ganancioso ou greedy).
*/
class Kruskal {
private:
	const Graph& graph;

	struct LessWeight {
		const bool operator()(const Edge& lhs, const Edge& rhs) const {
			return lhs.WEIGHT < rhs.WEIGHT;
		}
	};

	std::pair<unsigned int, unsigned int>* subsets;
	//pair.first = parent;
	//pair.second = rank;

	const unsigned int find(const unsigned int u) {
		if (subsets[u].first != u)
			subsets[u].first = find(subsets[u].first);
		return subsets[u].first;
	}

	void makeUnion(const unsigned int u, const unsigned int v) {
		const unsigned int uRoot = find(u);
		const unsigned int vRoot = find(v);

		if (subsets[uRoot].second < subsets[vRoot].second)
			subsets[uRoot].first = vRoot;
		else if (subsets[uRoot].second > subsets[vRoot].second)
			subsets[vRoot].first = uRoot;
		else {
			subsets[vRoot].first = uRoot;
			subsets[uRoot].second++;
		}
	}

	inline void makeSet(const unsigned int v) {
		subsets[v].first = v;
		subsets[v].second = 0;
	}

	std::multiset<Edge, LessWeight> getEdgesLessWeight() {
		std::multiset<Edge> set = graph.getEdges();
		std::multiset<Edge, LessWeight> edges(set.cbegin(), set.cend());
		return edges;
	}

public:
	Kruskal() = delete;
	Kruskal(const Graph& graph) : graph(graph) {
		if (graph.IS_DIGRAPH)
			throw std::exception("O Grafo precisa ser nao dirigido para o algoritmo Kruskal funcionar.");

		subsets = new std::pair<unsigned int, unsigned int>[graph.AMOUNT_VERTEXES];
	}

	~Kruskal() {
		delete[] subsets;
		subsets = nullptr;
	}

	void kruskal() {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			makeSet(u);

		std::multiset<Edge, LessWeight> edges(getEdgesLessWeight());

		PageTable table("Kruskal", PageTable::HeaderOrientation::COLUMN);
		table.addHeader({"Edge", "C(e)", ""});

		while (!edges.empty()) {
			unsigned int u = find(edges.cbegin()->U);
			unsigned int v = find(edges.cbegin()->V);

			if (u != v)
				makeUnion(edges.cbegin()->U, edges.cbegin()->V);

			table.setRowCount(table.getRowCount() + 1);
			table.updateValueAt(table.getRowCount() - 1, 0, graph.getEdgeName(*edges.cbegin()));
			table.updateValueAt(table.getRowCount() - 1, 1, edges.cbegin()->WEIGHT);
			table.updateValueAt(table.getRowCount() - 1, 2, u != v);

			edges.erase(edges.cbegin());
		}

		table.print();
	}
};