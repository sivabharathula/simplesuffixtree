#ifndef __EDGE_H
#define __EDGE_H

#include <functional>
#include <boost/functional/hash.hpp>
#include <boost/utility.hpp>

class NullEdge;
class EdgeEqualTo;
class Edge{
	friend class EdgeEqualTo;
	Edge& operator=(const Edge& value);
public:
	Edge();
	Edge(int initialFirstCharIndex, int initialLastCharIndex, int parentNode, int endNode, char firstChar);

	//Edge(const Edge& value);

	static int Hash(int node, int c);
	int getFirstCharIndex() const;
	void setFirstCharIndex(int firstCharIndex, char c);
	void setFirstChar(char c);
	char getFirstChar() const;
private:
	int firstCharIndex;
	char firstChar;
public:
	int lastCharIndex;
	int startNode;
	const int endNode;
};


struct EdgeHash: public std::unary_function<Edge, std::size_t> {

  inline std::size_t operator()(Edge const& edge) const
		  {
			  boost::hash<std::size_t> hasher;
			  char c = edge.getFirstChar();
			  return hasher((edge.startNode<<8) | c );
		  }
};

struct EdgeEqualTo: public std::binary_function<Edge, Edge, bool> {
	inline bool operator()(const Edge & a,const Edge & b) const {
		if (a.startNode == b.startNode)
		{
			if (b.firstChar == a.firstChar)
			{
				return true;
			}
		}

		return false;
	}

};

#endif
