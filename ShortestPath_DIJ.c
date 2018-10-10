/*
	@brief:迪杰斯特拉最短路径
	@author:WavenZ
	@time:2018/10/9
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MGraph.h"

typedef struct {
	int Length[MAX_VERTEX_NUM];//路径长度
	int Shortest[MAX_VERTEX_NUM];//标记路径长度是否是最短路径
	int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//路径存储矩阵
}ShortPath;


int Dmin(ShortPath *D, int num, int *min) {
	int index=-1;
	*min=INFINITY;
	for (int i = 0; i < num; ++i) {
		if (D->Shortest[i]==0&&D->Length[i]<*min) {
			*min = D->Length[i];
			index = i;
		}
	}
	if (index != -1) D->Shortest[index] = 1;
	return index;
}


void ShortestPath_DIJ(MGraph *G, int v0,ShortPath *D) {
	int min;
	int v;
	for (v=0; v < G->vexnum; ++v) {
		D->Shortest[v] = 0;//初始化标记
		D->Length[v] = G->arcs[v0][v].adj;//初始化路径长度
		for (int w = 0; w < G->vexnum; ++w) {
			D->PathMatrix[v][w] = 0;//初始化最短路径
		}
		if (D->Length[v] < INFINITY) {
			D->PathMatrix[v][v0] = 1;
			D->PathMatrix[v][v] = 1;
		}
	}
	D->Length[v0] = 0;
	D->Shortest[v0] = 1;
	for (int i = 1; i < G->vexnum; ++i) {
		//if (v = Dmin(D, G->vexnum, &min) == -1) break;
		v = Dmin(D, G->vexnum, &min);
		if (v == -1) break;
		for (int j = 0; j < G->vexnum; ++j) {
			if (!D->Shortest[j] && (G->arcs[v][j].adj + min < D->Length[j])) {
				D->Length[j] = G->arcs[v][j].adj + min;
				D->PathMatrix[j][v] = 1;
			}
		}
	}
}
void printLength(MGraph *G, ShortPath *D, int v0) {
	for (int i = 0; i < G->vexnum; ++i) {
		printf("%c --> %c : %d\n", G->vexs[v0], G->vexs[i], D->Length[i]);
	}
	 
}
int main(int argc, char *argv[]) {
	MGraph G;
	ShortPath D;
	CreateMGraph(&G);
	ShortestPath_DIJ(&G, 0, &D);
	printLength(&G, &D, 0);
	system("pause");
	return 1;
}