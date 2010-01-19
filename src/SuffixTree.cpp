#include <string>
#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h"
#include "Edge.h"

int Node::Count = 1;

SuffixTree::SuffixTree(string inputText) :
	Text(inputText),
	Length(inputText.length()),
	Active(0, 0, -1)
{
	for (unsigned int i = 0; i <= Length; ++i)
	{
		AddPrefix(Active, i);
	}
}

SuffixTree::~SuffixTree()
{
}

void SuffixTree::AddPrefix(Suffix &active, int lastCharIndex)
{
	int parentNode;
	int lastParentNode = -1;

	Edge tmpEdge;
	for (; ;)
	{
		parentNode = active.originNode;

		if (active.Explicit())
		{
			tmpEdge = Find(Active.originNode, Text[lastCharIndex]);
			if (tmpEdge.startNode != -1)
			{
				break;
			}
		}
		else
		{
			tmpEdge = Find(Active.originNode, Text[Active.firstCharIndex]);
			int span = Active.lastCharIndex - Active.firstCharIndex;

			if (Text[tmpEdge.firstCharIndex + span + 1] == Text[lastCharIndex])
			{
				break;
			}

			parentNode = SplitEdge(Active, tmpEdge);
		}

		Edge *newEdge = new Edge(lastCharIndex, Length, parentNode);
		Insert(*newEdge);

		if (lastParentNode > 0)
		{
			Nodes[lastParentNode].suffixNode = parentNode;
		}

		lastParentNode = parentNode;

		if (Active.originNode == 0)
		{
			Active.firstCharIndex++;
		}
		else
		{
			Active.originNode = Nodes[Active.originNode].suffixNode;
		}

		Active.Canonize();
	}

	if (lastParentNode > 0)
	{
		Nodes[lastParentNode].suffixNode = parentNode;
	}

	Active.lastCharIndex++;
	Active.Canonize();
}

Edge SuffixTree::Find(int node, int c)
{
	int i = Edge::Hash(node, c);
	for ( ; ; )
	{
		if (Edges[i].startNode == node )
		{
			if (c == Text[Edges[i].firstCharIndex])
			{
				return Edges[i];
			}
		}
		if (Edges[i].startNode == -1)
		{
			return Edges[i];
		}
		i++;
		i	%= 2179;
	}
}

void SuffixTree::Insert(Edge& edge)
{
	int i = Edge::Hash(edge.startNode, Text[edge.firstCharIndex]);
	while (Edges[i].startNode != -1)
	{
		i++;
		i %= 2179;
	}

	Edges[i] = edge;
}

void SuffixTree::Remove(Edge& edge)
{
	int i = Edge::Hash(edge.startNode, Text[edge.firstCharIndex]);

	for (; ;)
	{
		Edges[i].startNode = -1;
		int j = 1;

		for (; ;)
		{
			i++;
			i %= 2179;
			if (Edges[i].startNode == -1)
			{
				return;
			}

			int r = Edge::Hash(Edges[i].startNode, Text[Edges[i].firstCharIndex]);

			if (i >= r && r > j)
			{
				continue;
			}
			if (r > j && i >= r)
			{
				continue;
			}
			if (j > 1 && i >= r)
			{
				continue;
			}

			break;
		}

		Edges[j] = Edges[i];
	}
}

int SuffixTree::SplitEdge(Suffix &suffix, Edge &edge)
{
	Remove(edge);
	Edge *newEdge = new Edge(edge.firstCharIndex,
			edge.firstCharIndex + suffix.lastCharIndex - suffix.firstCharIndex,
			suffix.originNode);
	Insert(*newEdge);

	Nodes[newEdge->endNode].suffixNode = suffix.originNode;
	edge.firstCharIndex += suffix.lastCharIndex - suffix.firstCharIndex + 1;
	edge.startNode = newEdge->endNode;

	Insert(edge);

	return newEdge->endNode;
}
