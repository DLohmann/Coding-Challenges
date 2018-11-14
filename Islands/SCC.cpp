#ifndef SCC_h
#define SCC_h

#define scc_debug

#include <iostream>
#include <stdio.h>
#include <climits>	// has integer's INT_MAX
#include <algorithm>	// has sort()
//#include <map>	// has hashmap
#include <vector>

using namespace std;

struct node {
	int startTime;
	int finishTime;
	int distance;
	int previous;
	int color;	// white == 0, grey == 1, black == 2
};

//void StronglyConnectedComponents (int numEdges, int graph [][]);

int timeState = 0;
int numVertices;
int numEdges;
int * G;	// pointer to graph
//int * T;	// pointer to transpose of graph
int lowestSubComponent;	// pointer to array of [numVertex] elements. Each index holds the lowest
int * SCCMin = NULL;
node * vertices;
int * stack;	// points to stack of vertices in order of their discovery
int top = 0;	// top of the stack how many elements it holds. size
vector<int> sccVect;

void DfsVisit (int u) {
	//printf ("Visiting %d\n", u);

	if (SCCMin != NULL) {	// this if statement only runs when DfsVisit is called the second time, on the transpose graph
		lowestSubComponent = min(u, lowestSubComponent);
	}

	//printf ("%d\n", min(u, lowestSubComponent));
	timeState ++;
	vertices[u].distance = timeState;
	vertices[u].color = 1;
	for (int v= 0; v < numVertices; v++) {
		if (G[(u * numVertices) + v] == 1 && vertices[v].color == 0) {
				//printf("expanding %d\n", v);
				vertices [v].previous = u;
				DfsVisit (v);

		}
	}
	vertices [u].color = 2;
	// add to stack
	if (SCCMin != NULL) {
		SCCMin [u] = lowestSubComponent;
		sccVect.push_back(lowestSubComponent);
	}
	stack[top] = u;
	top++;

	timeState++;
	vertices[u].finishTime = timeState;
}

/*
int main() {
	scanf ("%d", &numVertices);
	scanf ("%d", &numEdges);
    
    #ifdef scc_debug
	printf ("numEdges: %d, numVertices: %d\n", numEdges, numVertices);
    #endif
    
	// initialize the graph to all 0's
	int graph [numVertices][numVertices];
	int graphTranspose [numVertices][numVertices];
	int stackMem [numVertices];
	stack = (int *)&stackMem;
	G = (int*)&graph;
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			graph[i][j] = 0;
			graphTranspose[i][j] = 0;
		}
	}
	// insert the vertices in the graph


	for (int i = 0; i < numEdges; i++) {
		//printf("Enter edge %d: ", i);
		int from;
		int to;
		scanf ("%d", &from);
		scanf ("%d", &to);
		graph[from][to] = 1;
		graphTranspose[to][from] = 1;
	}

	node nodes [numVertices];
	vertices = nodes;

	// Call DFS to compute finish times
	for (int i = 0; i < numVertices; i++) {
		vertices[i].startTime = -1;
		vertices[i].finishTime = -1;
		vertices[i].distance = -1;
		vertices[i].previous = -1;
		vertices[i].color = 0;
	}


	for (int i = 0; i < numVertices; i++) {
		if (vertices[i].color == 0) {
			DfsVisit (i);
		}
	}


	// call strongly connected components
	//StronglyConnectedComponents (numEdges, &graph);



	// Printing graph, transpose, and vertice info
	#ifdef scc_debug
	printf ("Graph is:\n");
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			printf ("%d ", G[(i * numVertices) + j]);
		}
		printf ("\n");
	}
	#endif
	G = (int *)graphTranspose;
	
    #ifdef scc_debug
	printf ("Transpose Graph is:\n");
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			printf ("%d ", G[(i * numVertices) + j]);
		}
		printf ("\n");
	}
	printf ("Vertices info is:\n");
	for (int i = 0; i < numVertices; i++) {
		printf ("vertice[%d] = {start = %d, finish = %d, distance = %d, prev = %d, color = %d}\n", i, vertices[i].startTime, vertices[i].finishTime, vertices[i].distance, vertices[i].previous, vertices[i].color);
	}
	#endif

	// Now reset colors
	for (int i = 0; i < numVertices; i++) {
		vertices[i].color = 0;
	}





	// call DFS again on transpose???
	//sort (G, G + top);
	//for (int i = 0; i < numVertices; i++) {
	int lowestSCC [numVertices];
	SCCMin = (int *)lowestSCC;
	//printf ("SCCMin == %p\n", SCCMin);
	while (top > 0) {
		top--;
		if (vertices[stack[top]].color == 0) {
			//printf ("Strongly Connected Component:\n");
			lowestSubComponent = INT_MAX;
			sccVect.clear();
			DfsVisit(stack[top]);
			int min = *min_element(sccVect.begin(), sccVect.end());
			for (std::vector<int>::iterator comp = sccVect.begin(); comp != sccVect.end(); comp++) {
				lowestSCC[*comp] = min;
			}
		}

	}

	for (int i = 0; i < numVertices; i++) {
		printf ("%d\n", lowestSCC[i]);
	}

	
	// while (top > 0) {
		// top --;
		// printf ("Strongly Connected Component:\n");
		// if (vertices[stack[top]].color == 0) {
			// DfsVisit(stack[top]);
		// }
	// }
	




	return 0;
}
*/


#endif
