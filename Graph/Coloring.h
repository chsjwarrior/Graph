#pragma once
#include "NonCopyable.h"
/*
Colora��o de grafos e um caso especial de rotulagem dos vertices atraves de "cores", sujeitos a certas restri��es.
Na sua forma mais simples, e uma maneira de colorir os vertices de um grafo, de modo que nao haja dois vertices adjacentes da mesma cor.
Da mesma forma, uma colora�ao de aresta atribui uma cor a cada aresta, de modo que nao haja duas arestas adjacentes da mesma cor,
e uma colora��o de face de um grafo planar atribui uma cor a cada face ou regi�o, de modo que nenhuma das duas faces que compartilham um limite tenha a mesma cor.
*/
class Coloring : private NonCopyable {
private:
	const Graph& graph;
	unsigned int* color;

	void print(const std::string& text) const override;

	void setValidColor(const unsigned int u);

	unsigned int getHigherDegreeNotColored();

public:
	Coloring() = delete;
	Coloring(const Graph& graph) noexcept(false);
	~Coloring();

	void coloring(const bool isHeuristic);
};