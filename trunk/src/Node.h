#ifndef __NODE_H
#define __NODE_H

class Node
{
public:
	Node();
	Node(int suffixNode);

	int getSuffixNode() const;
	void setSuffixNode(int suffixNode);
	const static int EMPTY;
private:
	int d_suffixNode;
};



#endif

