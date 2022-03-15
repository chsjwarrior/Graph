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

void RobertFlores::print(const std::string& text) const {
	std::cout << text;
	for (unsigned int* p = array; p != array + index; ++p)
		std::cout << graph.getVertexName(*p) << '-';
}

void RobertFlores::robertFloresRecursive(const unsigned int u) {
	array[index++] = u;
	visited[u] = true;
	print("\n");

	std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
	for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
		if (*v != u)
			if (index == graph.AMOUNT_VERTEXES && array[0] == *v) {
				print("\n");
				std::cout << graph.getVertexName(*v);
				print(" achou\n");
				break;
			} else if (visited[*v] == false)
				robertFloresRecursive(*v);
	}

	if (index > 0) {
		--index;
		visited[u] = false;
	}
	print("\n");
}

void RobertFlores::robertFloresIterative(unsigned int u) {
	std::stack<unsigned int> stack;

	stack.push(u);
	while (!stack.empty()) {
		u = stack.top();

		if (!visited[u]) {
			array[index++] = u;
			visited[u] = true;
			print("\n");

			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.crbegin(); v != adjacences.crend(); ++v)
				if (*v != u)
					if (index == graph.AMOUNT_VERTEXES && array[0] == *v) {
						print("\n");
						std::cout << graph.getVertexName(*v);
						print(" achou\n");
						break;
					} else if (visited[*v] == false)
						stack.push(*v);
					adjacences.clear();

		} else {
			stack.pop();
			if (index > 0) {
				--index;
				visited[u] = false;
			}
			print("\n");
		}
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