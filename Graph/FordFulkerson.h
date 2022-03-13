#pragma once
#include "NonCopyable.h"
#include <queue>

class FordFulkerson : private NonCopyable {
private:
	const Graph& graph;
	int** costMatrix;
	unsigned int* predecessor;
	bool* visited;

	bool bfsUtil(unsigned int u, const unsigned int k);

public:
	FordFulkerson() = delete;
	FordFulkerson(const Graph& graph) noexcept(false);
	~FordFulkerson();

	void fordFulkerson(const unsigned int source, const unsigned int sink);
};