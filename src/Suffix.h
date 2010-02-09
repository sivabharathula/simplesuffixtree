#ifndef __SUFFIX_H
#define __SUFFIX_H

class SuffixTree;
class Suffix
{
public:
	Suffix(int node, int start, int stop);

	bool isExplicit();
	bool isImplicit();

	int getFirstCharIndex() const;
	void setFirstCharIndex(int index);

	int getLastCharIndex() const;
	void setLastCharIndex(int index);

	int getOriginNode() const;
	void setOriginNode(int node);

private:
	int d_originNode;
	int d_firstCharIndex;
	int d_lastCharIndex;
};

#endif

