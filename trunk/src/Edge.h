/*
 * Edge.h
 *
 *  Created on: Feb 9, 2010
 *      Author: Piotr Zemczak
 */


#ifndef __EDGE_H
#define __EDGE_H

#include <functional>
#include <boost/functional/hash.hpp>
#include <boost/utility.hpp>


template<typename T>
class EdgeEqualTo;
/**
 * \brief Klasa krawędzi drzewa suffixów
 * \param Traits - Klasa cech typów wykorzystywanych przez Edge
 */
template<typename Traits>
class EdgeTemplate
{
public:
	/// Typ zmiennej wskazującej numer węzła-Node
	typedef typename Traits::NodeT NodeT;
	/// Typ zmiennej wskazującej pozycję w tekscie
	typedef typename Traits::IndT IndT;
	/// Typ pojedynczego znaku tekstu
	typedef typename Traits::CharT CharT;
	/// Liczba oznaczająca brak węzła
	const static NodeT EMPTY = Traits::EMPTY_NODE;

	EdgeTemplate();

	EdgeTemplate(IndT initialFirstCharIndex, IndT initialLastCharIndex,
			NodeT parentNode, NodeT endNode, CharT firstChar);

	IndT getFirstCharIndex() const;
	void setFirstCharIndex(IndT firstCharIndex, CharT c);

	IndT getLastCharIndex() const;
	void setLastCharIndex(IndT firstCharIndex);

	void setFirstChar(CharT c);
	CharT getFirstChar() const;

	NodeT getStartNode() const;
	void setStartNode(NodeT node);

	const NodeT getEndNode() const;

	/*
	 * \return true Jeśli węzeł pusty.
	 */
	bool isNull() const;


private:
	/// Klasa stwierdzjąca równość krawędzi.
	friend class EdgeEqualTo<EdgeTemplate> ;
	/// Asigning Edges is forbidden
	EdgeTemplate& operator=(const EdgeTemplate& value);

	/// Pierwszy znak tekstu znajdującego się na krawędzi
	IndT d_firstCharIndex;
	/// Ostatni znak tekstu znajdującego się na krawędzi
	IndT d_lastCharIndex;

	/// Numer węzła z którego wychodzi krawędź.
	NodeT d_startNode;
	/// Numer węzła do którego dochdzi krawędź. Wartość ta jest unikatowa.
	const NodeT d_endNode;

	/// Pierwszy znak na krawędzi.
	CharT d_firstChar;
};

template<typename T>
EdgeTemplate<T>::EdgeTemplate() :
	d_startNode(EMPTY), d_endNode(EMPTY)
{
}

template<typename T>
EdgeTemplate<T>::EdgeTemplate(
		EdgeTemplate<T>::IndT initialFirstCharIndex,
		IndT initialLastCharIndex, NodeT parentNode,
		EdgeTemplate<T>::NodeT endNode, CharT firstChar) :
	d_firstCharIndex(initialFirstCharIndex), d_lastCharIndex(
			initialLastCharIndex), d_startNode(parentNode), d_endNode(endNode),
			d_firstChar(firstChar)
{
}

template<typename T>
EdgeTemplate<T>& EdgeTemplate<T>::operator=(const EdgeTemplate& value)
{
	assert(false);
	return *this;
}

template<typename T>
inline void EdgeTemplate<T>::setFirstCharIndex(EdgeTemplate::IndT index,
		EdgeTemplate::CharT c)
{
	this->d_firstCharIndex = index;
	this->d_firstChar = c;
}

template<typename T>
inline typename EdgeTemplate<T>::IndT EdgeTemplate<T>::getFirstCharIndex() const
{
	return d_firstCharIndex;
}

template<typename T>
inline typename EdgeTemplate<T>::IndT EdgeTemplate<T>::getLastCharIndex() const
{
	return d_lastCharIndex;
}

template<typename T>
inline void EdgeTemplate<T>::setLastCharIndex(IndT index)
{
	d_lastCharIndex = index;
}

template<typename T>
inline void EdgeTemplate<T>::setFirstChar(EdgeTemplate::CharT c)
{
	d_firstChar = c;
}

template<typename T>
inline typename EdgeTemplate<T>::CharT EdgeTemplate<T>::getFirstChar() const
{
	return d_firstChar;
}

template<typename T>
inline typename EdgeTemplate<T>::NodeT EdgeTemplate<T>::getStartNode() const
{
	return d_startNode;
}

template<typename T>
inline void EdgeTemplate<T>::setStartNode(NodeT node)
{
	d_startNode = node;
}

template<typename T>
inline const typename EdgeTemplate<T>::NodeT EdgeTemplate<T>::getEndNode() const
{
	return d_endNode;
}

template<typename T>
inline bool EdgeTemplate<T>::isNull() const
{
	return (d_startNode == EdgeTemplate<T>::EMPTY);
}

/**
 * \brief klasa szablonowa obliczająca hash krawędzi.
 * \param EdgeT Typ krawędzi w drzewie suffixów.
 */
template<typename EdgeT>
struct EdgeHash: public std::unary_function<EdgeT, std::size_t>
{
	inline std::size_t operator()(EdgeT const& edge) const
	{
		std::size_t seed = 0;
		boost::hash_combine(seed, edge.getStartNode());
		boost::hash_combine(seed, edge.getFirstChar());
		return seed;
	}
};

/**
 * \brief Obiekt funkcyjny określający równość krawędzi.
 * \param EdgeT Typ krawędzi w drzewie suffixów.
 * Krawędź jest równa wtedy i tylko wtedy gdy wychodzi z tego samego węzła
 * i ma tą samą literę na swojej krawędzi.
 */
template<typename EdgeT>
struct EdgeEqualTo: public std::binary_function<EdgeT, EdgeT, bool>
{
	inline bool operator()(const EdgeT& a, const EdgeT& b) const
	{
		if (a.d_startNode == b.d_startNode)
		{
			if (b.d_firstChar == a.d_firstChar)
			{
				return true;
			}
		}

		return false;
	}

};

#endif
