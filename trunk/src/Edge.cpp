#include "Edge.h"
#include "Node.h"

Edge::Edge():endNode(-1)
{
	startNode = -1;
}
/*Edge::Edge(const Edge& value)
	:firstCharIndex(value.firstCharIndex)
	,lastCharIndex(value.lastCharIndex)
	,startNode(value.startNode)
	,endNode(value.endNode)
	,firstChar(value.firstChar)
{
}*/

Edge::Edge(int initialFirstCharIndex,
		int initialLastCharIndex,
		int parentNode,
		int end_node,
		char first_char)
		:firstChar(first_char)
		 ,endNode(end_node)

	//:endNode(Node::Count++)
{
	firstCharIndex = initialFirstCharIndex;
	lastCharIndex = initialLastCharIndex;
	startNode = parentNode;
}


int Edge::Hash(int node, int c)
{
	return ((node << 8) + c) % 2179;
}
Edge& Edge::operator=(const Edge& value)
{
	this->firstCharIndex = value.firstCharIndex;
	this->lastCharIndex = value.lastCharIndex;
	this->startNode = value.startNode;
	//this->endNode = value.endNode;
	this->firstChar = value.firstChar;
	return *this;
}

int Edge::getFirstCharIndex() const
{
	return firstCharIndex;
}

void Edge::setFirstCharIndex(int firstCharIndex, char c)
{
	this->firstCharIndex = firstCharIndex;
	this->firstChar = c;
}

void Edge::setFirstChar(char c)
{
	firstChar = c;
}
char Edge::getFirstChar() const
{
	return firstChar;
}


