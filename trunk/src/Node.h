#ifndef __NODE_H
#define __NODE_H

template<typename Traits>
class NodeTemplate
{
public:
	typedef typename Traits::NodeT NodeT;
	const static NodeT EMPTY = Traits::EMPTY_NODE ;

	NodeTemplate();
	NodeTemplate(NodeT suffixNode);

	NodeT getSuffixNode() const;
	void setSuffixNode(NodeT suffixNode);

private:
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

