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
