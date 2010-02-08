#include <string>
#include <iostream>
#include <iomanip>
#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h"
#include "Edge.h"
#include "NullEdge.h"
#include <boost/unordered_map.hpp>

int Node::Count = 1;

SuffixTree::SuffixTree(string inputText) :
	Text(inputText),
	Length(inputText.length()),
	Active(0, 0, -1)
{
	Active.tree = this;
	Node zero_Node;
	zero_Node.suffixNode = 0;
	d_nodes[0] = zero_Node;
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


	for (; ;)
	{
		parentNode = active.originNode;

		if (active.Explicit())
		{
			Edge& tmpEdge = Find(Active.originNode, Text[lastCharIndex]);
			if (tmpEdge.startNode != -1)
			{
				break;
			}
		}
		else
		{
			Edge& tmpEdge = Find(Active.originNode, Text[Active.firstCharIndex]);
			int span = Active.lastCharIndex - Active.firstCharIndex;

			if (Text[tmpEdge.getFirstCharIndex() + span + 1] == Text[lastCharIndex])
			{
				break;
			}

			parentNode = SplitEdge(Active, tmpEdge);
		}

		Edge newEdge(lastCharIndex, Length, parentNode, d_nodes.size(), Text[lastCharIndex]);
		assert(d_nodes.find(d_nodes.size()) == d_nodes.end());
		d_nodes[d_nodes.size()] = Node();
		Insert(newEdge);

		if (lastParentNode > 0)
		{
			d_nodes[lastParentNode].suffixNode = parentNode;
			//Nodes[lastParentNode].suffixNode = parentNode;
		}

		lastParentNode = parentNode;

		if (Active.originNode == 0)
		{
			Active.firstCharIndex++;
		}
		else
		{
			Active.originNode = d_nodes[Active.originNode].suffixNode;
			//Active.originNode = Nodes[Active.originNode].suffixNode;
		}

		Active.Canonize();
	}

	if (lastParentNode > 0)
	{
		d_nodes[lastParentNode].suffixNode = parentNode;
		//Nodes[lastParentNode].suffixNode = parentNode;
	}

	Active.lastCharIndex++;
	Active.Canonize();
}

Edge& SuffixTree::Find(int node, int c)
{

	Edge mockEdge(c, c, node, -1, c);
	EdgeHashSet::const_iterator cit = d_edges.find(mockEdge);
	if (cit == d_edges.end())
	{
		return NullEdge::getNull();
	}
	return const_cast<Edge&>(*cit);

/*
	int i = Edge::Hash(node, c);
	for ( ; ; )
	{
		if (Edges[i].startNode == node )
		{
			if (c == Text[Edges[i].getFirstCharIndex()])
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
*/
}

void SuffixTree::Insert(Edge& edge)
{
	d_edges.insert(edge);
	assert(d_edges.find(edge) != d_edges.end());

/*
	int i = Edge::Hash(edge.startNode, Text[edge.firstCharIndex]);
	while (Edges[i].startNode != -1)
	{
		i++;
		i %= 2179;
	}

	Edges[i] = edge;
*/
}

void SuffixTree::Remove(Edge& edge)
{
	d_edges.erase(edge);
/*
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
*/
}

int SuffixTree::SplitEdge(Suffix &suffix, Edge &edge)
{
	Remove(edge);
	Edge newEdge(edge.getFirstCharIndex(),
			edge.getFirstCharIndex() + suffix.lastCharIndex - suffix.firstCharIndex,
			suffix.originNode, d_nodes.size(), edge.getFirstChar());
	assert(edge.getFirstChar() == Text[edge.getFirstCharIndex()]);
	assert(d_nodes.find(d_nodes.size()) == d_nodes.end());
	d_nodes[(int)d_nodes.size()] = Node();
	Insert(newEdge);

	d_nodes[newEdge.endNode].suffixNode = suffix.originNode;
	//Nodes[newEdge.endNode].suffixNode = suffix.originNode;
	int index = edge.getFirstCharIndex() + suffix.lastCharIndex - suffix.firstCharIndex +1;
	edge.setFirstCharIndex(index, Text[index]);
	//edge.firstCharIndex += suffix.lastCharIndex - suffix.firstCharIndex + 1;
	edge.startNode = newEdge.endNode;

	Insert(edge);

	return newEdge.endNode;
}

void SuffixTree::dump_edges( int current_n )
{
    cout << " Start  End  Suf  First Last  String\n";
    //for ( int j = 0 ; j < 2179 ; j++ ) {
    //    Edge *s = Edges + j;
    for(EdgeHashSet::const_iterator cit = d_edges.begin(); cit != d_edges.end();++cit)
    {
    	const Edge* s = &(*cit);
        if ( s->startNode == -1 )
            continue;
        std::cout << std::setw( 5 ) << s->startNode << " "
             << std::setw( 5 ) << s->endNode << " "
             << std::setw( 3 ) << d_nodes[ s->endNode ].suffixNode << " "
             << std::setw( 5 ) << s->getFirstCharIndex() << " "
             << std::setw( 6 ) << s->lastCharIndex << "  ";
        int top;
        if ( current_n > s->lastCharIndex )
            top = s->lastCharIndex;
        else
            top = current_n;
        for ( int l = s->getFirstCharIndex() ;
                  l <= top;
                  l++ )
            cout << Text[ l ];
        cout << "\n";
    }
}
