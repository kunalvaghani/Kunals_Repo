#ifndef GRAPH_H
#define GRAPH_H

/// DO NOT USE THIS OUTSIDE THIS COURSE

#include <vector>
#include <map>
#include "Node.h"
#include <set>
#include <iostream>
#include <queue>

class Graph
{
private:
	// a list of the nodes
	std::map<int, Node*> node;	
	std::set<int> blockedNodes;

	// a 2D matrix of the connection costs/weights
	std::vector< std::vector< float > > cost;

public:
	Graph();
	~Graph();
	bool OnCreate(std::vector< Node* > nodes_);
	int numNodes();
	Node* getNode(int label) { return node[label]; }
	void addWeightedConnection(Node* fromNode, Node* toNode, float weight);
	std::vector<Node*> neighbours(Node* fromNode);
	std::vector<Node*> findPath(Node* startNode, Node* goal);
	void blockNode(int label);
	void unblockNode(int label);
	bool isNodeBlocked(int label) const;

};

#endif
