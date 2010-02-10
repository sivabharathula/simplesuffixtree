/*
 * Node.h
 *
 *  Created on: Feb 9, 2010
 *      Author: Piotr Zemczak
 */

#ifndef __NODE_H
#define __NODE_H

/**
 * \brief Klasa szblonowa dla typu węzła.
 * Reprezentuje węzeł w drzewie suffixów.
 * \param Traits cechy typów wykorzystywancyh przez NodeTemplate
 */
template<typename Traits>
class NodeTemplate
{
public:
	/// Typ zmiennej wskazującej numer węzła-Node
	typedef typename Traits::NodeT NodeT;
	/// Liczba oznaczająca brak węzła
	const static NodeT EMPTY = Traits::EMPTY_NODE ;

	NodeTemplate();
	NodeTemplate(NodeT suffixNode);

	NodeT getSuffixNode() const;
	void setSuffixNode(NodeT suffixNode);

private:
	/// zmienna reprezentująca węzeł wskazujący na suffix tekstu wskazywanego przez ten węzeł
	NodeT d_suffixNode;
};

template<typename T>
NodeTemplate<T>::NodeTemplate() :
	d_suffixNode(NodeTemplate<T>::EMPTY)
{
}

template<typename T>
NodeTemplate<T>::NodeTemplate(NodeT node) :
	d_suffixNode(node)
{
}

template<typename T>
typename NodeTemplate<T>::NodeT
NodeTemplate<T>::getSuffixNode() const
{
	return d_suffixNode;
}

template<typename T>
void NodeTemplate<T>::setSuffixNode(NodeT suffixNode)
{
	d_suffixNode = suffixNode;
}


#endif

