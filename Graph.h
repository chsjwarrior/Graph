#pragma once
#include <set>

#ifndef NIL
#define NIL UINT_MAX
#endif //!NIL

#ifndef INF
#define INF 10000
#endif //!INF

struct Edge {
	const unsigned int U, V;
	const int WEIGHT;

	Edge() = delete;

	explicit Edge(const unsigned int u, const unsigned int v, const int w) : U(u), V(v), WEIGHT(w) {
		//std::cout << "constructor {" << U << ',' << V << '=' << WEIGHT << '}' << std::endl;
	}
	explicit Edge(const Edge& other) : U(other.U), V(other.V), WEIGHT(other.WEIGHT) {
		//std::cout << "copy constructor {" << U << ',' << V << '=' << WEIGHT << '}' << std::endl;
	}
	~Edge() {
		//std::cout << "destructor {" << U << ',' << V << '=' << WEIGHT << '}' << std::endl;
	}

	const bool operator<(const Edge& other) const {
		return U < other.U ||
			U == other.U && V < other.V ||
			U == other.U && V == other.V &&
			WEIGHT < other.WEIGHT;

		/*general pattern to compare is:
		if (U < other.U) return true;
		if (other.U < U) return false;
		if (V < other.V) return true;
		if (other.V < V) return false;
		if (WEIGHT < other.WEIGHT) return true;
		if (other.WEIGHT < WEIGHT) return false;
		return false;
		*/
	}

	const bool operator>(const Edge& other) const {
		return other < *this;
	}

	Edge& operator=(const Edge&) = delete;
	/*
	const Edge& operator=(const Edge& other) {
		//write("copy Assigment {", U, ",", V, "=", WEIGHT, "} & {", other.U, ",", other.V, "=", other.WEIGHT, "}\n");
		if (this != &other) {
			(unsigned int&) U = other.U;
			(unsigned int&) V = other.V;
			(int&) WEIGHT = other.WEIGHT;
		}
		return *this;
	}
	*/
};

class Graph {
private:
	mutable std::multiset<unsigned int> adjacences;
	std::multiset<Edge> edges;
	/*
	O conjunto de arestas do grafo armazena apenas as aresta u->v de um grafo não dirigido.
	Significa que as arestas v->u são encontradas pela conta-parte u->v.
	*/

public:
	const unsigned int AMOUNT_VERTEXES;
	const bool IS_DIGRAPH;

	Graph() = delete;

	explicit Graph(const unsigned int& amountVertexes, const bool& isDigraph) noexcept(false) :
		AMOUNT_VERTEXES(amountVertexes), IS_DIGRAPH(isDigraph) {
		if (amountVertexes == 0)
			throw std::length_error("numero de vertices deve ser maior que zero");
		if (amountVertexes == NIL)
			throw std::length_error("numero de vertices deve ser menor que " + NIL);
	}

	explicit Graph(const Graph& other) : AMOUNT_VERTEXES(other.AMOUNT_VERTEXES), IS_DIGRAPH(other.IS_DIGRAPH) {
		edges = other.getEdges();
	}

	~Graph() {
		adjacences.clear();
		edges.clear();
	}

	const Graph& operator=(const Graph& other) {
		if (this != &other) {
			(unsigned int&)AMOUNT_VERTEXES = other.AMOUNT_VERTEXES;
			(bool&)IS_DIGRAPH = other.IS_DIGRAPH;
			edges.clear();
			edges = other.edges;
		}
		return *this;
	}

	const bool isValidVertex(const unsigned int& v) {
		return v < AMOUNT_VERTEXES;
	}

	const bool isValidWeight(const int& w) {
		return w > -INF && w < INF;
	}

	void insertEdge(const unsigned int& u, const unsigned int& v, const int& weight = 1) noexcept(false) {
		if (u >= AMOUNT_VERTEXES)
			throw std::range_error("vertice u deve ser menor que " + AMOUNT_VERTEXES);
		if (v >= AMOUNT_VERTEXES)
			throw std::range_error("vertice v deve ser menor que " + AMOUNT_VERTEXES);
		if (weight <= -INF)
			throw std::range_error("o custo de u e v deve ser maior que " + -INF);
		if (weight >= INF)
			throw std::range_error("o custo de u e v deve ser menor que " + -INF);
		edges.emplace(u, v, weight);
	}

