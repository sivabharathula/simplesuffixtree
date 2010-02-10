/*
 * SuffixTree.h
 *
 *  Created on: Feb 9, 2010
 *      Author: Piotr Zemczak
 */

#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <map>
#include <boost/unordered_set.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>

#ifndef __SUFFIX_H
#include "Suffix.h"
#endif

#ifndef __EDGE_H
#include "Edge.h"
#endif

#ifndef NULLEDGE_H_
#include "NullEdge.h"
#endif

#ifndef __NODE_H
#include "Node.h"
#endif

#ifndef SUFFIXTREETYPETRAITS_H_
#include "SuffixTreeTypeTraits.h"
#endif

/**
 * \brief Klasa szablonowa drzewa suffixów.
 * \param T typ zmiennej przechowywującej rozmiar tekstu.
 * \param stringT Typ zmiennej reprezentującej łańcuch znaków
 * \param Traits parametr z cechami typów stosowanych w drzewie.
 */
template<typename T = unsigned int, typename stringT = std::string,
		typename Traits = SuffixTreeTraits<T, typename stringT::value_type> >
class SuffixTreeTemplate
{
public:
	/// Typ zmiennej wskazującej numer węzła-Node
	typedef typename Traits::NodeT NodeT;
	/// Typ zmiennej wskazującej pozycję w tekscie
	typedef typename Traits::IndT IndT;
	/// Typ zmiennej wskazującej różnicę pomiędzy IndT
	typedef typename Traits::IndT_diff IndT_diff;
	/// Typ pojedynczego znaku tekstu
	typedef typename Traits::CharT CharT;

	/// Eddge typ specjalizacji krawędzi wykorzystywanej w drzewie.
	typedef EdgeTemplate<Traits> Edge;
	/// Node typ specjalizacji węzła wykorzystywanego w drzewie.
	typedef NodeTemplate<Traits> Node;
	/// NodeNull typ specjalizacji węzła pustego wykorzystywanego w drzewie.
	typedef NullEdgeTemplate<Traits> NullEdge;
	/// Typ reprezentujący suffix
	typedef SuffixTemplate<Traits> Suffix;
	/// Nazwa typu literału łańcuchowego
	typedef stringT sufstring;

	/// Liczba reprezentująca pozycję poza tekstem
	static const IndT INDEX_OUT = Traits::OUT_OF_RANGE;

	/*** Iterator definition  *************************************************************/
	class SuffixIterator;
	friend class SuffixTreeTemplate::SuffixIterator;
	class SuffixIterator: public std::iterator<std::random_access_iterator_tag,
			T>
	{

		friend class SuffixTreeTemplate;
		SuffixIterator(SuffixTreeTemplate& parent, IndT pos = 0) :
			d_pos(pos), d_parent(parent)
		{
		}
	public:
		SuffixIterator(const SuffixIterator& it) :
			d_pos(it.d_pos), d_parent(it.d_parent)
		{
		}
		SuffixIterator& operator++()
		{
			++d_pos;
			return *this;
		}

		const SuffixIterator& operator++() const
		{
			IndT* pos = const_cast<IndT*> (&d_pos);
			++(*pos);
			return *this;
		}

		SuffixIterator& operator++(int)
		{
			SuffixIterator copy(*this);
			++*this;
			return *copy;
		}

		const SuffixIterator& operator++(int) const
		{
			const SuffixIterator copy(*this);
			++*this;
			return *copy;
		}

		bool operator==(const SuffixIterator& rhs)
		{
			assert(&d_text == &rhs.d_text);
			return this->d_pos == rhs.d_pos;
		}

		bool operator!=(const SuffixIterator& rhs) const
		{
			assert(&d_parent == &rhs.d_parent);
			return this->d_pos != rhs.d_pos;
		}

		boost::iterator_range<typename sufstring::iterator> operator*()
		{
			sufstring& text = const_cast<sufstring&> (d_parent.d_text);

			return boost::iterator_range<typename sufstring::iterator>(
					text.begin() + d_pos, text.end());
		}

		boost::iterator_range<typename sufstring::const_iterator> operator*() const
		{
			return boost::iterator_range<typename sufstring::const_iterator>(
					d_parent.d_text.begin() + d_pos, d_parent.d_text.end());
		}

	private:
		IndT d_pos;
		SuffixTreeTemplate& d_parent;
	};

