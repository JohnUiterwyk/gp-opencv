/*
 * LoggingNode.h
 *
 *  Created on: 19/08/2013
 *      Author: james
 */

#ifndef LOGGINGNODE_H_
#define LOGGINGNODE_H_

#include "Node.h"
#include <iostream>

class LoggingNode : public Node
{
public:
	LoggingNode(GPConfig* conf, Node* node);
	virtual ~LoggingNode();

	virtual void evaluate(ReturnData *out);
	static LoggingNode* Wrap(GPConfig* conf, Node* node);

    virtual void addToVector(vector<Node *> &vec);
    virtual int computeSize() ;
    virtual int computeDepth(int curDepth) ;
    virtual void addToVector(vector<Node *> &vec, int typeNum) ;
    virtual void print(string &s) ;
    virtual Node* copy() ;


	Node* baseNode;

	static int depth;

};

#endif /* LOGGINGNODE_H_ */
