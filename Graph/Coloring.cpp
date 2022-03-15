#include "Coloring.h"

//Constructor
Coloring::Coloring(const Graph& graph) noexcept(false) : NonCopyable(), graph(graph) {
	color = new unsigned int[graph.AMOUNT_VERTEXES];
}

//Destructor
Coloring::~Coloring() {
	delete[] color;
	color = nullptr;
}

void Coloring::print(const std::string& text) const {
	PageTable table(text, PageTable::HeaderOrientation::ROW);
	table.setColumnsForPage(20);

	table.addHeader({ "Vi", "Ci" });
	table.setColumnCount(graph.AMOUNT_VERTEXES);
	for (unsigned int i = 0; i < graph.AMOUNT_VERTEXES; ++i) {
		table.setColumnMaxWidth(i, 4);
		table.updateValueAt(0, i, graph.getVertexName(i));
	}
	table.addRow(color, graph.AMOUNT_VERTEXES);

	table.print();
}

void Coloring::setValidColor(const unsigned int u) {
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

unsigned int Coloring::getHigherDegreeNotColored() {
	unsigned int vertex = graph.AMOUNT_VERTEXES;
	unsigned int higherDegreeNotColored = 0;

	for (unsigned int u = 0, count = 0; u < graph.AMOUNT_VERTEXES; ++u, count = 0) {
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

void Coloring::coloring(const bool isHeuristic) {
	memset(color, 0, sizeof(unsigned int) * graph.AMOUNT_VERTEXES);

	if (isHeuristic == false) {
		for (unsigned int u = 0; u < graph.AMOUNT_VERTEXES; ++u)
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