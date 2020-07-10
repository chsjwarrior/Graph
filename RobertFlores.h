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

	void robertFloresRecursive(const unsigned int& u) {
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
				} else if (visited[*v] == false)
					robertFloresRecursive(*v);
		}

		if (index > 0) {
			index--;
			visited[u] = false;
		}
		print();
	}

	void robertFloresIterative(unsigned int u) {
		std::stack<unsigned int> stack;

		stack.push(u);
		while (!stack.empty()) {
			u = stack.top();

			if (!visited[u]) {
				array[index++] = u;
				visited[u] = true;
				print();

				std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
				for (auto v = adjacences.crbegin(); v != adjacences.crend(); ++v)
					if (*v != u)
						if (index == graph.AMOUNT_VERTEXES && array[0] == *v) {
							print();
							writeVertex(*v);
							write(" achou");
							print();
							break;
						} else if (visited[*v] == false)
							stack.push(*v);
						adjacences.clear();

			} else {
				stack.pop();
				if (index > 0) {
					index--;
					visited[u] = false;
				}
				print();
			}
		}
	}

	void print() const {
		std::cout << std::endl;
		for (unsigned int* p = array; p != array + index; ++p) {
			writeVertex(*p);
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

	void robertFlores(const unsigned int& source, const bool& isRecursive) {
		memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
		index = 0;

		if (isRecursive) {
			write("Robert-Flores recursivo:");
			robertFloresRecursive(source);
		} else {
			write("Robert-Flores iterativo:");
			robertFloresIterative(source);
		}
		write("\n");
	}
};