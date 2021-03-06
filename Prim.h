#pragma once
/*
O algoritmo de Prim ? empregado para encontrar uma arvore geradora minima (minimal spanning tree) num grafo conexo, valorado e n?o direcionado.
Isto significa que ele encontra um subgrafo que forma uma arvore que inclui todos os vertices,
onde o peso total ? dado pela soma dos pesos das arestas da ?rvore de menor valor.
*/
class Prim {
private:
	const Graph& graph;
	int* key;
	unsigned int* predecessor;
	bool* visited;

	const unsigned int extractMin(std::list<unsigned int>& queue) {
		int lowerDistance = INF;
		unsigned int lowerVertex = NIL;
		for (auto u = queue.cbegin(); u != queue.cend(); ++u)
			if (key[*u] < lowerDistance) {
				lowerDistance = key[*u];
				lowerVertex = *u;
			}
		queue.remove(lowerVertex);
		return lowerVertex;
	}

	inline void relax(const unsigned int u, const unsigned int v, const int w) {
		if (graph.getWeigthFrom(u, v) < key[v]) {
			predecessor[v] = u;
			key[v] = w;
		}
	}

	void print() const {
		PageTable table("Prim:", PageTable::HeaderOrientation::ROW);
		table.setColumnsForPage(20);

		table.addHeader({"Vi", "Ki", "Pi"});
		table.setColumnCount(graph.AMOUNT_VERTEXES);		
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			table.setColumnMaxWidth(i, 4);
			table.updateValueAt(0, i, graph.getVertexName(i));			
		}
		table.addRow(key, graph.AMOUNT_VERTEXES);		
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
			table.updateValueAt(2, i, graph.getVertexName(predecessor[i]));

		table.print();
	}

public:
	Prim() = delete;
	Prim(const Graph& graph) noexcept(false) : graph(graph) {
		if (graph.IS_DIGRAPH)
			throw std::invalid_argument("O Grafo precisa ser nao dirigido para o algoritmo Prim funcionar.");
		
		key = new int[graph.AMOUNT_VERTEXES];
		predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~Prim() {
		delete[] key;
		delete[] predecessor;
		delete[] visited;
		key = nullptr;
		predecessor = nullptr;
		visited = nullptr;
	}

	void prim(const unsigned int source) {
		std::list<unsigned int> queue;
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			key[i] = INF;
			predecessor[i] = NIL;
			visited[i] = false;
			queue.push_back(i);
		}
		key[source] = 0;

		while (!queue.empty()) {
			unsigned int u = extractMin(queue);
			visited[u] = true;

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (visited[*v] == false)
					relax(u, *v, graph.getWeigthFrom(u, *v));
		}
		print();
	}
};