	/// Typ iteratora do przechodzenia po suffixach
	typedef SuffixIterator iterator;
	/// Typ iteratora do przechodzenia po suffixach
	typedef const SuffixIterator const_iterator;

	/// Zwraca iterator na pierwszy suffix
	const_iterator begin() const;
	/// Zwraca iterator na suffix za ostatnim
	const_iterator end() const;

	iterator begin();
	iterator end();

	/*** End of Iterator definition  *************************************************************/

	/**
	 * Konstruktor tworzy drzewo suffixów.
	 * \param inputText - tekst, który ma być dodany do drzewa suffixów.
	 */
	SuffixTreeTemplate(const sufstring& inputText);
	~SuffixTreeTemplate();

	/**
	 * Metoda stwierdza czy tekst znajduje się w drzewie.
	 * \param text do wyszukania
	 * \return true jeśli tekst został znaleziony
	 */
	bool isSuffix(const sufstring& text);

	/**
	 * Metoda wyświetla wszystkie krawędzi
	 * \param current_n maksymalny rozmiar tekstu,
	 * który może być wyświetlony jeśli na krawędzi znajduje się dłuższy tekst
	 */
	void dumpEdges(int current_n);

	/**
	 * Metoda dodaje tekst do drzewa suffixów.
	 */
	void addText(const sufstring& t);

private:
	/**
	 * Metoda sprawdza, czy tekst wskazany przez parę iteratorów znajduje się w drzewie.
	 * \param begin - iterator wskazujący początek tekstu.
	 * \param end - iterator wskazujący koniec tekstu.
	 * \param node węzeł od którego ma być rozpoczęte szukanie tekstu.
	 *  Parametr wykorzystywany w rekurencyjnym wywoływaniu metody.
	 *  \return true jeśli tekst został znaleziony
	 */
	bool isSuffix(typename sufstring::const_iterator begin,
			typename sufstring::const_iterator end, NodeT node = 0);

	/// Typ tablicy haszującej. Zawierającej krawędzie.
	typedef boost::unordered_set<Edge, EdgeHash<Edge> , EdgeEqualTo<Edge> >
			EdgeHashSet;

	/// Typ określającyy obiekt przetrzymujący Węzły.
	typedef std::map<NodeT, Node> NodeMap;

	/// Metoda dodająca znak do drzewa suffixów.
	void addPrefix(Suffix &active, IndT lastCharIndex);
	/// Metoda umieszcza krawędź w tablicy mieszającej
	void insert(Edge &edge);
	/// Metoda usuwa krawędź z tablicy mieszającej
	void remove(Edge &edge);
	///Metoda wyszukuje w tablicy mieszającej
	Edge& find(NodeT nodeParent, CharT firstCharOnEdge);

	NodeT splitEdge(Suffix &suffix, Edge edge);

	/**
	 * Przekształca suffix do postaci kannonicznej
	 *
	 */
	void canonize(Suffix& suffix);

	/// Tekst na którym operuje drzewo suffixów.
	const sufstring& d_text;
	Suffix d_active;
	///tablica mieszająca zawierajaca krawędzie drzewa
	EdgeHashSet d_edges;
	/// Kontener zawierający węzły drzewa
	NodeMap d_nodes;

};

template<typename T, typename T2, typename T3>
SuffixTreeTemplate<T, T2, T3>::SuffixTreeTemplate(const sufstring& inputText) :
	d_text(inputText), d_active(0, 0, INDEX_OUT)
{
#ifndef NDEBUG
	std::cout << "Sizeof Node"<< sizeof(Node) <<std::endl;
	std::cout << "Sizeof Node field "<< sizeof(NodeT) <<std::endl;
	std::cout << "Sizeof Edge"<< sizeof(Edge) <<std::endl;
#endif

	Node zero_Node(0);
	d_nodes[0] = zero_Node;

	for (unsigned int i = 0; i <= d_text.length(); ++i)
	{
		addPrefix(d_active, i);
	}
}

