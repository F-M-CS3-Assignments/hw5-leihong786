#include "Graph.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <set>

using namespace std;

// Returns existing edge from gnFrom to gnTo if found in adjList.
const GraphEdge* findExistingEdge(nodekey_t gnFrom, nodekey_t gnTo, vector<vector<GraphEdge *>> adjList) {
    if (adjList.size() == 0) return nullptr;
    for (size_t rowIDX = 0; rowIDX < adjList.size(); rowIDX++) {
        vector<GraphEdge*> row = adjList.at(rowIDX);
        for (size_t i = 0; i < row.size(); i++) {
            GraphEdge* cur = row.at(i);
            if (cur->from == gnFrom && cur->to == gnTo) {
                return cur;
            }
        }
    }
    return nullptr;
}

// Returns string representation of a GraphEdge.
string GraphEdgeToString(const GraphEdge* e) {
    return "((" + to_string(e->from) + ")->(" + to_string(e->to) + ") w:" + to_string(e->weight) + ")";
}

// Adds a new node to the graph if it doesn't already exist.
void Graph::AddNode(nodekey_t key) {
    if (this->IsPresent(key)) {
        throw invalid_argument("Duplicate node cannot be added: " + to_string(key));
    }
    nodes.push_back(key);
    adjList.push_back(vector<GraphEdge*>());
}

// Adds a new directed edge from gnFrom to gnTo with given weight.
const GraphEdge* Graph::AddEdge(nodekey_t gnFrom, nodekey_t gnTo, unsigned int w) {
    const GraphEdge* dup = findExistingEdge(gnFrom, gnTo, this->adjList);
    if (dup != nullptr) {
        throw invalid_argument("Duplicate edge cannot be added: " + GraphEdgeToString(dup));
    }
    if (!this->IsPresent(gnFrom) || !this->IsPresent(gnTo)) {
        throw invalid_argument("Invalid node key in edge: (" + to_string(gnFrom) + "->" + to_string(gnTo) + ")");
    }

    size_t idxFrom = 0;
    while (nodes[idxFrom] != gnFrom) idxFrom++;

    GraphEdge* ge = new GraphEdge();
    ge->from = gnFrom;
    ge->to = gnTo;
    ge->weight = w;

    adjList.at(idxFrom).push_back(ge);
    return ge;
}

// Returns true if node with key exists in the graph.
bool Graph::IsPresent(nodekey_t key) const {
    for (nodekey_t n : nodes) {
        if (n == key) return true;
    }
    return false;
}

// Returns set of all outgoing edges from a given node.
set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t node) const {
    size_t idx = 0;
    while (idx < nodes.size() && nodes[idx] != node) {
        idx++;
    }
    if (idx == nodes.size()) {
        throw invalid_argument("No such node: " + to_string(node));
    }

    set<const GraphEdge*> result;
    for (GraphEdge* edge : adjList[idx]) {
        if (edge->from == node) {
            result.insert(edge);
        }
    }

    return result;
}

// Returns a set of all node keys in the graph.
set<nodekey_t> Graph::GetNodes() const {
    return set<nodekey_t>(nodes.begin(), nodes.end());
}

// Returns the number of nodes in the graph.
size_t Graph::Order() const {
    return nodes.size();
}

// Returns the total number of edges in the graph.
size_t Graph::Size() const {
    size_t total = 0;
    for (const auto& row : adjList) {
        total += row.size();
    }
    return total;
}

// Returns string version of all nodes.
string Graph::NodesToString() const {
    if (nodes.empty()) return "[]";

    string str = "[";
    for (size_t i = 0; i < nodes.size(); i++) {
        str += "(" + to_string(nodes[i]) + ")";
        if (i != nodes.size() - 1) str += ", ";
    }
    return str + "]";
}

// Returns string version of all edges.
string Graph::EdgesToString() const {
    if (adjList.empty()) return "[]";

    string str = "[";
    size_t count = 0;
    size_t total = Size();

    for (const auto& row : adjList) {
        for (const GraphEdge* e : row) {
            str += GraphEdgeToString(e);
            if (++count < total) str += ", ";
        }
    }

    return str + "]";
}

// Frees all dynamically allocated GraphEdge objects.
Graph::~Graph() {
    for (auto& row : adjList) {
        for (GraphEdge* edge : row) {
            delete edge;
        }
        row.clear();
    }
    adjList.clear();
    nodes.clear();
}
