#ifndef __SUFFIX_H
#define __SUFFIX_H


class SuffixTree;
class Suffix
{
	public:
		Suffix(int node, int start, int stop);

		int Explicit();
		int Implicit();
		void Canonize();

		int originNode;
		int firstCharIndex;
		int lastCharIndex;
		SuffixTree* tree;
};

#endif

