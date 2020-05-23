#pragma once
#include "Graph.h"

using namespace Scanner;

/*
funcionando, falta testar com grafos dirigidos.
*/

class CheaperConnection {
private:
	Graph graph;
	std::multiset<Edge> edges;
	bool* visited;

	const bool bfs(unsigned int u, const unsigned int& k) {
		bool found = false;
		std::queue<unsigned int> queue;
		queue.push(u);
		while(!queue.empty() && !found) {
			u = queue.front();
			queue.pop();
			visited[u] = true;
			std::multiset<unsigned int>& adjacences = graph.getAdjacencesFrom(u);
			for(auto v = adjacences.cbegin(); v != adjacences.cend() && !found; v = adjacences.erase(v)) {
				if(!visited[*v])
					queue.push(*v);
				found = *v == k;
			}
		}
		return found;
	}

public:
    CheaperConnection() = delete;
	CheaperConnection(const Graph& graph) : graph(graph.AMOUNT_VERTICES, graph.IS_DIGRAPH) {
		edges = graph.getEdges();
		visited = new bool[graph.AMOUNT_VERTICES];
	}

	~CheaperConnection() {
		edges.clear();
		delete[] visited;
		visited = nullptr;
	}

	void cheaperConnection() {
		writeln("Ligacao mais economica:");
		while(!edges.empty()) {
		    for(unsigned int i = 0; i < graph.AMOUNT_VERTICES; i++)
                visited[i] = false;

			auto lowerWeight = edges.cbegin();
			for(auto e = edges.cbegin(); e != edges.cend(); e++)
				if(e->WEIGHT < lowerWeight->WEIGHT)
					lowerWeight = e;

			if(!bfs(lowerWeight->U, lowerWeight->V)) {
				graph.insertEdge(lowerWeight->U, lowerWeight->V, lowerWeight->WEIGHT);
				lowerWeight->print();
				write("\n");
			}

			edges.erase(lowerWeight);
		}
	}
};
