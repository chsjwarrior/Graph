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
#include <fstream>

Graph* graph;

inline void destroyGraph() {
	delete graph;
	graph = nullptr;
}

void openFile(const char* path) {
	std::ifstream file(path, std::ios::in);
	if (file.is_open()) {
		bool fail = false;
		unsigned int u, v, line = 1;
		int w;
		file >> u >> v >> w;
		destroyGraph();
		try {
			graph = new Graph(u, w != 0);

			while (fail == false && file >> u && file >> v && file >> w) {
				++line;
				graph->insertEdge(--u, --v, w);
			}
		} catch (std::length_error& e) {
			std::cerr << e.what() << std::endl;
			fail = true;
		} catch (std::range_error& e) {
			std::cerr << "Erro na linha " << line << ' ' << e.what() << std::endl;
			fail = true;
		}
		file.close();
		if (fail)
			destroyGraph();
	} else
		std::cerr << "Nao foi possivel abrir o arquivo." << std::endl;
}

inline void clearCin() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T>
T read() requires std::integral<T> {
	T value = NULL;
	std::cin >> value;
	while (std::cin.fail()) {
		clearCin();
		std::cin >> value;
	}
	return value;
}

void createGraph() {
	unsigned int u, v;
	std::cout << "Dgt a qtd de Vertices." << std::endl;
	u = read<unsigned int>();
	std::cout << "[1] Grafo dirigido.\nDgt outro valor: Grafo nao dirigido." << std::endl;
	int w = read<signed int>();
	destroyGraph();
	try {
		graph = new Graph(u, w == 1);
	} catch (std::length_error& e) {
		std::cerr << e.what() << std::endl;
		return;
	}
	std::cout << "[1] Grafo valorado.\nDgt outro valor: Grafo nao valorado." << std::endl;
	w = read<signed int>();
	u = v = NIL;
	do {
		graph->printVerticesToSelect();
		std::cout << "Selecione o numero do primeiro vertice ou 0 para retornar:" << std::endl;
		u = read<unsigned int>();
		if (u != 0 && graph->isValidVertex(u - 1)) {
			std::cout << "Selecione o segundo vertice ou 0 para cancelar:" << std::endl;
			v = read<unsigned int>();
			if (v != 0 && graph->isValidVertex(v - 1)) {
				if (w == 1) {// se grafo valorado
					std::cout << "Dgt o custo da Aresta:" << std::endl;
					w = read<signed int>();
					if (graph->isValidWeight(w))
						graph->insertEdge(u - 1, v - 1, w);
					w = 1;
				} else
					graph->insertEdge(u - 1, v - 1);
			} else
				std::cerr << "vertice v deve ser menor que " << graph->AMOUNT_VERTEXES << std::endl;
		} else
			std::cerr << "vertice u deve ser menor que " << graph->AMOUNT_VERTEXES << std::endl;
	} while (v != 0 && u != 0);
}

unsigned int getVertex(const char msg[]) {
	unsigned int value = NIL;
	do {
		graph->printVerticesToSelect();
		std::cout << msg << std::endl;
		value = read<unsigned int>();
	} while (value > graph->AMOUNT_VERTEXES || value < 1);
	return --value;
}

void clearScreen() {
#ifdef _WIN32
	system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
	system("clear");
#else
#error "OS not supported."
#endif
}

