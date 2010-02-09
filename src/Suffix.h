#ifndef __SUFFIX_H
#define __SUFFIX_H




template<typename SuffixTraits>
class SuffixTemplate
{
public:
	typedef typename SuffixTraits::NodeT NodeT;
	typedef typename SuffixTraits::IndT IndT;
	static const IndT INDEX_OUT = SuffixTraits::OUT_OF_RANGE;

	SuffixTemplate(NodeT node, IndT start, IndT stop);

	bool isExplicit();
	bool isImplicit();

	IndT getFirstCharIndex() const;
	void setFirstCharIndex(IndT index);

	IndT getLastCharIndex() const;
	void setLastCharIndex(IndT index);

	NodeT getOriginNode() const;
	void setOriginNode(NodeT node);

private:
	NodeT d_originNode;
	IndT d_firstCharIndex;
	IndT d_lastCharIndex;
};

template<typename T>
SuffixTemplate<T>::SuffixTemplate(NodeT node, IndT start, IndT stop) :
	d_originNode(node), d_firstCharIndex(start), d_lastCharIndex(stop)
{
}

template<typename T>
bool SuffixTemplate<T>::isExplicit()
{

	if (d_lastCharIndex == INDEX_OUT)

	{
		return true;
	}
	return d_firstCharIndex > d_lastCharIndex;
}

template<typename T>
bool SuffixTemplate<T>::isImplicit()
{
	if (d_lastCharIndex == INDEX_OUT)

	{
		return false;
	}
	return d_lastCharIndex >= d_firstCharIndex;
}

template<typename T>
typename SuffixTemplate<T>::IndT SuffixTemplate<T>::getFirstCharIndex() const
{
	return d_firstCharIndex;
}

template<typename T>
void SuffixTemplate<T>::setFirstCharIndex(IndT index)
{
	d_firstCharIndex = index;
}

template<typename T>
typename SuffixTemplate<T>::IndT SuffixTemplate<T>::getLastCharIndex() const
{
	return d_lastCharIndex;
}

template<typename T>
void SuffixTemplate<T>::setLastCharIndex(IndT index)
{
	d_lastCharIndex = index;
}

template<typename T>
typename SuffixTemplate<T>::NodeT SuffixTemplate<T>::getOriginNode() const
{
	return d_originNode;
}

template<typename T>
void SuffixTemplate<T>::setOriginNode(NodeT node)
{
	d_originNode = node;
}

#endif

