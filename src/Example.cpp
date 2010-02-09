#include <iostream>
#include "SuffixTree.h"
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
	const char* text = "BOOKKE";
	std::string str(text);
	SuffixTree tree = str;


	//tree.dumpEdges(str.length());

	if (tree.isSuffix("BADtextBASS"))
		{
		std::cout << std::endl <<"YES it is"<<std::endl;
		}
	else
	{
		std::cout << std::endl <<"NO it is not"<<std::endl;
	}


	if (tree.isSuffix("KK"))
		{
		std::cout << std::endl <<"YES it is"<<std::endl;
		}
	else
	{
		std::cout << std::endl <<"NO it is not"<<std::endl;
	}
	return 0;
}
