#include <iostream>
#include <set>
#include <climits>
#include <vector>
using namespace std;

#include "BetterPriorityQueue.h"

BetterPriorityQueue::~BetterPriorityQueue() {
}

bool BetterPriorityQueue::Contains(BPQNode key) {
    for (unsigned int i = 0; i < c.size(); i++) {
        if (c[i] == key) {
            return true;
        }
    }
    return false;
}

// loops through the underlying vector and if exists and key pri is lesser, then delete old value in vec and push key in
bool BetterPriorityQueue::Update(BPQNode key) {
    for (unsigned int i = 0; i < c.size(); i++) {
        if (c[i] == key) {
            if (key < c[i]) {
                c.erase(c.begin() + i);
                push(key);
                return true;
            }
        }
    }
    return false;
}

string BetterPriorityQueue::ToString() {
    string str = "[";
    for (unsigned int i = 0; i < c.size(); i++) {
        if (i != 0) {
            str += ", ";
        }
        str += BPQNodeToString(c[i]);
    }
    str += "]";
    return str;
}

string BetterPriorityQueue::BPQNodeToString(BPQNode input) {
    return "(" + to_string(input.gnode) + ", pri: " + to_string(input.pri) + ")";
}