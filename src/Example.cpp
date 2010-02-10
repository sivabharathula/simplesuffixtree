#include <iostream>
#include "SuffixTree.h"
#include "SuffixTreeTypeTraits.h"
#include <boost/unordered_set.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <string>
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
	//typedef SuffixTreeTemplate<unsigned long long> SuffixTreeLL;
	//typedef SuffixTreeTemplate<unsigned int> SuffixTreeINT;
	//typedef SuffixTreeTemplate<unsigned short> SuffixTreeSHRT;
	//typedef SuffixTreeTemplate<unsigned char, SuffixTreeTraits<unsigned char, char> > SuffixTree;
	typedef SuffixTreeTemplate<> SuffixTree;
	typedef SuffixTreeTemplate<unsigned char, std::wstring > SuffixTreeW;
	const char* text = "BOOKKE";
	std::string str(text);
	std::wstring wstr(L"BOOKKEĘĄŚź");



	std::cout << "Tree uchar: \n";
	SuffixTree tree( str );

	for (SuffixTree::const_iterator cit = tree.begin(); cit!= tree.end(); ++cit)
	{
		std::cout << *cit << std::endl;

	}

	for (SuffixTree::iterator cit = tree.begin(); cit!= tree.end(); ++cit)
	{
		std::cout << *cit << std::endl;

	}

	SuffixTreeW wtree( wstr );
	std::wcout << std::wstring(L"asdźćłżęąń\n");

/*	std::cout << "\nTree ushort: \n";
	SuffixTreeSHRT treeShrt( str );

	std::cout << "\nTree uint: \n";
	SuffixTreeINT treeInt( str );



	std::cout << "\nTree long long: \n";
	SuffixTreeLL treeLL( str );
*/

	//typedef SuffixTreeTemplate<unsigned char, SuffixTreeTraits<unsigned char, wchar_t> > WTree;



	tree.dumpEdges(str.length());

	for (unsigned int i = 0 ; i < str.length(); ++i)
	{
		if (!tree.isSuffix(str.substr(i)))
		{
			std::cout << "Drzewo jest do dupy" << std::endl;
		}
	}


	std::cout << "Looks ok"<<std::endl;


	if (tree.isSuffix("BOOKKE"))
		{
		std::cout << std::endl <<"YES it is"<<std::endl;
		}
	else
	{
		std::cout << std::endl <<"NO it is not"<<std::endl;
	}

	std::string s("BADtextBASS");
	if (tree.isSuffix(s))
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
