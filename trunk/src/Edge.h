#ifndef __EDGE_H
#define __EDGE_H

class Edge
{
	public:
		Edge();
		Edge(int initialFirstCharIndex,
				int initialLastCharIndex,
				int parentNode);

		static int Hash(int node, int c);

		int firstCharIndex;
		int lastCharIndex;
		int startNode;
		int endNode;
};

#endif
