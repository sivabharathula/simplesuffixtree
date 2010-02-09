#include "Edge.h"
#include "Node.h"

Edge::Edge() :
	d_startNode(Node::EMPTY), d_endNode(Node::EMPTY)
{
}

Edge::Edge(int initialFirstCharIndex, int initialLastCharIndex, int parentNode,
		int end_node, char first_char) :
		d_firstCharIndex(initialFirstCharIndex)
		,d_lastCharIndex(initialLastCharIndex)
		,d_startNode(parentNode)
		,d_endNode(end_node)
		,d_firstChar(first_char)
{
}

int Edge::Hash(int node, int c)
{
	return ((node << 8) + c) % 2179;
}

Edge& Edge::operator=(const Edge& value)
{
	assert(false);
	return *this;
}

