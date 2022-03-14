#include "Kosaraju.h"

//Constructor
Kosaraju::Kosaraju(Graph& graph) noexcept(false) : graph(graph) {
	if (!graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser dirigido para o algoritmo Kosaraju funcionar.");

	visited = new bool[graph.AMOUNT_VERTEXES];
}

//Destructor
Kosaraju::~Kosaraju() {
	delete[] visited;
	visited = nullptr;
}

void Kosaraju::print(const std::string& title) const {}

void Kosaraju::fillOrder(const unsigned int u) {
	visited[u] = true;

	std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
	for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
		if (visited[*v] == false)
			fillOrder(*v);

	stack.push(u);
}

void Kosaraju::dfs(const unsigned int u) {
	graph.writeVertex(u);
	std::cout << ' ';
	visited[u] = true;

	std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
	for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
		if (visited[*v] == false)
			dfs(*v);
}

void Kosaraju::kosaraju() {
	memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);

	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u)
		if (visited[u] == false)
			fillOrder(u);

	graph.transpose();

	memset(visited, false, sizeof(bool) * graph.AMOUNT_VERTEXES);

	std::cout << "Kosaraju:" << std::endl;
	unsigned int c = 1;
	while (!stack.empty()) {
		int u = stack.top();
		stack.pop();

		if (!visited[u]) {
			std::cout << "Conjunto " << c++ << ": {";
			dfs(u);
			std::cout << '}' << std::endl;
		}
	}
}