#ifndef DECISION_H
#define DECISION_H

#include "DecisionTreeNode.h"
#include "Action.h"

class Decision :
    public DecisionTreeNode
{
protected:
    DecisionTreeNode* trueNode;
    DecisionTreeNode* falseNode;
    class Character* owner;

public:
    //this default constructor should never be called
    Decision() : trueNode{ nullptr }, falseNode{ nullptr }, owner{ nullptr }
    {}

    Decision(DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_, Character* owner_) :
        trueNode{ trueNode_ },
        falseNode{ falseNode_ },
        owner{ owner_ }
    {}

    virtual bool testValue() = 0;
    virtual DecisionTreeNode* getBranch();
    virtual DecisionTreeNode* makeDecision();
};

#endif
