#pragma once
/*
Coloração de grafos e um caso especial de rotulagem dos vertices atraves de "cores", sujeitos a certas restrições.
Na sua forma mais simples, e uma maneira de colorir os vertices de um grafo, de modo que nao haja dois vertices adjacentes da mesma cor.
Da mesma forma, uma coloraçao de aresta atribui uma cor a cada aresta, de modo que nao haja duas arestas adjacentes da mesma cor,
e uma coloração de face de um grafo planar atribui uma cor a cada face ou região, de modo que nenhuma das duas faces que compartilham um limite tenha a mesma cor.
*/
class Coloring {
private:
	const Graph& graph;
	unsigned int* color;

	void setValidColor(const unsigned int& u) {
		unsigned int colorI = 0;
		bool isValidColor = false;

		do {
			colorI++;
			isValidColor = true;
			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); !adjacences.empty() && isValidColor; v = adjacences.erase(v))
				isValidColor = color[*v] != colorI;
		} while (!isValidColor && colorI <= graph.AMOUNT_VERTEXES);

		color[u] = colorI;
	}

	const unsigned int getHigherDegreeNotColored() {
		unsigned int vertex = graph.AMOUNT_VERTEXES;
		unsigned int higherDegreeNotColored = 0;

		for (unsigned int u = 0, count = 0; u < graph.AMOUNT_VERTEXES; u++, count = 0) {
			if (color[u] == 0) {
				if (vertex == graph.AMOUNT_VERTEXES)
					vertex = u;//first vertex not colored
				std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
				for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v))
					if (color[*v] == 0)
						count++;
				if (count > higherDegreeNotColored) {
					higherDegreeNotColored = count;
					vertex = u;
				}
			}
		}
		return vertex;
	}

	void print() const {
		std::cout << std::left << std::setw(4) << "Vi";
		std::cout << std::right;
		unsigned int i;
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			std::cout << '|' << std::setw(4);
			graph.writeVertex(i);
		}
		std::cout << std::endl << std::left << std::setw(4) << "ci";
		std::cout << std::right;
		for (i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			std::cout << '|' << std::setw(4);
			graph.writeValue(color[i]);
		}
		std::cout << std::endl;
	}

public:
	Coloring() = delete;
	Coloring(const Graph& graph) : graph(graph) {
		color = new unsigned int[graph.AMOUNT_VERTEXES];
	}

	~Coloring() {
		delete[] color;
		color = nullptr;
	}

	void coloring(const bool& isSequential) {
		memset(color, 0, sizeof(unsigned int) * graph.AMOUNT_VERTEXES);

		if (isSequential) {
			for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
				if (color[u] == 0)
					setValidColor(u);

			std::cout << "Coloracao seguencial:" << std::endl;
		} else {
			unsigned int u = getHigherDegreeNotColored();
			while (u != graph.AMOUNT_VERTEXES) {
				setValidColor(u);
				u = getHigherDegreeNotColored();
			}

			std::cout << "Coloracao heuristica:" << std::endl;
		}
		print();
	}
};