#include <string.h>
#include <iostream>
using namespace std;
struct city {
	string cityname;
	double lon;
	double lat;
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
	~DoublyLinkedList(); //结束

	void insertcity(city c); //插入城市
	bool deletecity(string cityname); //删除城市
	cityNode* findcity(string cityname); //查找城市
	//其他功能
	void printList();
	void sortByDistance();

};
