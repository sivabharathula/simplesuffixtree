/*

#include <string>
#include <iostream>
#include <iomanip>
#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h"
#include "Edge.h"

#include <cassert>
#include <boost/unordered_map.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <limits.h>

const SuffixTree::IndT SuffixTree::INDEX_OUT = -1;//UINT_MAX;

SuffixTree::SuffixTree(const std::string& inputText) :
	d_text(inputText), d_active(0, 0, INDEX_OUT)
{
	Node zero_Node(0);
	d_nodes[0] = zero_Node;

	for (unsigned int i = 0; i <= d_text.length(); ++i)
	{
		addPrefix(d_active, i);
	}
}

SuffixTree::~SuffixTree()
{
}

void SuffixTree::addPrefix(Suffix &active, IndT lastCharIndex)
{
	NodeT parentNode;
	NodeT lastParentNode = Node::EMPTY;

	for (;;)
	{
		parentNode = active.getOriginNode();

		if (active.isExplicit())
		{
			Edge& tmpEdge = find(d_active.getOriginNode(), d_text[lastCharIndex]);
			if (!tmpEdge.isNull())
			{
				break;
			}
		}
		else
		{
			Edge& tmpEdge =
					find(d_active.getOriginNode(), d_text[d_active.getFirstCharIndex()]);
			IndT_diff span = d_active.getLastCharIndex() - d_active.getFirstCharIndex();

			if (d_text[tmpEdge.getFirstCharIndex() + span + 1]
					== d_text[lastCharIndex])
			{
				break;
			}

			parentNode = splitEdge(d_active, tmpEdge);
		}

		Edge newEdge(lastCharIndex, d_text.length(), parentNode, d_nodes.size(),
				d_text[lastCharIndex]);
		assert(d_nodes.find(d_nodes.size()) == d_nodes.end());
		d_nodes[d_nodes.size()] = Node();
		insert(newEdge);

		if (lastParentNode > 0)
		{
			d_nodes[lastParentNode].setSuffixNode( parentNode );
		}

		lastParentNode = parentNode;

		if (d_active.getOriginNode() == 0)
		{
			d_active.setFirstCharIndex( d_active.getFirstCharIndex()+1);
		}
		else
		{
			d_active.setOriginNode(
					d_nodes[d_active.getOriginNode()].getSuffixNode() );
		}

		canonize(d_active);
	}

	if (lastParentNode > 0)
	{
		d_nodes[lastParentNode].setSuffixNode( parentNode );
	}

	d_active.setLastCharIndex(d_active.getLastCharIndex() + 1);
	canonize(d_active);
}

void SuffixTree::canonize(Suffix& suffix)
{
    if ( !suffix.isExplicit() ) {

        Edge* edge = &(find( suffix.getOriginNode(), d_text[ suffix.getFirstCharIndex() ] ));
        IndT_diff edge_span = edge->getLastCharIndex() - edge->getFirstCharIndex();
        while ( edge_span <= ( suffix.getLastCharIndex() - suffix.getFirstCharIndex()) ) {

        	suffix.setFirstCharIndex( suffix.getFirstCharIndex() + edge_span + 1);
        	suffix.setOriginNode( edge->getEndNode() );

        	//if ( suffix.getFirstCharIndex() <= suffix.getLastCharIndex()) {
        	if (suffix.isImplicit()) {
                edge = &(find( edge->getEndNode(), d_text[ suffix.getFirstCharIndex() ] ));
                edge_span = edge->getLastCharIndex()- edge->getFirstCharIndex();
            };
        }
    }
}

SuffixTree::Edge& SuffixTree::find(NodeT nodeParent, CharT firstCharOnEdge)
{
	Edge mockEdge(0, 0, nodeParent, Node::EMPTY, firstCharOnEdge);
	EdgeHashSet::const_iterator cit = d_edges.find(mockEdge);
	if (cit == d_edges.end())
	{
		return NullEdge::getNull();
	}
	return const_cast<Edge&> (*cit);
}

void SuffixTree::insert(Edge& edge)
{
	d_edges.insert(edge);
	assert(d_edges.find(edge) != d_edges.end());
}

void SuffixTree::remove(Edge& edge)
{
	d_edges.erase(edge);
}

SuffixTree::NodeT SuffixTree::splitEdge(Suffix &suffix, Edge edge)
{
	remove(edge);

	Edge newEdge(edge.getFirstCharIndex(), edge.getFirstCharIndex()
			+ suffix.getLastCharIndex() - suffix.getFirstCharIndex(), suffix.getOriginNode(),
			d_nodes.size(), edge.getFirstChar());

	assert(edge.getFirstChar() == d_text[edge.getFirstCharIndex()]);
	assert(d_nodes.find(d_nodes.size()) == d_nodes.end());
	d_nodes[(int) d_nodes.size()] = Node();

	insert(newEdge);

	d_nodes[newEdge.getEndNode()].setSuffixNode( suffix.getOriginNode() );
	int index = edge.getFirstCharIndex() + suffix.getLastCharIndex()
			- suffix.getFirstCharIndex() + 1;

	assert((index >=0) && (index < static_cast<int>(d_text.length())));

	edge.setFirstCharIndex(index, d_text[index]);
	edge.setStartNode(newEdge.getEndNode());

	insert(edge);

	return newEdge.getEndNode();
}

void SuffixTree::dumpEdges(int current_n)
{
	std::cout << " Start  End  Suf  First Last  String\n";
	for (EdgeHashSet::const_iterator cit = d_edges.begin(); cit
			!= d_edges.end(); ++cit)
	{
		const Edge* s = &(*cit);
		if (s->isNull())
			continue;
		std::cout << std::setw(5) << s->getStartNode() << " " << std::setw(5)
				<< s->getEndNode() << " " << std::setw(3)
				<< d_nodes[s->getEndNode()].getSuffixNode() << " " << std::setw(5)
				<< s->getFirstCharIndex() << " " << std::setw(6)
				<< s->getLastCharIndex() << "  ";
		int top;
		if (current_n > s->getLastCharIndex())
			top = s->getLastCharIndex();
		else
			top = current_n;
		for (int l = s->getFirstCharIndex(); l <= top; l++)
			std::cout << d_text[l];
		std::cout << "\n";
	}

	std::cout << "Active :" << d_active.getOriginNode() << " "
			<< d_active.getFirstCharIndex() << " " << d_active.getLastCharIndex()
			<< std::endl;

}

void SuffixTree::addText(const std::string& t)
{
	int oldLength = d_text.length();
	std::string& s = const_cast<std::string&>(d_text);
	s+= t;
	for (unsigned int i = oldLength; i < d_text.length(); ++i)
	{
		addPrefix(d_active, i);
	}
}

bool SuffixTree::isSuffix(const std::string& text)
{
	return isSuffix(text.begin(), text.end());
}

bool SuffixTree::isSuffix(std::string::const_iterator begin,
		std::string::const_iterator end, int node)
{
	boost::iterator_range<std::string::const_iterator> testText =
			boost::make_iterator_range(begin, end);
#ifndef NDEBUG
	std::cout << "Find " << boost::make_iterator_range(begin, end) << std::endl;
#endif

	Edge& e = find(node, *begin);//znajdz suffix zaczynajacy sie w node na literze *begin
	if (e.isNull())
	{
		return false;
	}

	int endNode = e.getEndNode();
	int firstChar = e.getFirstCharIndex();
	int lastChar = e.getLastCharIndex();

	boost::iterator_range<std::string::const_iterator> subText =
			boost::make_iterator_range(d_text.begin() + firstChar, d_text.begin()
					+ lastChar + 1);

#ifndef NDEBUG
	std::cout << " test " << testText << " subText" << subText << std::endl;
#endif
	if (subText.size() < testText.size())
	{
		if (boost::starts_with(testText, subText))
		{
			return isSuffix(begin + subText.size(), end, endNode);
		}
		else
		{
			return false;
		}
	}
	else if (boost::starts_with(subText, testText))
	{
		return true;
	}

	return false;
}
*/
