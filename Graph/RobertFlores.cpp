#include "RobertFlores.h"

//Constructor
RobertFlores::RobertFlores(const Graph& graph) noexcept(false) : graph(graph) {
	array = new unsigned int[graph.AMOUNT_VERTEXES];
	visited = new bool[graph.AMOUNT_VERTEXES];
	index = NULL;
}

//Destructor
RobertFlores::~RobertFlores() {
	delete[] array;
	delete[] visited;
	array = nullptr;
	visited = nullptr;
	index = NULL;
}

void RobertFlores::robertFloresRecursive(const unsigned int u) {
	array[index++] = u;
	visited[u] = true;
	print();

	std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
	for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
		if (*v != u)
			if (index == graph.AMOUNT_VERTEXES && array[0] == *v) {
				print();
				graph.writeVertex(*v);
				std::cout << " achou";
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

void RobertFlores::robertFloresIterative(unsigned int u) {
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
						graph.writeVertex(*v);
						std::cout << " achou";
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

void RobertFlores::print() const {
	std::cout << std::endl;
	for (unsigned int* p = array; p != array + index; ++p) {
		graph.writeVertex(*p);
		std::cout << '-';
	}
}

void RobertFlores::robertFlores(const unsigned int source, const bool isRecursive) {
	memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);
	index = 0;

	if (isRecursive) {
		std::cout << "Robert-Flores recursivo:" << std::endl;
		robertFloresRecursive(source);
	} else {
		std::cout << "Robert-Flores iterativo:" << std::endl;
		robertFloresIterative(source);
	}
	std::cout << std::endl;
}