#include "Suffix.h"
#include "Edge.h"
#include "SuffixTree.h"

Suffix::Suffix(int node, int start, int stop)
{
	originNode = node;
	firstCharIndex = start;
	lastCharIndex = stop;
}

int Suffix::Explicit()
{
	return firstCharIndex > lastCharIndex;
}

int Suffix::Implicit()
{
	return lastCharIndex >= firstCharIndex;
}

void Suffix::Canonize()
{
    if ( !Explicit() ) {

        Edge* edge = &(tree->Find( originNode, tree->Text[ firstCharIndex ] ));
        int edge_span = edge->lastCharIndex - edge->getFirstCharIndex();
        while ( edge_span <= ( lastCharIndex - firstCharIndex) ) {
            firstCharIndex = firstCharIndex + edge_span + 1;
            originNode = edge->endNode;
            if ( firstCharIndex <= lastCharIndex ) {
                edge = &(tree->Find( edge->endNode, tree->Text[ firstCharIndex ] ));
                edge_span = edge->lastCharIndex- edge->getFirstCharIndex();
            };
        }
    }
}

