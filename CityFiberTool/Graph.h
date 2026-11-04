#pragma once
#include "CityFiberTool.h" 

// 图的边结构体
struct Edge {
    int destIndex;
    double weight;
    Edge* next;
};

// 图的顶点结构体
struct Vertex {
    city data;      
    Edge* firstEdge;
};

// 图类
class Graph {
private:
    Vertex* vertices;
    int vertexCount;

public:
    Graph(int n);
    ~Graph();
    void addEdge(int u, int v, double w);
    void buildFromList(DoublyLinkedList& list);
    void printGraph();
};


