/**
 *
 * \file SuffixTreeTypeTraits.h
 *
 *  Created on: Feb 9, 2010
 *      Author: Łukasz Spintzyk
 *
 *
 * Szablon klasy cech dla Drzewa suffixow.
 * Cechy pozwalają zaoszczędzić na miejscu zajmowanym przez węzły i krawędzie drzewa suffixów.
 * Poprzez wybranie odpowiedniego typu na ich przechowywanie.
 * template<typename TEXT_SIZE_T, typename charType = char>
 *	class SuffixTreeTraits;
 * \param TEXT_SIZE_T odpowiednio duży typ do przechowywania numeru znaku w tekscie, dla którego budowane jest drzewo
 * \param charType typ pojedynczego znaku.
 *
 * Tree max string length = sizeof(uchar):<br>
	Sizeof Node2<br>
	Sizeof Node field 2<br>
	Sizeof Edge8<br>
	<br>
	Tree max string length = sizeof(ushort):<br>
	Sizeof Node4<br>
	Sizeof Node field 4<br>
	Sizeof Edge16<br>

	Tree max string length = sizeof(uint)<br>
	Sizeof Node8<br>
	Sizeof Node field 8<br>
	Sizeof Edge32<br>

	Tree max string length = sizeof(long long):<br>
	Sizeof Node8<br>
	Sizeof Node field 8<br>
	Sizeof Edge40<br>
 */


#ifndef SUFFIXTREETYPETRAITS_H_
#define SUFFIXTREETYPETRAITS_H_

#include <limits.h>


template<typename TEXT_SIZE_T, typename charType = char>
class SuffixTreeTraits;

/**
 * \brief Specjalizacja szablonu klasy cech dla Drzewa suffixow.
 * Ta cecha powinna być wykorzystana dla bardzo dużych tekstów.
 * \param 'unsigned long long' Pierwszy parametr wskazuje na rozmiar tekstu,
 * który nie może być większy od maksymalnej wartości unsigned long long
 * \param charType typ pojedynczego znaku.
 */
template<typename charType>
class SuffixTreeTraits<unsigned long long, charType>
{
public:
	/// Typ zmiennej wskazującej pozycję w tekscie
	typedef unsigned long long IndT;
	/// Typ zmiennej wskazującej różnicę pomiędzy IndT
	typedef long long IndT_diff;
	/// Typ zmiennej wskazującej numer węzła-Node
	typedef long long NodeT;
	/// Typ pojedynczego znaku tekstu
	typedef charType CharT;

	/// Liczba reprezentująca pozycję poza tekstem
	static const IndT OUT_OF_RANGE = UINT_MAX;
	/// Liczba oznaczająca brak węzła
	static const NodeT EMPTY_NODE = -1;
};

/**
 * \brief Specjalizacja szablonu klasy cech dla Drzewa suffixow.
 * Ta cecha powinna być wykorzystana dla dużych tekstów.
 * \param 'unsigned int' Pierwszy parametr wskazuje na rozmiar tekstu,
 * który nie może być większy od maksymalnej wartości unsigned int
 * \param charType typ pojedynczego znaku.
 */
template<typename charType>
class SuffixTreeTraits<unsigned int, charType>
{
public:
	/// Typ zmiennej wskazującej pozycję w tekscie
	typedef unsigned int IndT;
	/// Typ zmiennej wskazującej różnicę pomiędzy IndT
	typedef int IndT_diff;
	/// Typ zmiennej wskazującej numer węzła-Node
	typedef long long NodeT;
	/// Typ pojedynczego znaku tekstu
	typedef charType CharT;

	/// Liczba reprezentująca pozycję poza tekstem
	static const IndT OUT_OF_RANGE = UINT_MAX;
	/// Liczba oznaczająca brak węzła
	static const NodeT EMPTY_NODE = -1;
};


/**
 * \brief Specjalizacja szablonu klasy cech dla Drzewa suffixow.
 * Ta cecha powinna być wykorzystana dla tekstów średniej długości.
 * \param 'unsigned long long' Pierwszy parametr wskazuje na rozmiar tekstu,
 * który nie może być większy od maksymalnej wartości unsigned short
 * \param charType typ pojedynczego znaku.
 */
template<typename charType>
class SuffixTreeTraits<unsigned short, charType>
{
public:
	/// Typ zmiennej wskazującej pozycję w tekscie
	typedef unsigned short IndT;
	/// Typ zmiennej wskazującej różnicę pomiędzy IndT
	typedef int IndT_diff;
	/// Typ zmiennej wskazującej numer węzła-Node
	typedef int NodeT;
	/// Typ pojedynczego znaku tekstu
	typedef int CharT;

	/// Liczba reprezentująca pozycję poza tekstem
	static const IndT OUT_OF_RANGE = USHRT_MAX;
	/// Liczba oznaczająca brak węzła
	static const NodeT EMPTY_NODE = -1;
};


/**
 * \brief Specjalizacja szablonu klasy cech dla Drzewa suffixow.
 * Ta cecha powinna być wykorzystana dla tekstów do 255 znaków.
 * \param 'unsigned long long' Pierwszy parametr wskazuje na rozmiar tekstu,
 * który nie może być większy od maksymalnej wartości unsigned char
 * \param charType typ pojedynczego znaku.
 */
template<typename charType>
class SuffixTreeTraits<unsigned char, charType>
{
public:
	/// Typ zmiennej wskazującej pozycję w tekscie
	typedef unsigned char IndT;
	/// Typ zmiennej wskazującej różnicę pomiędzy IndT
	typedef short IndT_diff;
	/// Typ zmiennej wskazującej numer węzła-Node
	typedef short NodeT;
	/// Typ pojedynczego znaku tekstu
	typedef short CharT;

	/// Liczba reprezentująca pozycję poza tekstem
	static const IndT OUT_OF_RANGE = UCHAR_MAX;
	/// Liczba oznaczająca brak węzła
	static const NodeT EMPTY_NODE = -1;
};


#endif /* SUFFIXTREETYPETRAITS_H_ */
