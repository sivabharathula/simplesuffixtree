#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H

#include <string>
#include "Suffix.h"
#include "Edge.h"
#include "Node.h"
#include <boost/unordered_set.hpp>
#include <map>

using namespace std;

class SuffixTree
{
	public:
	string Text;
	private:
		typedef boost::unordered_set<Edge, EdgeHash, EdgeEqualTo> EdgeHashSet;
		typedef std::map<int, Node> NodeMap;
		void AddPrefix(Suffix &active, int lastCharIndex);
		void Insert(Edge &edge);
		void Remove(Edge &edge);


		unsigned int Length;
		Suffix Active;
		Edge Edges[2179];
		Node Nodes[2000];

		EdgeHashSet d_edges;
		NodeMap d_nodes;
	public:
		void dump_edges( int current_n );
		SuffixTree(string inputText);
		~SuffixTree();
		Edge& Find(int node, int c);
		int SplitEdge(Suffix &suffix, Edge &edge);
};

#endif

