#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Suffix.h"
#include "Edge.h"
#include "Node.h"
#include "NullEdge.h"
#include <boost/unordered_set.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <map>
#include <limits.h>

#include "SuffixTreeTypeTraits.h"

//
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
//


template<typename T = unsigned int, typename stringT = std::string, typename Traits = SuffixTreeTraits<T,typename stringT::value_type> >
class SuffixTreeTemplate
{
public:

	typedef typename Traits::NodeT NodeT;
	typedef typename Traits::IndT IndT;
	typedef typename Traits::IndT_diff IndT_diff;
	typedef typename Traits::CharT CharT;

	typedef EdgeTemplate<Traits> Edge;
	typedef NodeTemplate<Traits> Node;
	typedef NullEdgeTemplate<Traits> NullEdge;
	typedef SuffixTemplate<Traits> Suffix;
	typedef stringT sufstring;

	static const IndT INDEX_OUT = Traits::OUT_OF_RANGE;
	SuffixTreeTemplate(const sufstring& inputText);
	~SuffixTreeTemplate();

	bool isSuffix(typename sufstring::const_iterator begin,
			typename sufstring::const_iterator end, NodeT node = 0);
	bool isSuffix(const sufstring& text);

	void dumpEdges(int current_n);

	void addText(const sufstring& t);

private:
	typedef boost::unordered_set<Edge, EdgeHash<Edge> , EdgeEqualTo<Edge> >
			EdgeHashSet;

	typedef std::map<NodeT, Node> NodeMap;

	void addPrefix(Suffix &active, IndT lastCharIndex);
	void insert(Edge &edge);
	void remove(Edge &edge);
	Edge& find(NodeT nodeParent, CharT firstCharOnEdge);

	NodeT splitEdge(Suffix &suffix, Edge edge);
	void canonize(Suffix& suffix);

	const sufstring& d_text;
	Suffix d_active;
	EdgeHashSet d_edges;
	NodeMap d_nodes;

};

template<typename T, typename T2, typename T3>
SuffixTreeTemplate<T, T2, T3>::SuffixTreeTemplate(const sufstring& inputText) :
	d_text(inputText), d_active(0, 0, INDEX_OUT)
{
#ifndef NDEBUG
	std::cout << "Sizeof Node"<< sizeof(Node) <<std::endl;
	std::cout << "Sizeof Node field "<< sizeof(NodeT) <<std::endl;
	std::cout << "Sizeof Edge"<< sizeof(Edge) <<std::endl;
#endif

	Node zero_Node(0);
	d_nodes[0] = zero_Node;

	for (unsigned int i = 0; i <= d_text.length(); ++i)
	{
		addPrefix(d_active, i);
	}
}

