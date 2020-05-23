#include <fstream>
#include "Scanner.h"
#include "Graph.h"
#include "BreadthFirstSearch.h"
#include "DepthFirstSearch.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"
#include "Fleury.h"
#include "RobertFlores.h"
#include "CloserNeighbor.h"
#include "CheaperConnection.h"
#include "Goodman.h"
#include "DisjointAssemblies.h"
#include "Kruskal.h"
#include "Prim.h"
#include "Coloring.h"

using namespace Scanner;

Graph* graph;

void destroyGraph() {
	if(graph == nullptr)
		return;
	delete graph;
	graph = nullptr;
}

void openFile(const std::string& path) {
	std::ifstream file(path);
	if(file.is_open()) {
		bool fail = false;
		unsigned int u, v, line = 1;
		int w;
		file >> u >> v >> w;
		destroyGraph();
		graph = new Graph(u, w != 0);
		while(file >> u && file >> v && file >> w && !fail) {
			line++;
			u--;
			v--;
			if(!graph->isValidVertex(u)) {
				fail = true;
				writeln("Erro na linha ", line, " vertice U invalido");
			}
			if(!graph->isValidVertex(v)) {
				fail = true;
				writeln("Erro na linha ", line, " vertice V invalido");
			}
			if(!fail)
				graph->insertEdge(u, v, w);
		}
		file.close();
		if(fail)
			destroyGraph();
		else
			writeln("Grafo criado com exito.");
	} else
		writeln("Não foi possivel abrir o arquivo.");
}

unsigned int getOrigin() {
	unsigned int origin;
	do {
		graph->printVerticesToSelect();
		origin = read("Dgt o vertice de origem");
	} while(origin > graph->AMOUNT_VERTICES);
	return --origin;
}

void bfs() {
	BreadthFirstSearch bfs(*graph);
	bfs.bfs(getOrigin());
}

void dfs() {
	DepthFirstSearch dfs(*graph);
	dfs.dfs(getOrigin());
}

void dijkstra() {
	if(graph == nullptr)
		return;
	Dijkstra dijkstra(*graph);
	dijkstra.dijkstra(getOrigin());
}

void floydWarshall() {
	if(graph == nullptr)
		return;
	FloydWarshall floydWarshall(*graph);
	floydWarshall.floydWarshall();
}

void fleury() {
	if(graph == nullptr)
		return;
	Fleury fleury(*graph);
	fleury.fleury();
}

void robertFlores() {
	if(graph == nullptr)
		return;
	RobertFlores robertFlores(*graph);
	robertFlores.robertFlores(getOrigin());
}

void closerNeighbor() {
	if(graph == nullptr)
		return;
	CloserNeighbor closerNeighbor(*graph);
	closerNeighbor.closerNeighbor(getOrigin());
}

void closerNeighborRepetitive() {
	if(graph == nullptr)
		return;
	CloserNeighbor closerNeighbor(*graph);
	closerNeighbor.closerNeighborRepetitive();
}

void cheaperConnection() {
	if(graph == nullptr)
		return;
	CheaperConnection cheaperConnection(*graph);
	cheaperConnection.cheaperConnection();
}

void goodman() {
	if(graph == nullptr)
		return;
	Goodman goodman(*graph);
	goodman.goodman();
}

void disjointAssemblies() {
	if(graph == nullptr)
		return;
	DisjointAssemblies disjointAssemblies(*graph);
	disjointAssemblies.connectedComponents();
}

void kruskal() {
	if(graph == nullptr)
		return;
	Kruskal kruskal(*graph);
	kruskal.kruskal();
}

void prim() {
	if(graph == nullptr)
		return;
	Prim prim(*graph);
	prim.prim(getOrigin());
}

void sequentialColoring() {
	if(graph == nullptr)
		return;
	Coloring coloring(*graph);
	coloring.sequentialColoring();
}

void heuristicColoring() {
	if(graph == nullptr)
		return;
	Coloring coloring(*graph);
	coloring.heuristicColoring();
}

int main() {
    graph = nullptr;
	writeln("Desenvolvido por Carlos Henrique Stapait Junior");
	int value = 0;

	do {
		writeln("Dgt 0 para encerrar.",
                "Dgt 1 para abrir um grafo.");
        if (graph != nullptr)
            writeln("--------------------------------------------",
                  "Dgt 2 para imprimir Matriz de adjacencia",
                  "Dgt 3 para imprimir Matriz de incidencia",
                  "Dgt 4 para imprimir lista de adjacencia",
                  "Dgt 5 para imprimir lista de incidencia",
                  "Dgt 6 para imprimir Matriz de custo",
                  "Dgt 7 para imprimir Informacoes do grafo",
                  "--------------------------------------------",
                  "Dgt 8 para Busca em largura",
                  "Dgt 9 para Busca em profundidade",
                  "Dgt 10 para Dijkstra",
                  "Dgt 11 para Floyd Warshall",
                  "Dgt 12 para Fleury",
                  "Dgt 13 para Robert Flores",
                  "Dgt 14 para Vizinho mais proximo",
                  "Dgt 15 para Vizinho mais proximo repetitivo",
                  "Dgt 16 para Ligacao mais economica",
                  "Dgt 17 para Goodman",
                  "Dgt 18 para Conjuntos disjuntos",
                  "Dgt 19 para Kruskal",
                  "Dgt 20 para Prim",
                  "Dgt 21 para Coloracao sequencial",
                  "Dgt 22 para Coloracao heuristica");
        value = read("--------------------------------------------");

		system("CLS");
		if (value != 0) {
            if (value == 1) {
                openFile("C:\\temp\\graph.txt");
            } else if (graph == nullptr){
                writeErr("Grafo não inicializado");
            } else {
                switch(value) {
                case 2:
                    graph->printAdjacencematrix();
                    break;
                case 3:
                    graph->printIncidenceMatrix();
                    break;
                case 4:
                    graph->printAdjacenceList();
                    break;
                case 5:
                    graph->printIncidenceList();
                    break;
                case 6:
                    graph->printCostMatrix();
                    break;
                case 7:
                    graph->printGraphInfo();
                    break;
                case 8:
                    bfs();
                    break;
                case 9:
                    dfs();
                    break;
                case 10:
                    dijkstra();
                    break;
                case 11:
                    floydWarshall();
                    break;
                case 12:
                    fleury();
                    break;
                case 13:
                    robertFlores();
                    break;
                case 14:
                    closerNeighbor();
                    break;
                case 15:
                    closerNeighborRepetitive();
                    break;
                case 16:
                    cheaperConnection();
                    break;
                case 17:
                    goodman();
                    break;
                case 18:
                    disjointAssemblies();
                    break;
                case 19:
                    kruskal();
                    break;
                case 20:
                    prim();
                    break;
                case 21:
                    sequentialColoring();
                    break;
                case 22:
                    heuristicColoring();
                    break;
                default:
                    writeErr("valor invalido, dgt novamente");
                }
            }
		}
	} while(value != 0);

	destroyGraph();
	writeln("Programa encerrado");
	return 0;

    return 0;
}
