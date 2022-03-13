#pragma once
#include "NonCopyable.h"
#include <queue>
/*
O algoritmo da busca em largura (Breadth-First Search - BFS) e utilizado para realizar uma busca em estrutura de dados do tipo arvore.
O algoritmo come�a em um vertice raiz e explora todos os vertices vizinhos antes de ava�ar e explorar os proximos vertices vizinhos inexplorados.
O algoritmo da busca em largura calcula pode calcular a dist�ncia (menor n�mero de arestas)
desde o v�rtice raiz ate todos os v�rtices acessiveis.
*/
class BreadthFirstSearch : private NonCopyable {
	const Graph& graph;
	unsigned int* discovery;
	unsigned int* predecessor;
	bool* visited;

	void bfsRecursive(std::queue<unsigned int>& queue);

	void bfsIterative(std::queue<unsigned int>& queue);

	void print(const std::string& title) const;

public:
	BreadthFirstSearch() = delete;
	explicit BreadthFirstSearch(const Graph& graph) noexcept(false);
	~BreadthFirstSearch();

	void bfs(const unsigned int source, const bool isRecursive);
};