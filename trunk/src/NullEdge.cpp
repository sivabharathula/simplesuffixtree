/*
 * NullEdge.cpp
 *
 *  Created on: Feb 8, 2010
 *      Author: Lukasz Spintzyk
 */

#include "NullEdge.h"
#include <cassert>

NullEdge::NullEdge()
{
	setStartNode(-1);
}

Edge& NullEdge::getNull()
{
	static NullEdge s_nullEdge;
	assert(s_nullEdge.getStartNode() == -1);
	return s_nullEdge;
}
