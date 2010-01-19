#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H

#include <string>
#include "Suffix.h"
#include "Edge.h"
#include "Node.h"

using namespace std;

class SuffixTree
{
	private:
		void AddPrefix(Suffix &active, int lastCharIndex);
		void Insert(Edge &edge);
		void Remove(Edge &edge);

		string Text;
		unsigned int Length;
		Suffix Active;
		Edge Edges[2179];
		Node Nodes[2000];
	public:
		SuffixTree(string inputText);
		~SuffixTree();
		Edge Find(int node, int c);
		int SplitEdge(Suffix &suffix, Edge &edge);
};

#endif

