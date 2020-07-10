#include <fstream>
#include <iomanip>
#include "Scanner.h"
#include "Graph.h"
#include "BreadthFirstSearch.h"
#include "DepthFirstSearch.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"
#include "BellmanFord.h"
#include "Fleury.h"
#include "Hierholzer.h"
#include "RobertFlores.h"
#include "CloserNeighbor.h"
#include "CheapestLink.h"
#include "FordFulkerson.h"
#include "Goodman.h"
#include "DisjointAssemblies.h"
#include "Kosaraju.h"
#include "Tarjan.h"
#include "Kruskal.h"
#include "Prim.h"
#include "Boruvka.h"
#include "Coloring.h"

/*
https://en.wikipedia.org/wiki/Graph_theory
Boruvka's algorithm
Edmonds–Karp algorithm
Hopcroft–Karp algorithm
Hungarian algorithm
Network simplex algorithm
Planarity testing algorithms
Push–relabel maximum flow algorithm
Topological sorting
*/

using namespace Scanner;

Graph* graph;

void destroyGraph() {
	if (graph == nullptr)
		return;
	delete graph;
	graph = nullptr;
}

void openFile(const char path[]) {
	std::ifstream file(path, std::ios::in);
	if (file.is_open()) {
		bool fail = false;
		unsigned int u, v, line = 1;
		int w;
		file >> u >> v >> w;
		destroyGraph();
		try {
			graph = new Graph(u, w != 0);
		} catch (std::exception& e) {
			writeErr(e.what());
			fail = true;
		}
		while (fail == false && file >> u && file >> v && file >> w) {
			line++;
			u--;
			v--;
			if (graph->isValidVertex(u) == false) {
				fail = true;
				writeErr("Erro na linha ", line, " vertice U invalido.");
			}
			if (graph->isValidVertex(v) == false) {
				fail = true;
				writeErr("Erro na linha ", line, " vertice V invalido.");
			}
			if (graph->isValidWeight(w) == false) {
				writeErr("Erro na linha ", line, " custo da aresta invalido.");
				fail = true;
			}
			if (!fail)
				graph->insertEdge(u, v, w);
		}
		file.close();
		if (fail)
			destroyGraph();
	} else
		writeln("Nao foi possivel abrir o arquivo.");
}

void createGraph() {
	unsigned int u, v;
	u = uRead("Dgt a qtd de Vertices.");
	int w = iRead("Dgt 1: Grafo dirigido.", "Dgt outro valor: Grafo nao dirigido.");
	destroyGraph();
	try {
		graph = new Graph(u, w == 1);
	} catch (std::exception& e) {
		writeErr(e.what());
		return;
	}
	w = iRead("Dgt 1: Grafo valorado.", "Dgt outro valor: Grafo nao valorado.");
	u = v = NIL;
	do {
		graph->printVerticesToSelect();
		u = uRead("Selecione o numero do primeiro vertice ou 0 para retornar:");
		if (u != 0 && graph->isValidVertex(u)) {
			v = uRead("Selecione o segundo vertice ou 0 para cancelar:");
			if (v != 0 && graph->isValidVertex(v)) {
				if (w == 1) {// se grafo valorado
					w = iRead("Dgt o custo da Aresta:");
					if (graph->isValidWeight(w))
						graph->insertEdge(u - 1, v - 1, w);
					w = 1;
				} else
					graph->insertEdge(u - 1, v - 1);
			}
		}
	} while (v != 0 && u != 0);
}

unsigned int getVertex(const char msg[]) {
	unsigned int value;
	do {
		graph->printVerticesToSelect();
		value = uRead(msg);
	} while (value > graph->AMOUNT_VERTEXES || value < 1);
	return --value;
}

