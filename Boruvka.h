#pragma once

/*
O algoritmo de Boruvka serve para encontrar a arvore geradora mínima (minimal spanning tree) em um grafo não direcionado e ponderado.
Isto significa que ele encontra um subconjunto das arestas que forma uma arvore que inclui todos os vertices,
onde o peso total é dado pela soma dos pesos das arestas da árvore de menor valor.
Outros algoritmos conhecidos para encontrar árvores geradoras mínimas são o algoritmo de Kruskal e algoritmo de Prim.
Enquanto o algoritmo de Prim e o algorítmo de Kruskal precisam de um grafo conexo para funciona, o algoritmo de Boruvka pode ser empregado em grafos desconexos.
*/

class Boruvka {
private:
	const Graph& graph;

	// An array to store index of the cheapest edge of
	unsigned int* cheapest;
	// subset to stored index for indexing array edge[]
	std::pair<unsigned int, unsigned int>* subsets;
	//pair.first = parent;
	//pair.second = rank;

	/*
	A utility function to find set of an element i
	(uses path compression technique)
	*/
	const unsigned int find(const unsigned int& u) {
		if (subsets[u].first != u)
			subsets[u].first = find(subsets[u].first);
		return subsets[u].first;
	}

	/*
	A function that does union of two sets of x and y
	(uses union by rank)
	*/
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

public:
	Boruvka() = delete;
	Boruvka(const Graph& graph) : graph(graph) {
		cheapest = new unsigned int[graph.AMOUNT_VERTEXES];
		subsets = new std::pair<unsigned int, unsigned int>[graph.AMOUNT_VERTEXES];
	}
	~Boruvka() {
		delete cheapest;
		cheapest = nullptr;
		delete[] subsets;
		subsets = nullptr;
	}

	void boruvka() {
		if (graph.IS_DIGRAPH) {
			writeln("O Grafo precisa ser nao dirigido para o algoritmo Boruvka funcionar.");
			return;
		}

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			subsets[u].first = u;
			subsets[u].second = 0;
		}

		std::multiset<Edge> set = graph.getEdges();
		std::vector<Edge> edges(set.size());
		for (auto e = set.cbegin(); !set.empty(); e = set.erase(e))
			edges.emplace_back(e->U, e->V, e->WEIGHT);

		// Initially there are V different trees. 
		// Finally there will be one tree that will be MST 
		int numTrees = graph.AMOUNT_VERTEXES;
		int MSTweight = 0;

		// Keep combining components (or sets) until all 
		// compnentes are not combined into single MST. 
		writeln("Boruvka:");
		while (numTrees > 1) {
			memset(cheapest, NIL, sizeof(unsigned int) * graph.AMOUNT_VERTEXES);

			for (size_t i = 0; i < edges.size(); i++) {
				unsigned int set1 = find(edges[i].U);
				unsigned int set2 = find(edges[i].V);

				if (set1 != set2) {
					if (cheapest[set1] == NIL ||
						edges[cheapest[set1]].WEIGHT > edges[i].WEIGHT)
						cheapest[set1] = i;

					if (cheapest[set2] == -1 ||
						edges[cheapest[set2]].WEIGHT > edges[i].WEIGHT)
						cheapest[set2] = i;
				}
			}

			// Consider the above picked cheapest edges and add them 
			// to MST 
			for (int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
				// Check if cheapest for current set exists 
				if (cheapest[i] != -1) {
					int set1 = find(edges[cheapest[i]].U);
					int set2 = find(edges[cheapest[i]].V);

					if (set1 != set2) {
						MSTweight += edges[cheapest[i]].WEIGHT;
						edges[cheapest[i]].print();
						write("\n");
						// Do a union of set1 and set2 and decrease number 
						// of trees 
						makeUnion(set1, set2);
						numTrees--;
					}
				}
			}
		}
		write("Weight of MST is ", MSTweight, "\n");
		return;
	}
};