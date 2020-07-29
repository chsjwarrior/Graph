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

	void print(const std::string& title) const {
		PageTable table(title, PageTable::HeaderOrientation::ROW);
		table.setAutoResizeColumns(false);
		table.setColumnsOfPage(20);
		table.addHeader("Vi");
		table.addHeader("Ci");

		table.addRow(graph.AMOUNT_VERTEXES);
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			table.setValueAt(0, i, graph.getVertexName(i));
			table.setColumnWidth(i, 4);
		}

		table.addRow(color, graph.AMOUNT_VERTEXES);
		table.print();
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

	void coloring(const bool& isHeuristic) {
		memset(color, 0, sizeof(unsigned int) * graph.AMOUNT_VERTEXES);

		if (isHeuristic == false) {
			for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
				if (color[u] == 0)
					setValidColor(u);

			print("Coloracao seguencial:");
		} else {
			unsigned int u = getHigherDegreeNotColored();
			while (u != graph.AMOUNT_VERTEXES) {
				setValidColor(u);
				u = getHigherDegreeNotColored();
			}

			print("Coloracao heuristica:");
		}
	}
};