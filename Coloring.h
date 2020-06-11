#pragma once

class Coloring {
private:
	const Graph& graph;
	unsigned int* color;

	void setValidColor(const unsigned int& u) const {
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

	const unsigned int getHigherDegreeNotColored() const {
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
		write("Vi  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write('|');
		}
		write("\nci  |");
		for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; i++) {
			writeValue(color[i]);
			write('|');
		}
		write("\n");
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

	void sequentialColoring() const {
		memset(color, false, sizeof(color));

		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; u++)
			if (color[u] == 0)
				setValidColor(u);
		writeln("Coloracao seguencial:");
		print();
	}

	void heuristicColoring() {
		memset(color, false, sizeof(color));

		unsigned int u = getHigherDegreeNotColored();
		while (u != graph.AMOUNT_VERTEXES) {
			setValidColor(u);
			u = getHigherDegreeNotColored();
		}
		writeln("Coloracao heuristica:");
		print();
	}
};