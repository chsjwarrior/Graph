#pragma once
#include <queue>
/*
O algoritmo da busca em largura (Breadth-First Search - BFS) e utilizado para realizar uma busca em estrutura de dados do tipo arvore.
O algoritmo começa em um vertice raiz e explora todos os vertices vizinhos antes de avaçar e explorar os proximos vertices vizinhos inexplorados.
O algoritmo da busca em largura calcula pode calcular a distância (menor número de arestas)
desde o vértice raiz ate todos os vértices acessiveis.
*/
class BreadthFirstSearch {
private:
	const Graph& graph;
	unsigned int* discovery;
	unsigned int* predecessor;
	bool* visited;

	void bfsRecursive(std::queue<unsigned int>& queue) {
		if (queue.empty())
			return;

		unsigned int u = queue.front();
		queue.pop();

		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
			if (visited[*v] == false) {
				queue.push(*v);
				discovery[*v] = discovery[u] + 1;
				predecessor[*v] = u;
				visited[*v] = true;
			}

		bfsRecursive(queue);
	}

	void bfsIterative(std::queue<unsigned int>& queue) {
		unsigned int u;
		while (!queue.empty()) {
			u = queue.front();
			queue.pop();

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
				if (visited[*v] == false) {
					queue.push(*v);
					discovery[*v] = discovery[u] + 1;
					predecessor[*v] = u;
					visited[*v] = true;
				}
		}
	}

	void print(const std::string& title) const {
		PageTable table(title, PageTable::HeaderOrientation::ROW);
		table.setAutoResizeColumns(false);
		table.setColumnsForPage(20);
		table.addHeader("Vi");
		table.addHeader("Di");
		table.addHeader("Pi");

		table.addRow(graph.AMOUNT_VERTEXES);
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			table.setValueAt(0, i, graph.getVertexName(i));
			table.setColumnWidth(i, 4);
		}

		table.addRow(discovery, graph.AMOUNT_VERTEXES);
		table.addRow(graph.AMOUNT_VERTEXES);
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++)
			table.setValueAt(2, i, graph.getVertexName(predecessor[i]));

		table.print();
	}

public:
	BreadthFirstSearch() = delete;
	BreadthFirstSearch(const Graph& graph) : graph(graph) {
		discovery = new unsigned int[graph.AMOUNT_VERTEXES];
		predecessor = new unsigned int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
	}

	~BreadthFirstSearch() {
		delete[] discovery;
		delete[] predecessor;
		delete[] visited;
		discovery = nullptr;
		predecessor = nullptr;
		visited = nullptr;
	}

	void bfs(const unsigned int& source, const bool& isRecursive) {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++) {
			discovery[u] = NIL;
			predecessor[u] = NIL;
			visited[u] = false;
		}

		std::queue<unsigned int> queue;
		discovery[source] = 0;
		visited[source] = true;
		queue.push(source);

		if (isRecursive) {
			bfsRecursive(queue);
			print("Busca em largura recursiva:");
		} else {
			bfsIterative(queue);
			print("Busca em largura iterativa:");
		}
	}
};