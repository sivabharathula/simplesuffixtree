#include <iostream>
#include "SuffixTree.h"
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
	const char* text = "BOOKKE";
	SuffixTree tree(text);
	tree.dump_edges(strlen(text));
	return 0;
}