template<typename T, typename T2, typename T3>
SuffixTreeTemplate<T, T2, T3>::~SuffixTreeTemplate()
{
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::addPrefix(Suffix &active, IndT lastCharIndex)
{
	NodeT parentNode;
	NodeT lastParentNode = Node::EMPTY;

	for (;;)
	{
		parentNode = active.getOriginNode();

		if (active.isExplicit())
		{
			Edge& tmpEdge = find(d_active.getOriginNode(),
					d_text[lastCharIndex]);
			if (!tmpEdge.isNull())
			{
				break;
			}
		}
		else
		{
			Edge& tmpEdge = find(d_active.getOriginNode(),
					d_text[d_active.getFirstCharIndex()]);
			IndT_diff span = d_active.getLastCharIndex()
					- d_active.getFirstCharIndex();

			if (d_text[tmpEdge.getFirstCharIndex() + span + 1]
					== d_text[lastCharIndex])
			{
				break;
			}

			parentNode = splitEdge(d_active, tmpEdge);
		}

		Edge newEdge(lastCharIndex, d_text.length(), parentNode,
				d_nodes.size(), d_text[lastCharIndex]);
		assert(d_nodes.find(d_nodes.size()) == d_nodes.end());
		d_nodes[d_nodes.size()] = Node();
		insert(newEdge);

		if (lastParentNode > 0)
		{
			d_nodes[lastParentNode].setSuffixNode(parentNode);
		}

		lastParentNode = parentNode;

		if (d_active.getOriginNode() == 0)
		{
			d_active.setFirstCharIndex(d_active.getFirstCharIndex() + 1);
		}
		else
		{
			d_active.setOriginNode(
					d_nodes[d_active.getOriginNode()].getSuffixNode());
		}

		canonize(d_active);
	}

	if (lastParentNode > 0)
	{
		d_nodes[lastParentNode].setSuffixNode(parentNode);
	}

	d_active.setLastCharIndex(d_active.getLastCharIndex() + 1);
	canonize(d_active);
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::canonize(Suffix& suffix)
{
	if (!suffix.isExplicit())
	{

		Edge* edge = &(find(suffix.getOriginNode(),
				d_text[suffix.getFirstCharIndex()]));
		IndT_diff edge_span = edge->getLastCharIndex()
				- edge->getFirstCharIndex();
		while (edge_span <= static_cast<IndT_diff>(suffix.getLastCharIndex()
				- suffix.getFirstCharIndex()))
		{

			suffix.setFirstCharIndex(suffix.getFirstCharIndex() + edge_span + 1);
			suffix.setOriginNode(edge->getEndNode());

			//if ( suffix.getFirstCharIndex() <= suffix.getLastCharIndex()) {
			if (suffix.isImplicit())
			{
				edge = &(find(edge->getEndNode(),
						d_text[suffix.getFirstCharIndex()]));
				edge_span = edge->getLastCharIndex()
						- edge->getFirstCharIndex();
			};
		}
	}
}

template<typename T, typename T2, typename T3>
typename SuffixTreeTemplate<T, T2, T3>::Edge& SuffixTreeTemplate<T, T2, T3>::find(
		NodeT nodeParent, CharT firstCharOnEdge)
{
	Edge mockEdge(0, 0, nodeParent, Node::EMPTY, firstCharOnEdge);
	typename EdgeHashSet::const_iterator cit = d_edges.find(mockEdge);
	if (cit == d_edges.end())
	{
		return NullEdge::getNull();
	}
	return const_cast<Edge&> (*cit);
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::insert(Edge& edge)
{
	d_edges.insert(edge);
	assert(d_edges.find(edge) != d_edges.end());
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::remove(Edge& edge)
{
	d_edges.erase(edge);
}

template<typename T, typename T2, typename T3>
typename SuffixTreeTemplate<T, T2, T3>::NodeT SuffixTreeTemplate<T, T2, T3>::splitEdge(
		Suffix &suffix, Edge edge)
{
	remove(edge);

	Edge newEdge(edge.getFirstCharIndex(), edge.getFirstCharIndex()
			+ suffix.getLastCharIndex() - suffix.getFirstCharIndex(),
			suffix.getOriginNode(), d_nodes.size(), edge.getFirstChar());

	assert(edge.getFirstChar() == d_text[edge.getFirstCharIndex()]);
	assert(d_nodes.find(d_nodes.size()) == d_nodes.end());
	d_nodes[(int) d_nodes.size()] = Node();

	insert(newEdge);

	d_nodes[newEdge.getEndNode()].setSuffixNode(suffix.getOriginNode());
	int index = edge.getFirstCharIndex() + suffix.getLastCharIndex()
			- suffix.getFirstCharIndex() + 1;

	assert((index >=0) && (index < static_cast<int>(d_text.length())));

	edge.setFirstCharIndex(index, d_text[index]);
	edge.setStartNode(newEdge.getEndNode());

	insert(edge);

	return newEdge.getEndNode();
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::dumpEdges(int current_n)
{

	std::cout << " Start  End  Suf  First Last  String\n";
	for (typename EdgeHashSet::const_iterator cit = d_edges.begin(); cit
			!= d_edges.end(); ++cit)
	{
		const Edge* s = &(*cit);
		if (s->isNull())
			continue;
		std::cout << std::setw(5) << s->getStartNode() << " " << std::setw(5)
				<< s->getEndNode() << " " << std::setw(3)
				<< d_nodes[s->getEndNode()].getSuffixNode() << " "
				<< std::setw(5)
				<< static_cast<unsigned long long>(s->getFirstCharIndex()) << " "
				<< std::setw(6)
				<< static_cast<unsigned long long>(s->getLastCharIndex()) << "  ";
		int top;
		if (current_n > static_cast<int>(s->getLastCharIndex()))
			top = s->getLastCharIndex();
		else
			top = current_n;

		std::wcout <<  d_text.substr(s->getFirstCharIndex(),top).c_str() << std::endl;

	}

	std::cout << "Active :" << d_active.getOriginNode() << " "
			<< static_cast<unsigned long long>(d_active.getFirstCharIndex()) << " "
			<< static_cast<unsigned long long>(d_active.getLastCharIndex()) << std::endl;

}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::addText(const sufstring& t)
{
	int oldLength = d_text.length();
	sufstring& s = const_cast<sufstring&> (d_text);
	s += t;
	for (unsigned int i = oldLength; i < d_text.length(); ++i)
	{
		addPrefix(d_active, i);
	}
}

template<typename T, typename T2, typename T3>
bool SuffixTreeTemplate<T, T2, T3>::isSuffix(const sufstring& text)
{
	return isSuffix(text.begin(), text.end());
}

template<typename T, typename T2, typename T3>
bool SuffixTreeTemplate<T, T2, T3>::isSuffix(typename sufstring::const_iterator begin,
		typename sufstring::const_iterator end, NodeT node)
{
	boost::iterator_range<typename sufstring::const_iterator> testText =
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

	boost::iterator_range<typename sufstring::const_iterator> subText =
			boost::make_iterator_range(d_text.begin() + firstChar,
					d_text.begin() + lastChar + 1);

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

#endif

