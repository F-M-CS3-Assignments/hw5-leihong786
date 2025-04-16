#ifndef BETTERPRIORITYQUEUE_H
#define BETTERPRIORITYQUEUE_H

#include <iostream>
#include <set>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

#define nodekey_t unsigned long long int
#define INVALID_NODE_KEY ULLONG_MAX

struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;
	
	bool operator<(const BPQNode &other) const {
		return pri < other.pri;
	}

	bool operator>(const BPQNode &other) const {
		return pri > other.pri;
	}
	
	bool operator==(const BPQNode &other) const {
		return this->gnode == other.gnode;
	}
};

class BetterPriorityQueue: public priority_queue<BPQNode, vector<BPQNode>, greater<BPQNode>>::priority_queue {
    public: 
		~BetterPriorityQueue();

    	bool Contains(BPQNode key);
    	bool Update(BPQNode key);

    	string ToString();
    	static string BPQNodeToString(BPQNode input); //make static
};

#endif