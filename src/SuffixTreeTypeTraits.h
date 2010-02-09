/*
 * SuffixTreeTypeTraits.h
 *
 *  Created on: Feb 9, 2010
 *      Author: Lukasz Spintzyk
 */

#ifndef SUFFIXTREETYPETRAITS_H_
#define SUFFIXTREETYPETRAITS_H_

#include <limits.h>

template<typename TEXT_SIZE_T, typename charType = char>
class SuffixTreeTraits;

template<typename charType>
class SuffixTreeTraits<unsigned long long, charType>
{
public:
	typedef unsigned long long IndT;
	typedef long long IndT_diff;
	typedef long long NodeT;
	typedef charType CharT;

	static const IndT OUT_OF_RANGE = UINT_MAX;
	static const NodeT EMPTY_NODE = -1;
};

template<typename charType>
class SuffixTreeTraits<unsigned int, charType>
{
public:
	typedef unsigned int IndT;
	typedef int IndT_diff;
	typedef long long NodeT;
	typedef charType CharT;

	static const IndT OUT_OF_RANGE = UINT_MAX;
	static const NodeT EMPTY_NODE = -1;
};

template<typename charType>
class SuffixTreeTraits<unsigned short, charType>
{
public:
	typedef unsigned short IndT;
	typedef int IndT_diff;
	typedef int NodeT;
	typedef int CharT;

	static const IndT OUT_OF_RANGE = USHRT_MAX;
	static const NodeT EMPTY_NODE = -1;
};

template<typename charType>
class SuffixTreeTraits<unsigned char, charType>
{
public:
	typedef unsigned char IndT;
	typedef short IndT_diff;
	typedef short NodeT;
	typedef short CharT;

	static const IndT OUT_OF_RANGE = UCHAR_MAX;
	static const NodeT EMPTY_NODE = -1;
};


#endif /* SUFFIXTREETYPETRAITS_H_ */