	void removeEdge(const unsigned int& u, const unsigned int& v) noexcept(false) {
		if (u >= AMOUNT_VERTEXES)
			throw std::range_error("vertice u deve ser menor que " + AMOUNT_VERTEXES);
		if (v >= AMOUNT_VERTEXES)
			throw std::range_error("vertice v deve ser menor que " + AMOUNT_VERTEXES);

		auto edge = edges.cend();
		for (auto e = edges.cbegin(); e != edges.cend() && edge == edges.cend(); e++)
			if (e->U == u && e->V == u || !IS_DIGRAPH && e->V == u && e->U == v)
				edge = e;
		/*
		auto edge = edges.find(Edge(u, v, 1));
		if (edge == edges.cend() && IS_DIGRAPH == false)
			edge = edges.find(Edge(v, u, 1));
			*/

		if (edge != edges.cend())
			edges.erase(edge);
	}

	const int getWeigthFrom(const unsigned int& u, const unsigned int& v) const noexcept(false) {
		if (u >= AMOUNT_VERTEXES)
			throw std::range_error("vertice u deve ser menor que " + AMOUNT_VERTEXES);
		if (v >= AMOUNT_VERTEXES)
			throw std::range_error("vertice v deve ser menor que " + AMOUNT_VERTEXES);

		auto edge = edges.cend();
		for (auto e = edges.cbegin(); e != edges.cend() && edge == edges.cend(); e++)
			if (e->U == u && e->V == v || !IS_DIGRAPH && e->V == u && e->U == v)
				edge = e;

		if (edge != edges.cend())
			return edge->WEIGHT;
		else if (u == v)
			return 0;
		return INF;
	}

	const unsigned int getInDegreeFrom(const unsigned int& v) const noexcept(false) {
		if (v >= AMOUNT_VERTEXES)
			throw std::range_error("vertice deve ser menor que " + AMOUNT_VERTEXES);

		if (IS_DIGRAPH == false)
			return getOutDegreeFrom(v);

		return std::count_if(edges.cbegin(), edges.cend(), [&v](const Edge& e) {return e.V == v; });
	}

	//esse método tambem é usuado para grafos não dirigidos
	const unsigned int getOutDegreeFrom(const unsigned int& v) const noexcept(false) {
		if (v >= AMOUNT_VERTEXES)
			throw std::range_error("vertice deve ser menor que " + AMOUNT_VERTEXES);

		return std::count_if(edges.cbegin(), edges.cend(), [&IS_DIGRAPH = IS_DIGRAPH, &v](const Edge& e) {return e.U == v || !IS_DIGRAPH && e.V == v; });
	}

	std::multiset<unsigned int>& getAdjacencesFrom(const unsigned int& v) const noexcept(false) {
		if (v >= AMOUNT_VERTEXES)
			throw std::range_error("vertice deve ser menor que " + AMOUNT_VERTEXES);

		if (!adjacences.empty())
			adjacences.clear();
		for (const Edge& e : edges)
			if (e.U == v)
				adjacences.insert(e.V);
			else if (!IS_DIGRAPH && e.V == v)
				adjacences.insert(e.U);
		return adjacences;
	}

	std::multiset<Edge> getEdges() const {
		return edges;
	}

	const size_t getAmountEdges() const {
		return edges.size();
	}

