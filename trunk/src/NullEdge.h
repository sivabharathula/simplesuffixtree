/*
 * NullEdge.h
 *
 *  Created on: Feb 8, 2010
 *      Author: Lukasz Spintzyk
 */

#ifndef NULLEDGE_H_
#define NULLEDGE_H_

#include "Edge.h"

class NullEdge: public Edge {
	NullEdge();

public:
	static Edge& getNull();
};

#endif /* NULLEDGE_H_ */
