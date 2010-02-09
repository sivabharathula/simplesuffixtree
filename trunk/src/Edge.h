#ifndef __EDGE_H
#define __EDGE_H

#include <functional>
#include <boost/functional/hash.hpp>
#include <boost/utility.hpp>

class NullEdge;
class EdgeEqualTo;
class Edge
{
public:
	Edge();
	Edge(int initialFirstCharIndex, int initialLastCharIndex, int parentNode,
			int endNode, char firstChar);

	static int Hash(int node, int c);
	int getFirstCharIndex() const;
	void setFirstCharIndex(int firstCharIndex, char c);

	int getLastCharIndex() const;
	void setLastCharIndex(int firstCharIndex);

	void setFirstChar(char c);
	char getFirstChar() const;

	int getStartNode() const;
	void setStartNode(int node);

	const int getEndNode() const;

	bool isNull() const;
private:
	friend class EdgeEqualTo;
	Edge& operator=(const Edge& value);

	int d_firstCharIndex;
	int d_lastCharIndex;

	int d_startNode;
	const int d_endNode;

	char d_firstChar;
};

struct EdgeHash: public std::unary_function<Edge, std::size_t>
{
	inline std::size_t operator()(Edge const& edge) const
	{
		std::size_t seed = 0;
		boost::hash_combine(seed, edge.getStartNode());
		boost::hash_combine(seed, edge.getFirstChar());
		return seed;
	}
};

struct EdgeEqualTo: public std::binary_function<Edge, Edge, bool>
{
	inline bool operator()(const Edge & a, const Edge & b) const
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

inline void Edge::setFirstCharIndex(int index, char c)
{
	this->d_firstCharIndex = index;
	this->d_firstChar = c;
}

inline int Edge::getFirstCharIndex() const
{
	return d_firstCharIndex;
}

inline int Edge::getLastCharIndex() const
{
	return d_lastCharIndex;
}

inline void Edge::setLastCharIndex(int index)
{
	d_lastCharIndex = index;
}

inline void Edge::setFirstChar(char c)
{
	d_firstChar = c;
}
inline char Edge::getFirstChar() const
{
	return d_firstChar;
}

inline int Edge::getStartNode() const
{
	return d_startNode;
}

inline void Edge::setStartNode(int node)
{
	d_startNode = node;
}

inline const int Edge::getEndNode() const
{
	return d_endNode;
}

inline bool Edge::isNull() const
{
	return (d_startNode == -1);
}

#endif