int main() {
	system("COLOR 1F");
	std::cout << "Desenvolvido por Carlos Henrique Stapait Junior." << std::endl;
	graph = nullptr;
	unsigned int choice = 0;

	do {
		std::cout << "[0] encerrar." << std::endl
			<< "[1] criar um grafo." << std::endl
			<< "[2] abrir um arquivo." << std::endl;
		if (graph != nullptr)
			std::cout << std::endl
			<< "[3] imprimir Matriz de adjacencia." << std::endl
			<< "[4] imprimir Matriz de incidencia." << std::endl
			<< "[5] imprimir lista de adjacencia." << std::endl
			<< "[6] imprimir lista de incidencia." << std::endl
			<< "[7] imprimir Matriz de custo." << std::endl
			<< "[8] imprimir Informacoes do grafo." << std::endl
			<< "---------------caminhamento---------------" << std::endl
			<< "[9] Busca em largura." << std::endl
			<< "[10] Busca em profundidade." << std::endl
			<< "--------------menor caminho---------------" << std::endl
			<< "[11] Dijkstra." << std::endl
			<< "[12] Floyd Warshall." << std::endl
			<< "[13] Bellman-Ford." << std::endl
			<< "[14] Fleury." << std::endl
			<< "[15] Hierholzer." << std::endl
			<< "[16] Robert Flores." << std::endl
			<< "[17] Vizinho mais proximo." << std::endl
			<< "[18] Ligacao mais economica." << std::endl
			<< "--------------fluxo em rede---------------" << std::endl
			<< "[19] Ford-Fulkerson." << std::endl
			<< "---------------conexidade-----------------" << std::endl
			<< "[20] Goodman." << std::endl
			<< "[21] Conjuntos disjuntos." << std::endl
			<< "[22] Kosaraju." << std::endl
			<< "[23] Tarjan." << std::endl
			<< "----------arvore geradora minima----------" << std::endl
			<< "[24] Kruskal." << std::endl
			<< "[25] Prim." << std::endl
			<< "[26] Boruvka," << std::endl
			<< "------------------------------------------" << std::endl
			<< "[27] Coloracao." << std::endl;
		choice = read<unsigned int>();
		clearScreen();

		if (choice == 1)
			createGraph();
		else if (choice == 2)
			openFile("graph.txt");
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
				std::cout << "[0] busca iterativa.\nDgt qualquer valor para busca recursiva." << std::endl;
				bool isRecursive = read<unsigned int>();
				BreadthFirstSearch bfs(*graph);
				bfs.bfs(getVertex("Dgt o numero do vertice de origem."), isRecursive);
			} break;
			case 10:
			{
				std::cout << "[0] busca iterativa.\nDgt qualquer valor para busca recursiva." << std::endl;
				bool isRecursive = read<unsigned int>();
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
				} catch (std::invalid_argument& e) {
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
				std::cout << "[0] busca iterativa.\nDgt qualquer valor para busca recursiva." << std::endl;
				bool isRecursive = read<unsigned int>();
				RobertFlores robertFlores(*graph);
				robertFlores.robertFlores(getVertex("Dgt o numero do vertice de origem."), isRecursive);
			} break;
			case 17:
			{
				std::cout << "[0] Vizinha mais proximo.\nDgt qualquer valor para Vizinho mais proximo repetivo." << std::endl;
				bool isRepetitive = read<unsigned int>();
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
				} catch (std::invalid_argument& e) {
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
				} catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
				}
			} break;
			case 20:
			{
				try {
					Goodman goodman(*graph);
					goodman.goodman();
				} catch (std::invalid_argument& e) {
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
				} catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
				}
			} break;
			case 23:
			{
				try {
					Tarjan tarjan(*graph);
					tarjan.tarjan();
				} catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
				}
			} break;
			case 24:
			{
				try {
					Kruskal kruskal(*graph);
					kruskal.kruskal();
				} catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
				}
			} break;
			case 25:
			{
				try {
					Prim prim(*graph);
					prim.prim(getVertex("Dgt o numero do vertice de origem."));
				} catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
				}
			} break;
			case 26:
			{
				try {
					Boruvka boruvka(*graph);
					boruvka.boruvka();
				} catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
				}
			} break;
			case 27:
			{
				std::cout << "[0] Coloracao sequencial.\nDgt qualquer valor para Coloracao heuristica." << std::endl;
				bool isHeuristic = read<unsigned int>();
				Coloring coloring(*graph);
				coloring.coloring(isHeuristic);
			} break;
			default:
				std::cerr << "valor invalido." << std::endl;
			}
			std::cout << "pressione qualquer tecla para continuar..." << std::flush;
			std::cin.get();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clearScreen();
		}
	} while (choice != 0);

	destroyGraph();
	std::cout << "Programa encerrado." << std::endl;
	return 0;
}