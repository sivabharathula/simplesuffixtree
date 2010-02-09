#include <iostream>
#include "SuffixTree.h"
#include "SuffixTreeTypeTraits.h"
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
	typedef SuffixTreeTemplate<unsigned long long> SuffixTreeLL;
	typedef SuffixTreeTemplate<unsigned int> SuffixTreeINT;
	typedef SuffixTreeTemplate<unsigned short> SuffixTreeSHRT;
	typedef SuffixTreeTemplate<unsigned char> SuffixTree;

	const char* text = "BOOKKE";
	std::string str(text);

	std::cout << "Tree uchar: \n";
	SuffixTree tree( str );

/*	std::cout << "\nTree ushort: \n";
	SuffixTreeSHRT treeShrt( str );

	std::cout << "\nTree uint: \n";
	SuffixTreeINT treeInt( str );



	std::cout << "\nTree long long: \n";
	SuffixTreeLL treeLL( str );
*/



	//tree.dumpEdges(str.length());

	for (unsigned int i = 0 ; i < str.length(); ++i)
	{
		if (!tree.isSuffix(str.substr(i)))
		{
			std::cout << "Drzewo jest do dupy" << std::endl;
		}
	}


	std::cout << "Looks ok"<<std::endl;


	//tree.addText("BOOKKE\0");
	//std::cout << "NEW STR" << str << std::endl;

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