template<typename T, typename T2, typename T3>
SuffixTreeTemplate<T, T2, T3>::~SuffixTreeTemplate()
{
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::addPrefix(Suffix &active,
		IndT lastCharIndex)
{
	NodeT parentNode;
	NodeT lastParentNode = Node::EMPTY;

	for (;;)
	{
		parentNode = active.getOriginNode();

		if (active.isExplicit())
		{
			Edge& tmpEdge = find(d_active.getOriginNode(),
					d_text[lastCharIndex]);
			if (!tmpEdge.isNull())
			{
				break;
			}
		}
		else
		{
			Edge& tmpEdge = find(d_active.getOriginNode(),
					d_text[d_active.getFirstCharIndex()]);
			IndT_diff span = d_active.getLastCharIndex()
					- d_active.getFirstCharIndex();

			if (d_text[tmpEdge.getFirstCharIndex() + span + 1]
					== d_text[lastCharIndex])
			{
				break;
			}

			parentNode = splitEdge(d_active, tmpEdge);
		}

		Edge newEdge(lastCharIndex, d_text.length(), parentNode,
				d_nodes.size(), d_text[lastCharIndex]);
		assert(d_nodes.find(d_nodes.size()) == d_nodes.end());
		d_nodes[d_nodes.size()] = Node();
		insert(newEdge);

		if (lastParentNode > 0)
		{
			d_nodes[lastParentNode].setSuffixNode(parentNode);
		}

		lastParentNode = parentNode;

		if (d_active.getOriginNode() == 0)
		{
			d_active.setFirstCharIndex(d_active.getFirstCharIndex() + 1);
		}
		else
		{
			d_active.setOriginNode(
					d_nodes[d_active.getOriginNode()].getSuffixNode());
		}

		canonize(d_active);
	}

	if (lastParentNode > 0)
	{
		d_nodes[lastParentNode].setSuffixNode(parentNode);
	}

	d_active.setLastCharIndex(d_active.getLastCharIndex() + 1);
	canonize(d_active);
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::canonize(Suffix& suffix)
{
	if (!suffix.isExplicit())
	{

		Edge* edge = &(find(suffix.getOriginNode(),
				d_text[suffix.getFirstCharIndex()]));
		IndT_diff edge_span = edge->getLastCharIndex()
				- edge->getFirstCharIndex();
		while (edge_span <= static_cast<IndT_diff> (suffix.getLastCharIndex()
				- suffix.getFirstCharIndex()))
		{

			suffix.setFirstCharIndex(suffix.getFirstCharIndex() + edge_span + 1);
			suffix.setOriginNode(edge->getEndNode());

			//if ( suffix.getFirstCharIndex() <= suffix.getLastCharIndex()) {
			if (suffix.isImplicit())
			{
				edge = &(find(edge->getEndNode(),
						d_text[suffix.getFirstCharIndex()]));
				edge_span = edge->getLastCharIndex()
						- edge->getFirstCharIndex();
			};
		}
	}
}

template<typename T, typename T2, typename T3>
typename SuffixTreeTemplate<T, T2, T3>::Edge& SuffixTreeTemplate<T, T2, T3>::find(
		NodeT nodeParent, CharT firstCharOnEdge)
{
	Edge mockEdge(0, 0, nodeParent, Node::EMPTY, firstCharOnEdge);
	typename EdgeHashSet::const_iterator cit = d_edges.find(mockEdge);
	if (cit == d_edges.end())
	{
		return NullEdge::getNull();
	}
	return const_cast<Edge&> (*cit);
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::insert(Edge& edge)
{
	d_edges.insert(edge);
	assert(d_edges.find(edge) != d_edges.end());
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::remove(Edge& edge)
{
	d_edges.erase(edge);
}

template<typename T, typename T2, typename T3>
typename SuffixTreeTemplate<T, T2, T3>::NodeT SuffixTreeTemplate<T, T2, T3>::splitEdge(
		Suffix &suffix, Edge edge)
{
	remove(edge);

	Edge newEdge(edge.getFirstCharIndex(), edge.getFirstCharIndex()
			+ suffix.getLastCharIndex() - suffix.getFirstCharIndex(),
			suffix.getOriginNode(), d_nodes.size(), edge.getFirstChar());

	assert(edge.getFirstChar() == d_text[edge.getFirstCharIndex()]);
	assert(d_nodes.find(d_nodes.size()) == d_nodes.end());
	d_nodes[(int) d_nodes.size()] = Node();

	insert(newEdge);

	d_nodes[newEdge.getEndNode()].setSuffixNode(suffix.getOriginNode());
	int index = edge.getFirstCharIndex() + suffix.getLastCharIndex()
			- suffix.getFirstCharIndex() + 1;

	assert((index >=0) && (index < static_cast<int>(d_text.length())));

	edge.setFirstCharIndex(index, d_text[index]);
	edge.setStartNode(newEdge.getEndNode());

	insert(edge);

	return newEdge.getEndNode();
}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::dumpEdges(int current_n)
{

	std::cout << " Start  End  Suf  First Last  String\n";
	for (typename EdgeHashSet::const_iterator cit = d_edges.begin(); cit
			!= d_edges.end(); ++cit)
	{
		const Edge* s = &(*cit);
		if (s->isNull())
			continue;
		std::cout << std::setw(5) << s->getStartNode() << " " << std::setw(5)
				<< s->getEndNode() << " " << std::setw(3)
				<< d_nodes[s->getEndNode()].getSuffixNode() << " "
				<< std::setw(5)
				<< static_cast<unsigned long long> (s->getFirstCharIndex())
				<< " " << std::setw(6)
				<< static_cast<unsigned long long> (s->getLastCharIndex())
				<< "  ";
		int top;
		if (current_n > static_cast<int> (s->getLastCharIndex()))
			top = s->getLastCharIndex();
		else
			top = current_n;

		std::wcout << d_text.substr(s->getFirstCharIndex(), top).c_str()
				<< std::endl;

	}

	std::cout << "Active :" << d_active.getOriginNode() << " "
			<< static_cast<unsigned long long> (d_active.getFirstCharIndex())
			<< " "
			<< static_cast<unsigned long long> (d_active.getLastCharIndex())
			<< std::endl;

}

template<typename T, typename T2, typename T3>
void SuffixTreeTemplate<T, T2, T3>::addText(const sufstring& t)
{
	int oldLength = d_text.length();
	sufstring& s = const_cast<sufstring&> (d_text);
	s += t;
	for (unsigned int i = oldLength; i < d_text.length(); ++i)
	{
		addPrefix(d_active, i);
	}
}

template<typename T, typename T2, typename T3>
bool SuffixTreeTemplate<T, T2, T3>::isSuffix(const sufstring& text)
{
	return isSuffix(text.begin(), text.end());
}

template<typename T, typename T2, typename T3>
bool SuffixTreeTemplate<T, T2, T3>::isSuffix(
		typename sufstring::const_iterator begin,
		typename sufstring::const_iterator end, NodeT node)
{
	boost::iterator_range<typename sufstring::const_iterator> testText =
			boost::make_iterator_range(begin, end);
#ifndef NDEBUG
	std::cout << "Find " << boost::make_iterator_range(begin, end) << std::endl;
#endif

	Edge& e = find(node, *begin);//znajdz suffix zaczynajacy sie w node na literze *begin
	if (e.isNull())
	{
		return false;
	}

	int endNode = e.getEndNode();
	int firstChar = e.getFirstCharIndex();
	int lastChar = e.getLastCharIndex();

	boost::iterator_range<typename sufstring::const_iterator> subText =
			boost::make_iterator_range(d_text.begin() + firstChar,
					d_text.begin() + lastChar + 1);

#ifndef NDEBUG
	std::cout << " test " << testText << " subText" << subText << std::endl;
#endif
	if (subText.size() < testText.size())
	{
		if (boost::starts_with(testText, subText))
		{
			return isSuffix(begin + subText.size(), end, endNode);
		}
		else
		{
			return false;
		}
	}
	else if (boost::starts_with(subText, testText))
	{
		return true;
	}

	return false;
}

template<typename T, typename T2, typename T3>
typename SuffixTreeTemplate<T, T2, T3>::const_iterator SuffixTreeTemplate<T,
		T2, T3>::begin() const
{
	const_iterator cit(*this);
	return cit;
}
template<typename T, typename T2, typename T3>
typename SuffixTreeTemplate<T, T2, T3>::const_iterator SuffixTreeTemplate<T,
		T2, T3>::end() const
{
	const_iterator cit(*this);
	cit.d_pos = d_text.length();
	return cit;
}

template<typename T, typename T2, typename T3>
typename SuffixTreeTemplate<T, T2, T3>::iterator SuffixTreeTemplate<T, T2, T3>::begin()
{
	return iterator(*this);
}
template<typename T, typename T2, typename T3>
typename SuffixTreeTemplate<T, T2, T3>::iterator SuffixTreeTemplate<T, T2, T3>::end()
{
	iterator it(*this, d_text.length());
	return it;
}

#endif

