#pragma once
#include "Scanner.h"
#include <set>

#ifndef NIL
#define NIL -1
#endif //!NIL

#ifndef MAX_WEIGHT
#define MAX_WEIGHT 999999
#endif // !MAX_WEIGHT

using namespace Scanner;

struct Edge {
	const unsigned int U, V;
	const int WEIGHT;

	Edge() = delete;
	Edge(const unsigned int u, const unsigned int v, const int w) : U(u), V(v), WEIGHT(w) {
		write("constructor {", U, ",", V, "=", WEIGHT, "}\n");
	}
	Edge(const Edge& other) : U(other.U), V(other.V), WEIGHT(other.WEIGHT) {
		write("copy constructor {", U, ",", V, "=", WEIGHT, "}\n");
	}
	~Edge() { write("destructor {", U, ",", V, "=", WEIGHT, "}\n"); }

	void print() const {
		write("{");
		writeVertex(U);
		write(",");
		writeVertex(V);
		write("}");
	}

	const bool operator<(const Edge& other) const {
		if (U < other.U) return true;
		if (other.U < U) return false;
		if (V < other.V) return true;
		if (other.V < V) return false;
		if (WEIGHT < other.WEIGHT) return true;
		if (other.WEIGHT < WEIGHT) return false;
	}

	const bool operator>(const Edge& other) const {
		if (U > other.U) return true;
		if (other.U > U) return false;
		if (V > other.V) return true;
		if (other.V > V) return false;
		if (WEIGHT > other.WEIGHT) return true;
		if (other.WEIGHT > WEIGHT) return false;
	}

	const Edge& operator=(const Edge& other) const {
		write("copy Assigment {", U, ",", V, "=", WEIGHT, "}\n");
		if (this != &other) {
			(unsigned int&)U = other.U;
			(unsigned int&)V = other.V;
			(int&)WEIGHT = other.WEIGHT;
		}
		return *this;
	}
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
	Graph(const unsigned int& amountVertices, const bool& isDigraph) :
		AMOUNT_VERTEXES(amountVertices), IS_DIGRAPH(isDigraph) {}
	Graph(const Graph& other) : AMOUNT_VERTEXES(other.AMOUNT_VERTEXES), IS_DIGRAPH(other.IS_DIGRAPH) {
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

	const bool isValidVertex(const unsigned int& v) const {
		return v < AMOUNT_VERTEXES;
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
		return MAX_WEIGHT;
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

		/*
		getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); v != adjacences.cend(); v = adjacences.erase(v)) {
			degree++;
			if (!IS_DIGRAPH && u == *v)
				degree++;
		}
		*/
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
		writeln("Matriz de adjacencia");
		write("Vi  |");
		for (unsigned int i = 0; i < AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
		}
		write("\n");
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			writeVertex(u);
			write("|");
			for (unsigned int v = 0, count = 0; v < AMOUNT_VERTEXES; v++, count = 0) {
				getAdjacencesFrom(u);
				for (auto vv = adjacences.cbegin(); vv != adjacences.cend(); vv = adjacences.erase(vv))
					if (*vv == v)
						count++;
				writeValue(count);
				write("|");
			}
			write("\n");
		}
	}

	void printIncidenceMatrix() const {
		writeln("Matriz de incidencia");
		write("V\\E |");
		for (unsigned int i = 0; i < edges.size(); i++) {
			writeEdge(i);
			write("|");
		}
		write("\n");
		int value;
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			writeVertex(u);
			write("|");
			for (auto e = edges.cbegin(); e != edges.cend(); e++) {
				value = 0;
				if (IS_DIGRAPH) {
					if (e->U == u)
						value = -1;
					else if (e->V == u)
						value = 1;
				}
				else if (e->U == u)
					value = 1;
				else if (e->V == u)
					value = 1;
				writeValue(value);
				write("|");
			}
			write("\n");
		}
	}

	void printAdjacenceList() const {
		writeln("Lista de adjacencia");
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			writeVertex(u);
			getAdjacencesFrom(u);
			for (auto v = adjacences.cbegin(); v != adjacences.cend(); v = adjacences.erase(v)) {
				write("->");
				writeVertex(*v);
			}
			write("\n");
		}
	}

	void printIncidenceList() const {
		writeln("Lista de incidencia");
		for (auto e = edges.cbegin(); e != edges.cend(); e++) {
			writeVertex(e->U);
			write(",");
			writeVertex(e->V);
			write("->");
		}
		write("\n");
	}

	void printCostMatrix() const {
		std::cout << "Matriz de custo" << std::endl;
		write("Vi  |");
		for (unsigned int i = 0; i < AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
		}
		write("\n");
		for (unsigned int i = 0; i < AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
			for (unsigned int j = 0; j < AMOUNT_VERTEXES; j++) {
				writeValue(getWeigthFrom(i, j));
				write("|");
			}
			write("\n");
		}
	}

	void printGraphInfo() const {
		writeln("Conjunto de vertices:");
		write("V={");
		unsigned int i = 0;
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			writeVertex(u);
			if (u + 1 < AMOUNT_VERTEXES) {
				write(',');
				if (++i % 20 == 0)
					write("\n");
			}
		}
		writeln("}", "Conjunto de arestas:");
		write("E={");
		i = 0;
		for (auto e = edges.cbegin(); e != edges.cend(); e++) {
			e->print();
			if ((e) != --edges.cend())
				write(',');
			if (++i % 12 == 0)
				write("\n");
		}
		writeln("}", "Graus dos vertices:");
		write("Vi  |");
		for (unsigned int i = 0; i < AMOUNT_VERTEXES; i++) {
			writeVertex(i);
			write("|");
		}
		if (IS_DIGRAPH) {
			write("\nin  |");
			for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
				writeValue(getInDegreeFrom(u));
				write("|");
			}
		}
		write("\nout |");
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			writeValue(getOutDegreeFrom(u));
			write("|");
		}
		write("\n");
	}

	void printVerticesToSelect() {
		for (unsigned int u = 0; u < AMOUNT_VERTEXES; u++) {
			write(u + 1, "= [");
			writeVertex(u);
			write("] ");
			if (u + 1 % 10 == 0)
				write("\n");
		}
		write("\n");
	}
};
