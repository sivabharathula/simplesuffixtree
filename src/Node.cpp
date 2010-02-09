#include "Node.h"

const int Node::EMPTY = -1;

Node::Node() :
	d_suffixNode(EMPTY)
{
}

Node::Node(int node) :
	d_suffixNode(node)
{
}

int Node::getSuffixNode() const
{
	return d_suffixNode;
}
void Node::setSuffixNode(int suffixNode)
{
	d_suffixNode = suffixNode;
}
