#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H

#include <string>
#include "Suffix.h"
#include "Edge.h"
#include "Node.h"
#include <boost/unordered_set.hpp>
#include <map>

class SuffixTree
{
public:

	SuffixTree(const std::string& inputText);
	~SuffixTree();

	bool isSuffix(std::string::const_iterator begin,
			std::string::const_iterator end, int node = 0);
	bool isSuffix(const std::string& text);

	void dumpEdges(int current_n);

private:
	typedef boost::unordered_set<Edge, EdgeHash, EdgeEqualTo> EdgeHashSet;
	typedef std::map<int, Node> NodeMap;
	void addPrefix(Suffix &active, int lastCharIndex);
	void insert(Edge &edge);
	void remove(Edge &edge);
	Edge& find(int nodeParent, char firstCharOnEdge);
	int splitEdge(Suffix &suffix, Edge edge);
	void canonize(Suffix& suffix);

	const std::string& d_text;
	Suffix d_active;
	EdgeHashSet d_edges;
	NodeMap d_nodes;

};

#endif

