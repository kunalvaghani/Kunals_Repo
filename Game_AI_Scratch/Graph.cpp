#include "Graph.h"

#include <__msvc_filebuf.hpp>

using namespace std;
Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::OnCreate(std::vector<Node*> nodes_)
{
	// given a list of nodes, initialize a matrix of costs with 0.0
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		//populate the internal map
		if (i != nodes_[i]->getLabel())
		{
			std::cerr << "node with label 'i' not in the 'i' position for " << i << "\n";
			return false;
		}
		node[i] = nodes_[i];

		//set up connections
		cost[i].resize(numNodes);

		for (int j = 0; j < numNodes; j++)
		{
			cost[i][j] = 0.0f;
		}
	}
	return true;
}

int Graph::numNodes()
{
	return node.size();
}

void Graph::addWeightedConnection(Node* fromNode, Node* toNode, float weight)
{
	cost[fromNode->getLabel()][toNode->getLabel()] = weight;
}

void Graph::blockNode(int label) {
	blockedNodes.insert(label);
}

void Graph::unblockNode(int label) {
	blockedNodes.erase(label);
}

bool Graph::isNodeBlocked(int label) const {
	return blockedNodes.find(label) != blockedNodes.end();
}

std::vector<Node*> Graph::neighbours(Node* fromNode) {
	std::vector<Node*> result;
	int from = fromNode->getLabel();
	for (int j = 0; j < numNodes(); j++) {
		// Skip if the node is blocked
		if (cost[from][j] > 0.0f && !isNodeBlocked(j)) {
			result.push_back(getNode(j));
		}
	}
	return result;
}
struct NodeAndPriority
{
	Node* node;
	float priority;

	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		return lhs.priority > rhs.priority;
	}
};
std::vector<Node*> Graph::findPath(Node* startNode, Node* goalNode)
{
	float new_cost;
	float priority;
	Node* currentNode = startNode;

	// frontier
	priority_queue<NodeAndPriority, deque<NodeAndPriority>, NodeAndPriority> frontier;
	frontier.push(NodeAndPriority{ currentNode, 0.0f });

	// track solution path
	std::vector<int> came_from;
	came_from.resize(numNodes(), -1);

	// cost_so_far storage
	map<int, float> cost_so_far;
	int start = startNode->getLabel();
	cost_so_far[start] = 0.0f;

	// loop through the frontier while it's not empty
	while (!frontier.empty())
	{
		currentNode = frontier.top().node;
		frontier.pop();

		// if it was the goal node, break out of the loop
		if (currentNode == goalNode)
			break;

		//neighbors of the current node
		for (Node* neighbor : neighbours(currentNode))
		{
			// calculate new cost
			new_cost = cost_so_far[currentNode->getLabel()] + cost[currentNode->getLabel()][neighbor->getLabel()];

			// if neighbor is not a index in costsofar or newcost is lower
			if (cost_so_far.find(neighbor->getLabel()) == cost_so_far.end() || new_cost < cost_so_far[neighbor->getLabel()])
			{
				// found a better path
				cost_so_far[neighbor->getLabel()] = new_cost;
				priority = new_cost;
				frontier.push(NodeAndPriority{ neighbor, priority });
				came_from[neighbor->getLabel()] = currentNode->getLabel();
			}
		}
	}
	//follow the breadcrumbs in came_from to produce path
		std::vector<Node*> path = {};
		int current = goalNode->getLabel();
		while (current != -1)
		{
			path.push_back(getNode(current));
			current = came_from[current];
		}
		reverse(path.begin(), path.end());
		return path;
}
