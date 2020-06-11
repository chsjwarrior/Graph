#include <fstream>
#include "Scanner.h"
#include "Graph.h"
#include "BreadthFirstSearch.h"
#include "DepthFirstSearch.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"
#include "BellmanFord.h"
#include "FordFulkerson.h"
#include "Fleury.h"
#include "RobertFlores.h"
#include "CloserNeighbor.h"
#include "CheapestLink.h"
#include "Goodman.h"
#include "DisjointAssemblies.h"
#include "Kosaraju.h"
#include "Tarjan.h"
#include "Kruskal.h"
#include "Prim.h"
#include "Coloring.h"

using namespace Scanner;

Graph* graph;

void destroyGraph() {
	if (graph == nullptr)
		return;
	delete graph;
	graph = nullptr;
}

void openFile(const std::string& path) {
	std::ifstream file(path);
	if (file.is_open()) {
		bool fail = false;
		unsigned int u, v, line = 1;
		int w;
		file >> u >> v >> w;
		destroyGraph();
		graph = new Graph(u, w != 0);
		while (file >> u && file >> v && file >> w && !fail) {
			line++;
			u--;
			v--;
			if (!graph->isValidVertex(u)) {
				fail = true;
				writeln("Erro na linha ", line, " vertice U invalido");
			}
			if (!graph->isValidVertex(v)) {
				fail = true;
				writeln("Erro na linha ", line, " vertice V invalido");
			}
			if (!fail)
				graph->insertEdge(u, v, w);
		}
		file.close();
		if (fail)
			destroyGraph();
		else
			writeln("Grafo criado com exito.");
	} else
		writeln("Não foi possivel abrir o arquivo.");
}

void createGraph() {
	unsigned int u = read("Dgt a qtd de Vertices.");
	unsigned int v = read("Dgt 1: Grafo dirigido.", "Dgt outro valor: Grafo nao dirigido.");
	destroyGraph();
	graph = new Graph(u, v == 1);
	int w = read("Dgt 1: Grafo valorado.", "Dgt outro valor: Grafo nao valorado.");

	do {
		graph->printVerticesToSelect();
		u = read("Selecione o numero do primeiro vertice ou 0 para retornar:");
		if (u != 0) {
			v = read("Selecione o segundo vertice ou 0 para cancelar:");
			if (v != 0) {
				if (w == 1) {// se grafo valorado
					w = read("Dgt o custo da Aresta: ");
					graph->insertEdge(u - 1, v - 1, w);
					w = 1;
				} else
					graph->insertEdge(u - 1, v - 1);
			}
		}
	} while (v != 0 && u != 0);
}

unsigned int getOrigin(std::string msg) {
	unsigned int origin;
	do {
		graph->printVerticesToSelect();
		origin = read(msg);
	} while (origin > graph->AMOUNT_VERTEXES || origin < 1);
	return --origin;
}

void bfs() {
	BreadthFirstSearch bfs(*graph);
	bfs.bfs(getOrigin("Dgt o vertice de origem"));
}

void dfs() {
	DepthFirstSearch dfs(*graph);
	dfs.dfs(getOrigin("Dgt o vertice de origem"));
}

void dijkstra() {
	Dijkstra dijkstra(*graph);
	dijkstra.dijkstra(getOrigin("Dgt o vertice de origem"));
}

void floydWarshall() {
	FloydWarshall floydWarshall(*graph);
	floydWarshall.floydWarshall();
}

void bellmanFord() {
	BellmanFord bellmanFord(*graph);
	bellmanFord.bellmanFord(getOrigin("Dgt o vertice de origem"));
}

void fordFulkerson() {
	FordFulkerson fordFulkerson(*graph);
	fordFulkerson.fordFulkerson(getOrigin("Dgt o vertice de origem"), getOrigin("Dgt o vertice de destino"));
}

void fleury() {
	Fleury fleury(*graph);
	fleury.fleury();
}

void robertFlores() {
	RobertFlores robertFlores(*graph);
	robertFlores.robertFlores(getOrigin("Dgt o vertice de origem"));
}

void closerNeighbor() {
	CloserNeighbor closerNeighbor(*graph);
	closerNeighbor.closerNeighbor(getOrigin("Dgt o vertice de origem"));
}

void closerNeighborRepetitive() {
	CloserNeighbor closerNeighbor(*graph);
	closerNeighbor.closerNeighborRepetitive();
}

