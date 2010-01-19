#include "Suffix.h"

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

void Canonize()
{
}

