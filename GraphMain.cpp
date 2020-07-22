#include <fstream>
#include "PageTable.h"
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

Graph* graph;

void destroyGraph() {
	if (graph == nullptr)
		return;
	delete graph;
	graph = nullptr;
}

unsigned int uRead() {
	unsigned int value = NULL;
	std::cin >> value;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//system("CLS");
		std::cin >> value;
	}
	return value;
}

int iRead() {
	int value = NULL;
	std::cin >> value;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//system("CLS");
		std::cin >> value;
	}
	return value;
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
			std::cerr << e.what() << std::endl;
			fail = true;
		}
		while (fail == false && file >> u && file >> v && file >> w) {
			line++;
			u--;
			v--;
			if (graph->isValidVertex(u) == false) {
				fail = true;
				std::cerr << "Erro na linha " << line << " vertice U invalido." << std::endl;
			}
			if (graph->isValidVertex(v) == false) {
				fail = true;
				std::cerr << "Erro na linha " << line << " vertice V invalido." << std::endl;
			}
			if (graph->isValidWeight(w) == false) {
				fail = true;
				std::cerr << "Erro na linha " << line << " custo da aresta invalido." << std::endl;
			}
			if (!fail)
				graph->insertEdge(u, v, w);
		}
		file.close();
		if (fail)
			destroyGraph();
	} else
		std::cerr << "Nao foi possivel abrir o arquivo." << std::endl;
}

