#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H

#include <string>
#include "Suffix.h"

using namespace std;

class SuffixTree
{
	private:
		void AddPrefix(Suffix &active, int lastCharIndex);

		string tekst;
	public:
		SuffixTree(string wejsciowy_tekst);
};

#endif