	void printAdjacencematrix() const {
		std::cout << "Matriz de adjacencia:" << std::endl;
		std::cout << std::left << std::setw(4) << "Vi";
		std::cout << std::right;
		for (unsigned int i = 0; i < AMOUNT_VERTEXES; i++) {
			std::cout << '|' << std::setw(4);
			writeVertex(i);
		}
		std::cout << std::endl;
		size_t count;
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			std::cout << std::left << std::setw(4);
			writeVertex(u);
			std::cout << std::right;
			getAdjacencesFrom(u);
			for (unsigned int v = 0; v < AMOUNT_VERTEXES; v++) {
				count = std::count(adjacences.begin(), adjacences.end(), v);
				std::cout << '|' << std::setw(4) << count;
			}
			std::cout << std::endl;
		}
	}

	void printIncidenceMatrix() const {
		std::cout << "Matriz de incidencia:" << std::endl;
		std::cout << std::left << std::setw(4) << "V\\E";
		std::cout << std::right;
		for (unsigned int i = 0; i < edges.size(); i++) {
			std::cout << '|' << std::setw(4);
			writeEdge(i);
		}
		std::cout << std::endl;
		int value;
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			std::cout << std::left << std::setw(4);
			writeVertex(u);
			std::cout << std::right;
			for (auto e = edges.cbegin(); e != edges.cend(); e++) {
				value = 0;
				if (IS_DIGRAPH && e->U == u)
					value = -1;
				else if (e->U == u || e->V == u)
					value = 1;
				std::cout << '|' << std::setw(4);
				writeValue(value);
			}
			std::cout << std::endl;
		}
	}

	void printAdjacenceList() const {
		std::cout << "Lista de adjacencia:" << std::endl;
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			std::cout << '[' << getVertexName(u) << ']';
			getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); v != adjacences.cend(); v = adjacences.erase(v))
				std::cout << "->[" << getVertexName(*v) << ']';
			std::cout << std::endl;
		}
	}

	void printIncidenceList() const {
		std::cout << "Lista de incidencia:" << std::endl;
		for (const Edge& e : edges) {
			std::cout << '[';
			writeVertex(e.U);
			std::cout << ',';
			writeVertex(e.V);
			std::cout << "]->";
		}
		std::cout << std::endl;
	}

	void printCostMatrix() const {
		std::cout << "Matriz de custo:" << std::endl;
		std::cout << std::left << std::setw(4) << "Vi";
		std::cout << std::right;
		unsigned int i;
		for (i = 0; i < AMOUNT_VERTEXES; i++) {
			std::cout << '|' << std::setw(4);
			writeVertex(i);
		}
		std::cout << std::endl;
		for (i = 0; i < AMOUNT_VERTEXES; i++) {
			std::cout << std::left << std::setw(4);
			writeVertex(i);
			std::cout << std::right;
			for (unsigned int j = 0; j < AMOUNT_VERTEXES; j++) {
				std::cout << '|' << std::setw(4);
				writeValue(getWeigthFrom(i, j));
			}
			std::cout << std::endl;
		}
	}

	void printGraphInfo() const {
		std::cout << "Total de vertices: " << AMOUNT_VERTEXES << std::endl;
		std::cout << "Total de arestas: " << edges.size() << std::endl;
		std::cout << "Grafo ";
		if (IS_DIGRAPH == false)
			std::cout << " nao ";
		std::cout << "dirigido e ";
		if (std::all_of(edges.cbegin(), edges.cend(), [](const Edge& e) {return e.WEIGHT == 1; }))
			std::cout << "nao ";
		std::cout << "valorado" << std::endl;

		PageTable table("Graus dos vertices:", PageTable::HeaderOrientation::ROW);
		table.setColumnsForPage(20);

		table.addHeader("Vi");
		table.setColumnCount(AMOUNT_VERTEXES);
		size_t rowsCount = 1;
		if (IS_DIGRAPH) {
			rowsCount++;
			table.addHeader("In");
		}		
		table.addHeader("Out");

		for (unsigned int i = 0; i < AMOUNT_VERTEXES; i++) {
			table.setColumnMaxWidth(i, 4);
			table.updateValueAt(0, i, getVertexName(i));
			if (IS_DIGRAPH)
				table.updateValueAt(1, i, getInDegreeFrom(i));
			table.updateValueAt(rowsCount, i, getOutDegreeFrom(i));
		}
		table.print();
	}

	void printVerticesToSelect() const {
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			std::cout << u + 1 << "= [";
			writeVertex(u);
			std::cout << "] ";
			if (u + 1 % 10 == 0)
				std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	const std::string getVertexName(const unsigned int vertex) const {
		if (vertex != NIL)
			return "V" + std::to_string(vertex + 1);
		else
			return "nil";
	}

	const std::string getEdgeName(const Edge& edge) const {
		return "{" + getVertexName(edge.U) + "," + getVertexName(edge.V) + "}";
	}

	void writeVertex(const unsigned int& vertex) const {
		std::cout << getVertexName(vertex);
	}

	void writeEdge(const Edge& edge) const {
		std::cout << getEdgeName(edge);
	}

	void writeEdge(const unsigned int& edge) const {
		if (edge != UINT_MAX)
			std::cout << "E" + std::to_string(edge + 1);
		else
			std::cout << "nil";
	}

	void writeValue(const int& value) const {
		if (value > -10000 && value < 10000)
			std::cout << value;
		else
			std::cout << "inf";
	}
};