void createGraph() {
	unsigned int u, v;
	std::cout << "Dgt a qtd de Vertices." << std::endl;
	u = uRead();
	std::cout << "Dgt 1: Grafo dirigido.\nDgt outro valor: Grafo nao dirigido." << std::endl;
	int w = iRead();
	destroyGraph();
	try {
		graph = new Graph(u, w == 1);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return;
	}
	std::cout << "Dgt 1: Grafo valorado.\nDgt outro valor: Grafo nao valorado." << std::endl;
	w = iRead();
	u = v = NIL;
	do {
		graph->printVerticesToSelect();
		std::cout << "Selecione o numero do primeiro vertice ou 0 para retornar:" << std::endl;
		u = uRead();
		if (u != 0 && graph->isValidVertex(u)) {
			std::cout << "Selecione o segundo vertice ou 0 para cancelar:" << std::endl;
			v = uRead();
			if (v != 0 && graph->isValidVertex(v)) {
				if (w == 1) {// se grafo valorado
					std::cout << "Dgt o custo da Aresta:" << std::endl;
					w = iRead();
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
		std::cout << msg << std::endl;
		value = uRead();
	} while (value > graph->AMOUNT_VERTEXES || value < 1);
	return --value;
}

int main() {
	system("COLOR 1F");
	graph = nullptr;
	std::cout << "Desenvolvido por Carlos Henrique Stapait Junior." << std::endl;
	int choice = 0;

	PageTable table("Busca em largura recursiva: ");
	table.addRowHeader("Vi");
	table.addRowHeader("di");
	table.addRowHeader("pi");

	table.addColumnHeader("V1");
	table.addColumnHeader("V2");
	table.addColumnHeader("V3");
	table.addColumnHeader("V4");
	table.addColumnHeader("V5");
	table.addColumnHeader("V6");
	table.addColumnHeader("V7");
	table.addColumnHeader("V8");
	table.addColumnHeader("V9");
	table.addColumnHeader("V10");
	table.addColumnHeader("V11");
	table.addColumnHeader("V12");

	table.addRow({"0", "1", "2", "1", "2", "2", "1", "2", "2", "1", "2", "1"});
	table.addRow({"nil", "V1", "V2", "V1", "V12", "V7", "V1", "V7", "V2", "V1", "V10", "V1"});
	table.printPage(0);

	do {
		std::cout << "Dgt 0 para encerrar." << std::endl
			<< "Dgt 1 para criar um grafo." << std::endl
			<< "Dgt 2 para abrir um arquivo." << std::endl;
		if (graph != nullptr)
			std::cout << std::endl
			<< "Dgt 3 para imprimir Matriz de adjacencia." << std::endl
			<< "Dgt 4 para imprimir Matriz de incidencia." << std::endl
			<< "Dgt 5 para imprimir lista de adjacencia." << std::endl
			<< "Dgt 6 para imprimir lista de incidencia." << std::endl
			<< "Dgt 7 para imprimir Matriz de custo." << std::endl
			<< "Dgt 8 para imprimir Informacoes do grafo." << std::endl
			<< "---------------caminhamento---------------" << std::endl
			<< "Dgt 9 para Busca em largura." << std::endl
			<< "Dgt 10 para Busca em profundidade." << std::endl
			<< "--------------menor caminho---------------" << std::endl
			<< "Dgt 11 para Dijkstra." << std::endl
			<< "Dgt 12 para Floyd Warshall." << std::endl
			<< "Dgt 13 para Bellman-Ford." << std::endl
			<< "Dgt 14 para Fleury." << std::endl
			<< "Dgt 15 para Hierholzer." << std::endl
			<< "Dgt 16 para Robert Flores." << std::endl
			<< "Dgt 17 para Vizinho mais proximo." << std::endl
			<< "Dgt 18 para Ligacao mais economica." << std::endl
			<< "--------------fluxo em rede---------------"
			<< "\nDgt 19 para Ford-Fulkerson." << std::endl
			<< "---------------conexidade-----------------" << std::endl
			<< "Dgt 20 para Goodman." << std::endl
			<< "Dgt 21 para Conjuntos disjuntos." << std::endl
			<< "Dgt 22 para Kosaraju." << std::endl
			<< "Dgt 23 para Tarjan." << std::endl
			<< "----------arvore geradora minima----------" << std::endl
			<< "Dgt 24 para Kruskal." << std::endl
			<< "Dgt 25 para Prim." << std::endl
			<< "Dgt 26 para Boruvka," << std::endl
			<< "------------------------------------------"
			<< "Dgt 27 para Coloracao." << std::endl;
		choice = uRead();
		system("CLS");

		if (choice == 1)
			createGraph();
		else if (choice == 2)
			openFile("C:\\temp\\graph.txt");
		else if (graph == nullptr)
			std::cerr << "Grafo nao inicializado." << std::endl;
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
						std::cout << "Dgt 0 para busca iterativa.\nDgt qualquer valor para busca recursiva." << std::endl;
						bool isRecursive = iRead();
						BreadthFirstSearch bfs(*graph);
						bfs.bfs(getVertex("Dgt o numero do vertice de origem."), isRecursive);
					} break;
				case 10:
					{
						std::cout << "Dgt 0 para busca iterativa.\nDgt qualquer valor para busca recursiva." << std::endl;
						bool isRecursive = iRead();
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
							std::cerr << e.what() << std::endl;
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
							std::cerr << e.what() << std::endl;
						}
					} break;
				case 16:
					{
						std::cout << "Dgt 0 para busca iterativa.\nDgt qualquer valor para busca recursiva." << std::endl;
						bool isRecursive = iRead();
						RobertFlores robertFlores(*graph);
						robertFlores.robertFlores(getVertex("Dgt o numero do vertice de origem."), isRecursive);
					} break;
				case 17:
					{
						std::cout << "Dgt 0 para Vizinha mais proximo.\nDgt qualquer valor para Vizinho mais proximo repetivo." << std::endl;
						bool isRepetitive = iRead();
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
							std::cerr << e.what() << std::endl;
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
							std::cerr << e.what() << std::endl;
						}
					} break;
				case 20:
					{
						try {
							Goodman goodman(*graph);
							goodman.goodman();
						} catch (std::exception& e) {
							std::cerr << e.what() << std::endl;
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
							std::cerr << e.what() << std::endl;
						}
					} break;
				case 23:
					{
						try {
							Tarjan tarjan(*graph);
							tarjan.tarjan();
						} catch (std::exception& e) {
							std::cerr << e.what() << std::endl;
						}
					} break;
				case 24:
					{
						try {
							Kruskal kruskal(*graph);
							kruskal.kruskal();
						} catch (std::exception& e) {
							std::cerr << e.what() << std::endl;
						}
					} break;
				case 25:
					{
						try {
							Prim prim(*graph);
							prim.prim(getVertex("Dgt o numero do vertice de origem."));
						} catch (std::exception& e) {
							std::cerr << e.what() << std::endl;
						}
					} break;
				case 26:
					{
						try {
							Boruvka boruvka(*graph);
							boruvka.boruvka();
						} catch (std::exception& e) {
							std::cerr << e.what() << std::endl;
						}
					} break;
				case 27:
					{
						std::cout << "Dgt 0 para Coloracao sequencial.\nDgt qualquer valor para Coloracao heuristica." << std::endl;
						bool isSequential = iRead();
						Coloring coloring(*graph);
						coloring.coloring(isSequential);
					} break;
				default:
					std::cerr << "valor invalido, dgt novamente." << std::endl;
			}
			system("PAUSE");
			system("CLS");
		}
	} while (choice != 0);

	destroyGraph();
	std::cout << "Programa encerrado." << std::endl;
	return EXIT_SUCCESS;
}