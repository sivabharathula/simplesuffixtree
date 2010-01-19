#include "Edge.h"
#include "Node.h"

Edge::Edge()
{
	startNode = -1;
}

Edge::Edge(int initialFirstCharIndex,
		int initialLastCharIndex,
		int parentNode)
{
	firstCharIndex = initialFirstCharIndex;
	lastCharIndex = initialLastCharIndex;
	startNode = parentNode;
	endNode = Node::Count++;
}

