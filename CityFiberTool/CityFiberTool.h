#include <string>
#include <iostream>
#pragma once
using namespace std;
struct city {
	string cityname;
	double lon;
	double lat;
	double dist = 0.0;
};

struct cityNode {
	city data;
	cityNode* next;
	cityNode* prev;
};

class DoublyLinkedList {
private :
	cityNode* head;
	int size;  //城市数量

public:
	DoublyLinkedList();//构造空链表
	~DoublyLinkedList(); //结束，删除链表释放内存

	void insertCity(city c); //插入城市
	bool deleteCity(string cityname); //删除城市
	cityNode* findCity(string cityname); //查找城市
	int getSize() { return size; } //获取城市数量
	//其他功能
	void printList();//打印所有城市的数据
	void sortByDistance();
	void loadFromFile(string filename);//读取文件中的城市数据
	double calcDistance(city a, city b);//计算两城市之间的距离		
	void exportToArray(city* arr); //将链表中的城市数据导出到数组中
};
