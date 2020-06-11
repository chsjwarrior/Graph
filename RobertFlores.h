#pragma once

/*
O objetivo do algoritmo Robert e Flores é identificar um ciclo Hamiltoniano,
e tem como finalidade passar por cada vertices apenas uma vez e voltar a origem.
funcionando.
*/

class RobertFlores {
private:
	const Graph& graph;
	unsigned int* array;
	bool* visited;
	unsigned int index;

	void robertFloresR(const unsigned int& u) {
		array[index++] = u;
		visited[u] = true;
		print();

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
			if (*v != u)
				if (index == graph.AMOUNT_VERTEXES && array[0] == *v) {
					print();
					writeVertex(*v);
					write(" achou");
					print();
					break;
				} else if (!visited[*v])
					robertFloresR(*v);
		}

		if (index > 0) {
			index--;
			visited[u] = false;
		}
		print();
	}

	void print() const {
		write("\n");
		for (unsigned int i = 0; i < index; i++) {
			writeVertex(array[i]);
			write('-');
		}
	}

public:
	RobertFlores() = delete;
	RobertFlores(const Graph& graph) : graph(graph) {
		array = new unsigned int[graph.AMOUNT_VERTEXES];
		visited = new bool[graph.AMOUNT_VERTEXES];
		index = NULL;
	}

	~RobertFlores() {
		delete[] array;
		delete[] visited;
		array = nullptr;
		visited = nullptr;
		index = NULL;
	}

	void robertFlores(const unsigned int& origin) {
		memset(visited, false, sizeof(visited));
		index = 0;

		write("Robert-Flores:");
		robertFloresR(origin);
		write("\n");
	}
};