void cheapestLink() {
	CheapestLink cheapestLink(*graph);
	cheapestLink.cheaperConnection();
}

void goodman() {
	Goodman goodman(*graph);
	goodman.goodman();
}

void disjointAssemblies() {
	DisjointAssemblies disjointAssemblies(*graph);
	disjointAssemblies.connectedComponents();
}

void kosaraju() {
	Kosaraju kosaraju(*graph);
	kosaraju.kosaraju();
}

void tarjan() {
	Tarjan tarjan(*graph);
	tarjan.tarjan();
}

void kruskal() {
	Kruskal kruskal(*graph);
	kruskal.kruskal();
}

void prim() {
	Prim prim(*graph);
	prim.prim(getOrigin("Dgt o vertice de origem"));
}

void sequentialColoring() {
	Coloring coloring(*graph);
	coloring.sequentialColoring();
}

void heuristicColoring() {
	Coloring coloring(*graph);
	coloring.heuristicColoring();
}

int main() {
	graph = nullptr;
	writeln("Desenvolvido por Carlos Henrique Stapait Junior");
	int value = 0;

	do {
		writeln("Dgt 0 para encerrar.",
				"Dgt 1 para criar um grafo.",
				"Dgt 2 para abrir um arquivo.");
		if (graph != nullptr)
			writeln("--------------------------------------------",
					"Dgt 3 para imprimir Matriz de adjacencia",
					"Dgt 4 para imprimir Matriz de incidencia",
					"Dgt 5 para imprimir lista de adjacencia",
					"Dgt 6 para imprimir lista de incidencia",
					"Dgt 7 para imprimir Matriz de custo",
					"Dgt 8 para imprimir Informacoes do grafo",
					"--------------------------------------------",
					"Dgt 9 para Busca em largura",
					"Dgt 10 para Busca em profundidade",
					"Dgt 11 para Dijkstra",
					"Dgt 12 para Floyd Warshall",
					"Dgt 13 para Bellman-Ford",
					"Dgt 14 para Ford-Fulkerson",
					"Dgt 15 para Fleury",
					"Dgt 16 para Robert Flores",
					"Dgt 17 para Vizinho mais proximo",
					"Dgt 18 para Vizinho mais proximo repetitivo",
					"Dgt 19 para Ligacao mais economica",
					"Dgt 20 para Goodman",
					"Dgt 21 para Conjuntos disjuntos",
					"Dgt 22 para Kosaraju",
					"Dgt 23 para Tarjan",
					"Dgt 24 para Kruskal",
					"Dgt 25 para Prim",
					"Dgt 26 para Coloracao sequencial",
					"Dgt 27 para Coloracao heuristica");
		value = read("--------------------------------------------");

		system("CLS");

		if (value == 1) {
			createGraph();
		} else if (value == 2) {
			openFile("C:\\temp\\graph.txt");
		} else if (graph == nullptr) {
			writeErr("Grafo não inicializado");
		} else if (value != 0) {
			switch (value) {
			case 3:
				graph->printAdjacencematrix();
				break;
			case 4:
				graph->printIncidenceMatrix();
				break;
			case 5:
				graph->printAdjacenceList();
				break;
			case 6:
				graph->printIncidenceList();
				break;
			case 7:
				graph->printCostMatrix();
				break;
			case 8:
				graph->printGraphInfo();
				break;
			case 9:
				bfs();
				break;
			case 10:
				dfs();
				break;
			case 11:
				dijkstra();
				break;
			case 12:
				floydWarshall();
				break;
			case 13:
				bellmanFord();
				break;
			case 14:
				fordFulkerson();
				break;
			case 15:
				fleury();
				break;
			case 16:
				robertFlores();
				break;
			case 17:
				closerNeighbor();
				break;
			case 18:
				closerNeighborRepetitive();
				break;
			case 19:
				cheapestLink();
				break;
			case 20:
				goodman();
				break;
			case 21:
				disjointAssemblies();
				break;
			case 22:
				kosaraju();
				break;
			case 23:
				tarjan();
				break;
			case 24:
				kruskal();
				break;
			case 25:
				prim();
				break;
			case 26:
				sequentialColoring();
				break;
			case 27:
				heuristicColoring();
				break;
			default:
				writeErr("valor invalido, dgt novamente");
			}
		}
	} while (value != 0);

	destroyGraph();
	writeln("Programa encerrado");
	return 0;

	return 0;
}
