#pragma once
#include "NonCopyable.h"
#include <stack>

/*
O objetivo do algoritmo Robert e Flores é identificar um ciclo Hamiltoniano,
e tem como finalidade passar por cada vertices apenas uma vez e voltar a origem.
funcionando.
*/
class RobertFlores : NonCopyable {
private:
	const Graph& graph;
	unsigned int* array;
	bool* visited;
	unsigned int index;

	void robertFloresRecursive(const unsigned int u);

	void robertFloresIterative(unsigned int u);

	void print() const;

public:
	RobertFlores() = delete;
	RobertFlores(const Graph& graph) noexcept(false);
	~RobertFlores();

	void robertFlores(const unsigned int source, const bool isRecursive);
};