#ifndef __EDGE_H
#define __EDGE_H

class Edge
{
	public:
		Edge();
		Edge(int initialFirstCharIndex,
				int initialLastCharIndex,
				int parentNode);

		int firstCharIndex;
		int lastCharIndex;
		int startNode;
		int endNode;
};

#endif
