#include "Decision.h"

DecisionTreeNode* Decision::getBranch()
{
	if (testValue())
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
}

DecisionTreeNode* Decision::makeDecision()
{
	DecisionTreeNode* branch = getBranch();
	return branch->makeDecision();
}