int main() {
	system("COLOR 1F");
	graph = nullptr;
	writeln("Desenvolvido por Carlos Henrique Stapait Junior.");
	int choice = 0;

	do {
		writeln("Dgt 0 para encerrar.",
				"Dgt 1 para criar um grafo.",
				"Dgt 2 para abrir um arquivo.");
		if (graph != nullptr)
			writeln("------------------------------------------",
					"Dgt 3 para imprimir Matriz de adjacencia.",
					"Dgt 4 para imprimir Matriz de incidencia.",
					"Dgt 5 para imprimir lista de adjacencia.",
					"Dgt 6 para imprimir lista de incidencia.",
					"Dgt 7 para imprimir Matriz de custo.",
					"Dgt 8 para imprimir Informacoes do grafo.",
					"---------------caminhamento---------------",
					"Dgt 9 para Busca em largura.",
					"Dgt 10 para Busca em profundidade.",
					"--------------menor caminho---------------",
					"Dgt 11 para Dijkstra.",
					"Dgt 12 para Floyd Warshall.",
					"Dgt 13 para Bellman-Ford.",
					"Dgt 14 para Fleury.",
					"Dgt 15 para Hierholzer.",
					"Dgt 16 para Robert Flores.",
					"Dgt 17 para Vizinho mais proximo.",
					"Dgt 18 para Ligacao mais economica.",
					"--------------fluxo em rede---------------",
					"Dgt 19 para Ford-Fulkerson.",
					"---------------conexidade-----------------",
					"Dgt 20 para Goodman.",
					"Dgt 21 para Conjuntos disjuntos.",
					"Dgt 22 para Kosaraju.",
					"Dgt 23 para Tarjan.",
					"----------arvore geradora minima----------",
					"Dgt 24 para Kruskal.",
					"Dgt 25 para Prim.",
					"Dgt 26 para Boruvka,",
					"------------------------------------------",
					"Dgt 27 para Coloracao.");
		std::cin >> choice;
		system("CLS");

		if (choice == 1)
			createGraph();
		else if (choice == 2)
			openFile("C:\\temp\\graph.txt");
		else if (graph == nullptr)
			writeErr("Grafo nao inicializado.");
		else if (choice != 0) {
			switch (choice) {
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
					{
						bool isRecursive = iRead("Dgt 0 para busca iterativa. \nDgt qualquer valor para busca recursiva.");
						BreadthFirstSearch bfs(*graph);
						bfs.bfs(getVertex("Dgt o numero do vertice de origem."), isRecursive);
					} break;
				case 10:
					{
						bool isRecursive = iRead("Dgt 0 para busca iterativa. \nDgt qualquer valor para busca recursiva.");
						DepthFirstSearch dfs(*graph);
						dfs.dfs(getVertex("Dgt o numero do vertice de origem."), isRecursive);
					} break;
				case 11:
					{
						Dijkstra dijkstra(*graph);
						dijkstra.dijkstra(getVertex("Dgt o numero do vertice de origem."));
					} break;
				case 12:
					{
						FloydWarshall floydWarshall(*graph);
						floydWarshall.floydWarshall();
					} break;
				case 13:
					{
						try {
							BellmanFord bellmanFord(*graph);
							bellmanFord.bellmanFord(getVertex("Dgt o numero do vertice de origem."));
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;

				case 14:
					{
						Fleury fleury(*graph);
						fleury.fleury();
					} break;
				case 15:
					{
						try {
							Hierholzer Hierholzer(*graph);
							Hierholzer.hierholzer();
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 16:
					{
						bool isRecursive = iRead("Dgt 0 para busca iterativa. \nDgt qualquer valor para busca recursiva.");
						RobertFlores robertFlores(*graph);
						robertFlores.robertFlores(getVertex("Dgt o numero do vertice de origem."), isRecursive);
					} break;
				case 17:
					{
						bool isRepetitive = iRead("Dgt 0 para Vizinha mais proximo. \nDgt qualquer valor para Vizinho mais proximo repetivo.");
						CloserNeighbor closerNeighbor(*graph);
						if (isRepetitive)
							closerNeighbor.closerNeighborRepetitive();
						else
							closerNeighbor.closerNeighbor(getVertex("Dgt o numero do vertice de origem."));
					} break;
				case 18:
					{
						try {
							CheapestLink cheapestLink(*graph);
							cheapestLink.cheapestLink();
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 19:
					{
						unsigned int source = getVertex("Dgt o numero do vertice de origem.");
						unsigned int sink = getVertex("Dgt o numero do vertice de destino.");
						try {
							FordFulkerson fordFulkerson(*graph);
							fordFulkerson.fordFulkerson(source, sink);
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 20:
					{
						try {
							Goodman goodman(*graph);
							goodman.goodman();
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 21:
					{
						DisjointAssemblies disjointAssemblies(*graph);
						disjointAssemblies.connectedComponents();
					} break;
				case 22:
					{
						try {
							Kosaraju kosaraju(*graph);
							kosaraju.kosaraju();
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 23:
					{
						try {
							Tarjan tarjan(*graph);
							tarjan.tarjan();
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 24:
					{
						try {
							Kruskal kruskal(*graph);
							kruskal.kruskal();
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 25:
					{
						try {
							Prim prim(*graph);
							prim.prim(getVertex("Dgt o numero do vertice de origem."));
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 26:
					{
						try {
							Boruvka boruvka(*graph);
							boruvka.boruvka();
						} catch (std::exception& e) {
							writeErr(e.what());
						}
					} break;
				case 27:
					{
						bool isSequential = iRead("Dgt 0 para Coloracao sequencial. \nDgt qualquer valor para Coloracao heuristica.");
						Coloring coloring(*graph);
						coloring.coloring(isSequential);
					} break;
				default:
					writeErr("valor invalido, dgt novamente.");
			}
			system("PAUSE");
			system("CLS");
		}
	} while (choice != 0);

	destroyGraph();
	writeln("Programa encerrado.");
	return 0;
}