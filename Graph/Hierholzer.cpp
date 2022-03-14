#include "Hierholzer.h"

//Constructor
Hierholzer::Hierholzer(const Graph& graph) noexcept(false) : graph(graph) {
	if (!graph.IS_DIGRAPH)
		throw std::invalid_argument("O Grafo precisa ser dirigido para o algoritmo Hierholzer funcionar.");
}

//Destructor
Hierholzer::~Hierholzer() {}

void Hierholzer::print(const std::string& title) const {}

const std::pair<unsigned int, std::pair<unsigned int, unsigned int>> Hierholzer::validateGraph() {
	unsigned int inDegree, outDegree;
	unsigned int amountFailVertexes = 0;
	unsigned int startOddVertex = NIL;
	unsigned int endOddVertex = startOddVertex;

	for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u) {
		inDegree = graph.getInDegreeFrom(u);
		outDegree = graph.getOutDegreeFrom(u);
		if (startOddVertex == NIL)
			if (inDegree + 1 == outDegree)
				startOddVertex = u;
		if (endOddVertex == NIL)
			if (inDegree == outDegree + 1)
				endOddVertex = u;
		if (inDegree != outDegree)
			amountFailVertexes++;
	}

	if (startOddVertex == NIL)
		startOddVertex = 0;
	if (endOddVertex == NIL)
		endOddVertex = 0;
	return std::make_pair(amountFailVertexes, std::make_pair(startOddVertex, endOddVertex));
}

void Hierholzer::hierholzer(const unsigned int source, const unsigned int sink) {
	std::stack<unsigned int> path;
	std::vector<unsigned int> circuit;

	path.push(source);
	unsigned int u, v;

	while (!path.empty()) {
		u = path.top();
		std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);

		if (!adjacences.empty()) {
			v = *adjacences.crbegin();
			graph.removeEdge(u, v);
			path.push(v);
		} else {
			circuit.push_back(path.top());
			path.pop();
		}
	}

	for (auto i = circuit.crbegin(); i != circuit.crend(); ++i) {
		graph.writeVertex(*i);
		if ((i + 1) != circuit.crend())
			std::cout << "->";
	}
}

void Hierholzer::hierholzer() {
	std::cout << "Hierholzer:" << std::endl;

	/*
	Deve haver um unico vértice no grafo que tenha (inDegree + 1 == outDegree), este é o vertice inicial do caminho euleriano
	Deve haver um unico vértice no grafo que tenha (inDegree == outDegree + 1), este é o vertice final do caminho euleriano
	Todos os outros vertices devem ter (inDegree == outDegree)
	Se alguma das condições acima falhar, nao existe caminho euleriano.
	*/

	const std::pair<unsigned int, std::pair<unsigned int, unsigned int>> pair = validateGraph();

	if (pair.first > 2) {
		std::cout << pair.first << " vertices tem grau de entrada e saida diferentes" << std::endl << "O Grafo nao e euleriano" << std::endl;
	} else {
		if (pair.first == 0)
			std::cout << "Todos os vertices tem grau par" << std::endl << "E possivel encontrar um caminho euleriano." << std::endl;
		else if (pair.first == 2)
			std::cout << "Dois vertices tem grau impar" << std::endl << "E possivel encontrar um caminho semi-euleriano." << std::endl;
		hierholzer(pair.second.first, pair.second.second);
	}
	std::cout << std::endl;
}