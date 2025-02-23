#ifndef DECISION_TREE_NODE_H
#define DECISION_TREE_NODE_H

class DecisionTreeNode
{
public:
	virtual DecisionTreeNode* makeDecision() = 0;
};

#endif
