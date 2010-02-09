/*
 * NullEdge.h
 *
 *  Created on: Feb 8, 2010
 *      Author: Lukasz Spintzyk
 */

#ifndef NULLEDGE_H_
#define NULLEDGE_H_

#include "Edge.h"
#include <cassert>

template<typename Traits>
class NullEdgeTemplate: public EdgeTemplate<Traits>
{
	NullEdgeTemplate();

public:
	static EdgeTemplate<Traits>& getNull();
};

template<typename T>
NullEdgeTemplate<T>::NullEdgeTemplate()
{
	setStartNode(EdgeTemplate<T>::EMPTY);
}

template<typename T>
EdgeTemplate<T>& NullEdgeTemplate<T>::getNull()
{
	static NullEdgeTemplate s_nullEdge;
	assert(s_nullEdge.getStartNode() == EdgeTemplate<T>::EMPTY);
	return s_nullEdge;
}

#endif /* NULLEDGE_H_ */
