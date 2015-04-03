/*
 * LoggingNode.cpp
 *
 *  Created on: 19/08/2013
 *      Author: james
 */

#include <iostream>
#include <fstream>
#include <typeinfo>
#include "LoggingNode.h"
#include "Function.h"
#include "CVDebug.h"
#include "ReturnDouble.h"
#include "ReturnImage.h"
#include "ReturnUnit.h"
int LoggingNode::depth = 0;

LoggingNode::LoggingNode(GPConfig* conf, Node* node) : Node(node->getReturnType(), node->getMaxArgs(), "log", conf ) {

	baseNode = node;
}

LoggingNode::~LoggingNode() {

}

LoggingNode* LoggingNode::Wrap(GPConfig* conf, Node* node)
{
	LoggingNode* result = new LoggingNode(conf, node);

	Function* func=dynamic_cast<Function*>(node);
	if(func!=NULL)
	{
		for(int i=0;i<func->getMaxArgs();i++)
		{
			func->setArgN(i, Wrap(conf, func->getArgN(i)));
		}
	}
	return result;
}

void LoggingNode::addToVector(vector<Node *> &vec)
{

}


void LoggingNode::evaluate(ReturnData *out) {
	depth++;
	baseNode->evaluate(out);
	depth--;

	for (int i = 0; i < depth; i++)
		CVDebug::logstream << "    ";

	CVDebug::logstream << typeid(*baseNode).name() << " = ";

	ReturnDouble* rdbl = dynamic_cast<ReturnDouble*>(out);
	if (rdbl != NULL) {
		CVDebug::logstream << rdbl->getData();
	} else {
		ReturnUnit* runit = dynamic_cast<ReturnUnit*>(out);
		if (runit != NULL) {
			CVDebug::logstream << runit->getData();
		} else {
			ReturnImage* rimg = dynamic_cast<ReturnImage*>(out);
			if (rimg != NULL) {

				Mat img = rimg->getData();

				string fname=CVDebug::logImage(typeid(*baseNode).name(), img);
				CVDebug::logstream << "image " << img.cols << "x" << img.rows << " " << fname;
			}
			else
			{
				CVDebug::logstream << "unknown";
			}
		}
	}
	CVDebug::logstream << endl;
}

int LoggingNode::computeSize() { return 0;}
int LoggingNode::computeDepth(int curDepth) {return 0;}
void LoggingNode::addToVector(vector<Node *> &vec, int typeNum) {}
void LoggingNode::print(string &s) {}
Node* LoggingNode::copy() {return NULL;}
