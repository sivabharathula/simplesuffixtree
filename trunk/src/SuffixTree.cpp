#include <string>
#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h"

int Node::Count = 1;

SuffixTree::SuffixTree(string wejsciowy_tekst)
{
	tekst = wejsciowy_tekst;
}

void SuffixTree::AddPrefix(Suffix &active, int lastCharIndex)
{
}
