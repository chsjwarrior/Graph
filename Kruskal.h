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

	std::multiset<Edge, LessWeight> edges;
	std::pair<unsigned int, unsigned int>* subsets;
	//pair.first = parent;
	//pair.second = rank;

	const unsigned int find(const unsigned int& u) {
		if (subsets[u].first != u)
			subsets[u].first = find(subsets[u].first);
		return subsets[u].first;
	}

	void makeUnion(const unsigned int& u, const unsigned int& v) {
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

	void makeSet() {
		std::multiset<Edge> set = graph.getEdges();
		for (auto e = set.cbegin(); !set.empty(); e = set.erase(e))
			edges.emplace(e->U, e->V, e->WEIGHT);
	}

public:
	Kruskal() = delete;
	Kruskal(const Graph& graph) : graph(graph) {
		subsets = new std::pair<unsigned int, unsigned int>[graph.AMOUNT_VERTEXES];
	}

	~Kruskal() {
		delete[] subsets;
		subsets = nullptr;
	}

	void kruskal() {
		if (graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser nao dirigido para o algoritmo Kruskal funcionar.");
			return;
		}

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			subsets[u].first = u;
			subsets[u].second = 0;
		}

		makeSet();

		writeln("Kruskal:");
		while (!edges.empty()) {
			unsigned int x = find(edges.cbegin()->U);
			unsigned int y = find(edges.cbegin()->V);

			if (x != y) {
				makeUnion(edges.cbegin()->U, edges.cbegin()->V);
				edges.cbegin()->print();
				write("\n");
			}

			edges.erase(edges.cbegin());
		}
	}
};