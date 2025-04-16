#include "Dijkstra.h"
#include "Graph.h"
#include "BetterPriorityQueue.h"

using namespace std;

int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    set<nodekey_t> nodes = g->GetNodes();
    BetterPriorityQueue prioQ;
    // pushes all nodes into prioQ, making the start node have prio 0
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        BPQNode bNode;
        bNode.gnode = *it;
        if (*it == start) {
            bNode.pri = 0;
        } else {
            bNode.pri = INT16_MAX;
        }
        bNode.visited = false;
        prioQ.push(bNode);
    }
    // loops through prioQ and pops the top
    while (!prioQ.empty()) {
        BPQNode temp = prioQ.top();
        if (temp.gnode == end) {
            return temp.pri;
        }
        prioQ.pop();
        if (!temp.visited) {
            temp.visited = false;
        }
        prioQ.Update(temp);
        // checks for neighbors coming from the top node and updates their value in prioQ if they exist, returning the end node pri if found
        set<const GraphEdge*> graphE = g->GetOutwardEdgesFrom((temp).gnode);
        for (auto it = graphE.begin(); it != graphE.end(); it++) {
            BPQNode bNode;
            bNode.gnode = (*it)->to;
            bNode.pri = (*it)->weight + temp.pri;
            if (prioQ.Contains(bNode)) {
                bNode.visited = true;
            } else {
                bNode.visited = false;
            }
            prioQ.Update(bNode);
        }
    }
    return -1;
}