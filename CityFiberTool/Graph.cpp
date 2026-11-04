#include "Graph.h";
#include "CityFiberTool.h"
#include <iostream>
using namespace std;


// 构造函数，初始化图的顶点数组
Graph::Graph(int n) {
    vertexCount = n;
    vertices = new Vertex[n];
    for (int i = 0; i < n; i++) {
        vertices[i].firstEdge = nullptr;
    }
}

// 析构函数：清理内存
Graph::~Graph() {
    for (int i = 0; i < vertexCount; i++) {
        Edge* cur = vertices[i].firstEdge;
        while (cur != nullptr) {
            Edge* temp = cur;
            cur = cur->next;
            delete temp; // 挨个把边删掉
        }
    }
    delete[] vertices; // 把顶点数组也删掉
}

//添加边
void Graph::addEdge(int u, int v, double w) {
    // 无向图 u 到 v 有路，v 到 u 也就有路。所以要插两条边。

    // 第一步：把 v 插到 u 的边链表里
    Edge* e1 = new Edge;
    e1->destIndex = v;
    e1->weight = w;
    e1->next = vertices[u].firstEdge; 
    vertices[u].firstEdge = e1;       

    // 第二步：把 u 插到 v 的边链表里
    Edge* e2 = new Edge;
    e2->destIndex = u;
    e2->weight = w;
    e2->next = vertices[v].firstEdge;
    vertices[v].firstEdge = e2;
}

//建图
void Graph::buildFromList(DoublyLinkedList& list) {
    //先把链表里的城市数据倒进一个临时数组
    city* tempArray = new city[vertexCount];
    list.exportToArray(tempArray);

    //把临时数组里的城市，塞进图的顶点数组里
    for (int i = 0; i < vertexCount; i++) {
        vertices[i].data = tempArray[i];
    }
	delete[] tempArray; //释放临时数组内存

    //双重循环计算任意两城距离
    for (int i = 0; i < vertexCount; i++) {
        // j 从 i+1 开始，避免重复计算自己和自己，也避免 A 连 B 后 B 又连 A
        for (int j = i + 1; j < vertexCount; j++) { 
            double dist = list.calcDistance(vertices[i].data, vertices[j].data);
            addEdge(i, j, dist);
        }
    }
}

//打印完整的邻接表结构
void Graph::printGraph() {
    cout << "========== 图 的 邻 接 表 结 构 ==========" << endl;
    for (int i = 0; i < vertexCount; i++) {
        cout << vertices[i].data.cityname << " -> ";

        Edge* cur = vertices[i].firstEdge;
        while (cur != nullptr) {
            // 打印：目标城市名(权重)
            cout << vertices[cur->destIndex].data.cityname
                << "(" << cur->weight << ") -> ";
            cur = cur->next;
        }
        cout << "NULL" << endl; // 链表结束
    }
    cout << "==========================================" << endl;
}



