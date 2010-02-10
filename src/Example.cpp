#include <iostream>
#include <fstream>
#include "SuffixTree.h"
#include "SuffixTreeTypeTraits.h"
#include <cstring>
#include <time.h>
using namespace std;

typedef SuffixTreeTemplate<> SuffixTree;
typedef SuffixTreeTemplate<unsigned char, std::wstring > SuffixTreeW;
//typedef SuffixTreeTemplate<unsigned long long> SuffixTreeLL;
//typedef SuffixTreeTemplate<unsigned int> SuffixTreeINT;
//typedef SuffixTreeTemplate<unsigned short> SuffixTreeSHRT;
//typedef SuffixTreeTemplate<unsigned char, SuffixTreeTraits<unsigned char, char> > SuffixTree;

void Search(SuffixTree testTree, string testString, const char* word, int count)
{	
	clock_t start, end;
	bool found;

	start = clock();
	for (int i = 0; i < count; ++i)
	{
		found = testTree.isSuffix(word);
	}
	end = clock();

  cout << "Wyszukanie \"" << word << "\" " << count << " razy w SuffixTree: " << (((double)end - (double)start)/(double)CLOCKS_PER_SEC)*1000/(double)count << endl;

	start = clock();
	for (int i = 0; i < count; ++i)
	{
		testString.find(word);
	}
	end = clock();
	
	cout << "Wyszukanie \"" << word << "\" " << count << " razy w string: " << (((double)end - (double)start)/(double)CLOCKS_PER_SEC)*1000/(double)count << endl;
}

void PerformTest(string testString)
{
	SuffixTree testTree(testString);

	const char* test1 = "I przypomniał sobie całe szeregi ludzi obdartych,";

	Search(testTree, testString, test1, 10000);

	const char* test2 = "Rzecz dziwna! przecie miał już ustaloną opinię hojnego filantropa. Członkowie Towarzystwa Dobroczynności we frakach składali mu podziękowania za ofiarę dla wiecznie łaknącej instytucji; hrabina Karolowa we wszystkich salonach opowiadała o pieniądzach, które złożył na jej ochronę; jego służba i subiekci sławili go za podwyższenie im pensji. Ale Wokulskiemu rzeczy te nie sprawiały żadnej przyjemności, tak jak on sam nie przywiązywał do nich żadnej wagi. Rzucał tysiące rubli do kas urzędowych dobroczyńców, ażeby kupić za to rozgłos nie pytając, co się zrobi z pieniędzmi.";

	Search(testTree, testString, test2, 10000);

	const char* test3 = "SuffixTreeI przypomniał sobie całe szeregi ludzi obdartych,";

	Search(testTree, testString, test3, 10000);

	const char* test4 = "SuffixTreeRzecz dziwna! przecie miał już ustaloną opinię hojnego filantropa. Członkowie Towarzystwa Dobroczynności we frakach składali mu podziękowania za ofiarę dla wiecznie łaknącej instytucji; hrabina Karolowa we wszystkich salonach opowiadała o pieniądzach, które złożył na jej ochronę; jego służba i subiekci sławili go za podwyższenie im pensji. Ale Wokulskiemu rzeczy te nie sprawiały żadnej przyjemności, tak jak on sam nie przywiązywał do nich żadnej wagi. Rzucał tysiące rubli do kas urzędowych dobroczyńców, ażeby kupić za to rozgłos nie pytając, co się zrobi z pieniędzmi.";

	Search(testTree, testString, test4, 10000);
}

int main(int argc, char** argv)
{
	cout << "-----" << endl;
	cout << "Test wydajnosci." << endl << endl;
	cout << "-----" << endl;

	string testString;
	string readString;

  ifstream fin("lalka.txt");
	while (getline(fin, readString))
	{
		testString += readString;
	}

	cout << "Wczytanie pliku zakonczone" << endl;

	PerformTest(testString);

	return 0;
}
