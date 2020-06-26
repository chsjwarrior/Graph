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

/*
https://en.wikipedia.org/wiki/Graph_theory
Bellman–Ford algorithm
Boruvka's algorithm
Breadth-first search
Depth-first search
Dijkstra's algorithm
Edmonds–Karp algorithm
Floyd–Warshall algorithm
Ford–Fulkerson algorithm
Hopcroft–Karp algorithm
Hungarian algorithm
Kosaraju's algorithm
Kruskal's algorithm
Nearest neighbour algorithm
Network simplex algorithm
Planarity testing algorithms
Prim's algorithm
Push–relabel maximum flow algorithm
Tarjan's strongly connected components algorithm
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
				writeErr("Erro na linha ", line, " vertice U invalido.");
			}
			if (!graph->isValidVertex(v)) {
				fail = true;
				writeErr("Erro na linha ", line, " vertice V invalido.");
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
					w = read("Dgt o custo da Aresta:");
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
		value = read(msg);
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
					"------------------------------------------",
					"Dgt 9 para Busca em largura.",
					"Dgt 10 para Busca em profundidade.",
					"Dgt 11 para Dijkstra.",
					"Dgt 12 para Floyd Warshall.",
					"Dgt 13 para Bellman-Ford.",
					"Dgt 14 para Ford-Fulkerson.",
					"Dgt 15 para Fleury.",
					"Dgt 16 para Robert Flores.",
					"Dgt 17 para Vizinho mais proximo.",
					"Dgt 18 para Ligacao mais economica.",
					"Dgt 19 para Goodman.",
					"Dgt 20 para Conjuntos disjuntos.",
					"Dgt 21 para Kosaraju.",
					"Dgt 22 para Tarjan.",
					"Dgt 23 para Kruskal.",
					"Dgt 24 para Prim.",
					"Dgt 25 para Coloracao.");
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
						bool isRecursive = read("Dgt 0 para busca iterativa. \nDgt qualquer valor para busca recursiva.");
						BreadthFirstSearch bfs(*graph);
						bfs.bfs(getVertex("Dgt o numero do vertice de origem."), isRecursive);
					}
					break;
				case 10:
					{
						bool isRecursive = read("Dgt 0 para busca iterativa. \nDgt qualquer valor para busca recursiva.");
						DepthFirstSearch dfs(*graph);
						dfs.dfs(getVertex("Dgt o numero do vertice de origem."), isRecursive);
					}
					break;
				case 11:
					{
						Dijkstra dijkstra(*graph);
						dijkstra.dijkstra(getVertex("Dgt o numero do vertice de origem."));
					}
					break;
				case 12:
					{
						FloydWarshall floydWarshall(*graph);
						floydWarshall.floydWarshall();
					}
					break;
				case 13:
					{
						BellmanFord bellmanFord(*graph);
						bellmanFord.bellmanFord(getVertex("Dgt o numero do vertice de origem."));
					}
					break;
				case 14:
					{
						FordFulkerson fordFulkerson(*graph);
						unsigned int origin = getVertex("Dgt o numero do vertice de origem.");
						unsigned int destiny = getVertex("Dgt o numero do vertice de destino.");
						fordFulkerson.fordFulkerson(origin, destiny);
					}
					break;
				case 15:
					{
						Fleury fleury(*graph);
						fleury.fleury();
					}
					break;
				case 16:
					{
						RobertFlores robertFlores(*graph);
						robertFlores.robertFlores(getVertex("Dgt o numero do vertice de origem."));
					}
					break;
				case 17:
					{
						bool isRepetitive = read("Dgt 0 para Vizinha mais proximo. \nDgt qualquer valor para Vizinho mais proximo repetivo.");
						CloserNeighbor closerNeighbor(*graph);
						if (isRepetitive)
							closerNeighbor.closerNeighborRepetitive();
						else
							closerNeighbor.closerNeighbor(getVertex("Dgt o numero do vertice de origem."));
					}
					break;
				case 18:
					{
						CheapestLink cheapestLink(*graph);
						cheapestLink.cheapestLink();
					}
					break;
				case 19:
					{
						Goodman goodman(*graph);
						goodman.goodman();
					}
					break;
				case 20:
					{
						DisjointAssemblies disjointAssemblies(*graph);
						disjointAssemblies.connectedComponents();
					}
					break;
				case 21:
					{
						Kosaraju kosaraju(*graph);
						kosaraju.kosaraju();
					}
					break;
				case 22:
					{
						Tarjan tarjan(*graph);
						tarjan.tarjan();
					}
					break;
				case 23:
					{
						Kruskal kruskal(*graph);
						kruskal.kruskal();
					}
					break;
				case 24:
					{
						Prim prim(*graph);
						prim.prim(getVertex("Dgt o numero do vertice de origem."));
					}
					break;
				case 25:
					{
						bool isSequential = read("Dgt 0 para Coloracao sequencial. \nDgt qualquer valor para Coloracao heuristica.");
						Coloring coloring(*graph);
						coloring.coloring(isSequential);
					}
					break;
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