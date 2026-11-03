#include "CityFiberTool.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//构造空链表
DoublyLinkedList::DoublyLinkedList(){
	head = new cityNode;
	head->next = head;
	head->prev = head;
	size = 0;
}

//删除链表释放内存
DoublyLinkedList::~DoublyLinkedList() {
	cityNode* cur = head->next;
	while (cur != head) {
		cityNode* temp = cur;
		cur = cur->next;
		delete temp;
	}
	delete head;
}

//尾插法插入城市节点
void DoublyLinkedList::insertCity(city c) {
	cityNode* newNode = newNode;
	newNode->data = c;
	cityNode* tail = head->prev;
	tail->next = newNode;
	newNode->prev = tail;
	head->prev=newNode;
	newNode->next = head;
	//城市数量+1
	size++;
}

//打印所有城市数据
void DoublyLinkedList::printList() {
	if (size == 0) {
		cout << "城市列表为空" << endl;
		return;
	}
	cout << "----------城市列表如下----------" << endl;
	cityNode* cur = head->next;
	while (cur != head) {
		cout << "城市名称: " << cur->data.cityname << ", 经度: " << cur->data.lon << ", 纬度: " << cur->data.lat << endl;
		cur = cur->next;
	}
	cout << "-------------------------------" << endl;
}

//从文件中加载城市数据
void DoublyLinkedList::loadFromFile(string filename) {
	ifstream file(filename);
	if (!file.is_open()){
		cout << "---------无法打开文件!--------" << endl << "请检查文件位置是否正确！" << endl;
		return;
	}
	string line;
	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		stringstream ss(line);
		city c;
		ss >> c.cityname >> c.lon >> c.lat;
		insertCity(c);
	}
	cout << "---------城市数据加载完成!--------" << endl << "-------------------------------" << endl;
}

//查找城市节点
cityNode* DoublyLinkedList::findCity(string cityname) {
	cityNode* cur = head->next;
	while (cur != head) {
		if (cur->data.cityname == cityname) {
			return cur; 
		}
		cur = cur->next;
	}
	return nullptr; 
}

//删除城市节点
bool DoublyLinkedList::deleteCity( string cityname) {
	cityNode* target = findCity(cityname);
	if (target == nullptr) {
		return false; 
	}

	target->prev->next = target->next;
	target->next->prev = target->prev;

	delete target; 
	size--;
	return true;
}

//计算两个城市间的距离
double DoublyLinkedList::calcDistance(city a, city b) {
	//round四舍五入返回为整数，因此通过先×100的方式使数据存储在round中，然后再整个除以100，达到保留两位小数的效果
	return round(sqrt(pow(a.lon - b.lon, 2) + pow(a.lat - b.lat, 2)) * 100) / 100;
}

// 按距离排序（以第一个城市为基准）
void DoublyLinkedList::sortByDistance() {
	if (size <= 1) return; // 只有0或1个城市，不用排

	city baseCity = head->next->data;
	cityNode* cur = head->next;
	while (cur != head) {
		cur->data.dist = calcDistance(cur->data, baseCity);
		cur = cur->next;
	}

	// 冒泡排序，因为直接动链表太容易导致指针断掉，所以动的是数据
	for (int i = 0; i < size - 1; i++) {
		cityNode* p = head->next;
		for (int j = 0; j < size - 1 - i; j++) {
			if (p->data.dist > p->next->data.dist) {
				// 交换两座城市的数据
				swap(p->data, p->next->data);
			}
			p = p->next;
		}
	}
	cout << "排序完成！" << endl;
}