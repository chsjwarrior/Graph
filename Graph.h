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
		//write("constructor {", U, ",", V, "=", WEIGHT, "}\n");
	}
	explicit Edge(const Edge& other) : U(other.U), V(other.V), WEIGHT(other.WEIGHT) {
		//write("copy constructor {", U, ",", V, "=", WEIGHT, "}\n");
	}
	~Edge() {
		//write("destructor {", U, ",", V, "=", WEIGHT, "}\n");
	}

	const bool operator>(const Edge& other) const {
		if (U > other.U) return true;
		if (other.U > U) return false;
		if (V > other.V) return true;
		if (other.V > V) return false;
		if (WEIGHT > other.WEIGHT) return true;
		if (other.WEIGHT > WEIGHT) return false;
		return false;
	}

	const bool operator<(const Edge& other) const {
		if (U < other.U) return true;
		if (other.U < U) return false;
		if (V < other.V) return true;
		if (other.V < V) return false;
		if (WEIGHT < other.WEIGHT) return true;
		if (other.WEIGHT < WEIGHT) return false;
		return false;
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
	explicit Graph(const unsigned int& amountVertices, const bool& isDigraph) :
		AMOUNT_VERTEXES(amountVertices), IS_DIGRAPH(isDigraph) {
		if (amountVertices == 0)
			throw std::exception("numero de vertices deve ser maior que zero.");
		if (amountVertices == NIL)
			throw std::exception("numero de vertices deve ser menor que " + NIL);
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
			(unsigned int&) AMOUNT_VERTEXES = other.AMOUNT_VERTEXES;
			(bool&) IS_DIGRAPH = other.IS_DIGRAPH;
			edges.clear();
			edges = other.edges;
		}
		return *this;
	}

	const bool isValidVertex(const unsigned int& v) const {
		return v < AMOUNT_VERTEXES;
	}

	const bool isValidWeight(const int& w) const {
		return w > -INF && w < INF;
	}

	void insertEdge(const unsigned int& u, const unsigned int& v, const int& weight = 1) {
		edges.emplace(u, v, weight);
	}

	void removeEdge(const unsigned int& u, const unsigned int& v) {
		auto edge = edges.cend();
		for (auto e = edges.cbegin(); e != edges.cend(); ++e)
			if (e->U == u && e->V == v || !IS_DIGRAPH && (e->U == v && e->V == u))
				edge = e;
		if (edge != edges.cend())
			edges.erase(edge);
	}

	const int getWeigthFrom(const unsigned int& u, const unsigned int& v) const {
		auto edge = edges.cend();
		for (auto e = edges.cbegin(); e != edges.cend(); ++e)
			if (e->U == u && e->V == v || !IS_DIGRAPH && (e->U == v && e->V == u))
				edge = e;

		if (edge != edges.cend())
			return edge->WEIGHT;
		else if (u == v)
			return 0;
		return INF;
	}

	const unsigned int getInDegreeFrom(const unsigned int& u) const {
		if (!IS_DIGRAPH)
			return getOutDegreeFrom(u);

		unsigned int degree = 0;
		for (auto e = edges.cbegin(); e != edges.cend(); ++e)
			if (e->V == u)
				degree++;
		return degree;
	}

	//esse método tambem é usuado para grafos não dirigidos
	const unsigned int getOutDegreeFrom(const unsigned int& u) const {
		unsigned int degree = 0;
		for (auto e = edges.cbegin(); e != edges.cend(); ++e)
			if (e->U == u)
				degree++;
			else if (!IS_DIGRAPH && e->V == u)
				degree++;
		return degree;
	}

	std::multiset<unsigned int>& getAdjacencesFrom(const unsigned int& u) const {
		if (!adjacences.empty())
			adjacences.clear();
		for (auto e = edges.cbegin(); e != edges.cend(); ++e)
			if (e->U == u)
				adjacences.insert(e->V);
			else if (!IS_DIGRAPH && e->V == u)
				adjacences.insert(e->U);
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
			writeVertex(u);
			getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); v != adjacences.cend(); v = adjacences.erase(v)) {
				std::cout << "->";
				writeVertex(*v);
			}
			std::cout << std::endl;
		}
	}

	void printIncidenceList() const {
		std::cout << "Lista de incidencia:" << std::endl;
		for (auto e = edges.cbegin(); e != edges.cend(); ++e) {
			writeVertex(e->U);
			std::cout << ',';
			writeVertex(e->V);
			std::cout << "->";
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
		std::cout << "Conjunto de vertices:" << std::endl;
		std::cout << "V={";
		unsigned int i = 0;
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			writeVertex(u);
			if (u + 1 < AMOUNT_VERTEXES) {
				std::cout << ',';
				if (++i % 20 == 0)
					std::cout << std::endl;
			}
		}
		std::cout << '}' << std::endl;
		std::cout << "Conjunto de arestas:" << std::endl;
		std::cout << "E={";
		i = 0;
		for (auto e = edges.cbegin(); e != edges.cend(); ++e) {
			writeEdge(*e);
			if ((e) != --edges.cend()) {
				std::cout << ',';
				if (++i % 12 == 0)
					std::cout << std::endl;
			}
		}
		std::cout << '}' << std::endl;
		std::cout << "Graus dos vertices:" << std::endl;
		std::cout << std::left << std::setw(4) << "Vi";
		std::cout << std::right;
		for (unsigned int i = 0; i < AMOUNT_VERTEXES; i++) {
			std::cout << '|' << std::setw(4);
			writeVertex(i);
		}
		std::cout << std::endl;
		if (IS_DIGRAPH) {
			std::cout << std::left << std::setw(4) << "in";
			std::cout << std::right;
			for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
				std::cout << '|' << std::setw(4);
				writeValue(getInDegreeFrom(u));
			}
			std::cout << std::endl;
		}
		std::cout << std::left << std::setw(4) << "out";
		std::cout << std::right;
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			std::cout << '|' << std::setw(4);
			writeValue(getOutDegreeFrom(u));
		}
		std::cout << std::endl;
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

	void writeVertex(const unsigned int& vertex) const {
		if (vertex != UINT_MAX)
			std::cout << "V" + std::to_string(vertex + 1);
		else
			std::cout << "nil";
	}

	void writeEdge(const Edge& edge) const {
		std::cout << '{';
		writeVertex(edge.U);
		std::cout << ',';
		writeVertex(edge.V);
		std::cout << '}';
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