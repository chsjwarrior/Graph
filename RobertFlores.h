#pragma once
#include "Graph.h"

using namespace Scanner;

/*
O objetivo do algoritmo Robert e Flores é identificar um ciclo Hamiltoniano,
e tem como finalidade passar por cada vertices apenas uma vez e voltar a origem.
funcionando.
*/

class RobertFlores {
private:
	const Graph& graph;
	unsigned int* array;
	unsigned int index;

	const bool contains(const unsigned int& v) const {
		for (unsigned int i = 0; i < index; i++)
			if (array[i] == v)
				return true;
		return false;
	}

	void robertFloresR(const unsigned int& u) {
		array[index++] = u;
		print();

		std::multiset<unsigned int> adjacences = graph.getAdjacencesFrom(u);
		for (auto v = adjacences.cbegin(); !adjacences.empty(); v = adjacences.erase(v)) {
			if (*v != u)
				if (index == graph.AMOUNT_VERTICES && array[0] == *v) {
					write(" achou");
					break;
				} else if (!contains(*v))
					robertFloresR(*v);
		}
		if (index > 0)
			index--;
		print();
	}

	void print() const {
		write("\n");
		for (unsigned int i = 0; i < index; i++) {
			writeVertex(array[i]);
			write("-");
		}
	}

public:
	RobertFlores() = delete;
	RobertFlores(const Graph& graph) : graph(graph) {
		array = new unsigned int[graph.AMOUNT_VERTICES];
		index = 0;
	}

	~RobertFlores() {
		delete[] array;
		array = nullptr;
		index = NULL;
	}

	void robertFlores(const unsigned int& origin) {
		write("Robert & Flores:");
		robertFloresR(origin);
		write("\n");
	}
};