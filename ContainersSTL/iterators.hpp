#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include "utility.hpp"
#include "redBlackTree.hpp"

namespace ft{

/*********************************************/
/*********** Iterator for vector *************/
/*********************************************/

template <typename U>
class IteratorVector : iterator<std::random_access_iterator_tag, U> {
public:
	typedef typename iterator<std::random_access_iterator_tag, U>::value_type		value_type;
	typedef typename iterator<std::random_access_iterator_tag, U>::difference_type		difference_type;
	typedef typename iterator<std::random_access_iterator_tag, U>::pointer			pointer;
	typedef typename iterator<std::random_access_iterator_tag, U>::reference		reference;
	typedef typename iterator<std::random_access_iterator_tag, U>::iterator_category	iterator_category;
	typedef pointer																		iterator_type;																
private:
	pointer _pointer;
public:
	IteratorVector() : _pointer(nullptr) {}
	IteratorVector(pointer p) : _pointer(p) {}
	template <typename _U>
	IteratorVector(const IteratorVector<_U>& it) : _pointer(&(*it)) {}
	~IteratorVector() {}
	IteratorVector& operator=(const IteratorVector& it) {
		if (this == &it) return *this;
		_pointer = it._pointer;
		return *this;
	}
	reference operator*() {return *_pointer; }
	const reference operator*() const {return *_pointer; }
	pointer operator->() { return _pointer; }
	const pointer operator->() const  { return _pointer; }
	reference operator[](difference_type i) { return *(_pointer + i); }
	IteratorVector& operator++() { ++_pointer; return *this; }
	IteratorVector operator++(int) { IteratorVector copy(*this); ++_pointer; return copy; }
	IteratorVector& operator--() { --_pointer; return *this; }
	IteratorVector operator--(int) { IteratorVector copy(*this); --_pointer; return copy; } 
	IteratorVector& operator+=(const difference_type& i) { _pointer += i; return *this; }
	IteratorVector& operator-=(const difference_type& i) { _pointer -= i; return *this; }
	IteratorVector operator+(const difference_type& i) const { return _pointer + i; }
	IteratorVector operator-(const difference_type& i) const { return _pointer - i; }
	difference_type operator-(const IteratorVector& r) const { return _pointer - r._pointer;}

	template <typename T1, typename T2> 
	friend bool operator==(const IteratorVector<T1>& x, const IteratorVector<T2>& y) { return x._pointer == y._pointer; }
	template <typename T1, typename T2> 
	friend bool operator!=(const IteratorVector<T1>& x, const IteratorVector<T2>& y) { return !(x._pointer == y._pointer); }
	template <typename T1, typename T2> 
	friend bool operator<(const IteratorVector<T1>& x, const IteratorVector<T2>& y) { return x._pointer < y._pointer; }
	template <typename T1, typename T2> 
	friend bool operator>(const IteratorVector<T1>& x, const IteratorVector<T2>& y) { return y._pointer < x._pointer; }
	template <typename T1, typename T2> 
	friend bool operator<=(const IteratorVector<T1>& x, const IteratorVector<T2>& y) { return !(y._pointer < x._pointer); }
	template <typename T1, typename T2> 
	friend bool operator>=(const IteratorVector<T1>& x, const IteratorVector<T2>& y) { return !(x._pointer < y._pointer); }
};

/*********************************************/
/************ Iterator for tree **************/
/*********************************************/

template <typename U>
class IteratorTree : iterator<std::bidirectional_iterator_tag, U> {
public:
	typedef U										iterator_type;
	typedef typename iterator<std::bidirectional_iterator_tag, U>::value_type		value_type;
	typedef typename iterator<std::bidirectional_iterator_tag, U>::difference_type		difference_type;
	typedef typename iterator<std::bidirectional_iterator_tag, U>::pointer			pointer;
	typedef typename iterator<std::bidirectional_iterator_tag, U>::reference		reference;
	typedef typename iterator<std::bidirectional_iterator_tag, U>::iterator_category	iterator_category;
	typedef redBlackTreeNode<typename std::remove_const<value_type>::type>*			node_pointer;
private:
	node_pointer _pointer;
public:
	IteratorTree() : _pointer(nullptr) {}
	IteratorTree(const node_pointer& p) : _pointer(p) {}
	template <typename _U>
	IteratorTree(const IteratorTree<_U>& it) : _pointer(reinterpret_cast<node_pointer>(&(*it))) {}
	~IteratorTree() {}
	IteratorTree& operator=(const IteratorTree& it) {
		if (this == &it) return *this;
		_pointer = it._pointer;
		return *this;
	}
	reference operator*() {return (_pointer->_value); }
	const reference operator*() const {return (_pointer->_value); }
	pointer operator->() {return &(_pointer->_value); }
	const pointer operator->() const {return &(_pointer->_value); }
	IteratorTree& operator++() { _pointer = _pointer->increment(); return *this; }
	IteratorTree operator++(int) { IteratorTree copy(*this); _pointer = _pointer->increment(); return copy; }
	IteratorTree& operator--() { _pointer = _pointer->dicrement(); return *this; }
	IteratorTree operator--(int) { IteratorTree copy(*this); _pointer = _pointer->dicrement(); return copy; }
	operator node_pointer() { return _pointer; }
	template <typename T1, typename T2> 
	friend bool operator==(const IteratorTree<T1>& x, const IteratorTree<T2>& y) { return x._pointer == y._pointer; }
	template <typename T1, typename T2> 
	friend bool operator!=(const IteratorTree<T1>& x, const IteratorTree<T2>& y) { return !(x._pointer == y._pointer); }
};

/*********************************************/
/************* Reverse Iterator **************/
/*********************************************/

template <typename Iterator>
class ReverseIterator {
public:
	typedef Iterator						iterator_type;
	typedef typename iterator_traits<Iterator>::value_type		value_type;
	typedef typename iterator_traits<Iterator>::pointer		pointer;
	typedef typename iterator_traits<Iterator>::reference		reference;
	typedef typename iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
private:
	Iterator _iter;
public:
	ReverseIterator() : _iter() {}
	explicit ReverseIterator(const Iterator& iter) : _iter(iter) {}
	template <typename _U>
	ReverseIterator(const ReverseIterator<_U>& it) : _iter(it.base()) {}
	~ReverseIterator() {}
	template <typename _U>
	ReverseIterator& operator=(const ReverseIterator<_U>& it) {
		if (it == *this) return *this;
		_iter = it._iter;
		return *this;
	}
	Iterator base() const { return _iter; }
	reference operator*() { return *(_iter); }
	pointer operator->() { return &(operator*()); }
	reference operator[](difference_type i) { return *(_iter - i - 1); }
	ReverseIterator& operator++() { --_iter; return *this; }
	ReverseIterator operator++(int) { ReverseIterator copy(*this); --_iter; return copy; }
	ReverseIterator& operator--() { ++_iter; return *this; }
	ReverseIterator operator--(int) { ReverseIterator copy(*this); ++_iter; return copy; }
	ReverseIterator operator+(const difference_type& i) const { return ReverseIterator(_iter - i); }
	ReverseIterator& operator+=(const difference_type& i) const { _iter -= i; return *this; }
	ReverseIterator& operator-=(const difference_type& i) const { _iter += i; return *this; }
	ReverseIterator operator-(const difference_type& i) const { return ReverseIterator(_iter + i); }

	template <typename T1, typename T2> 
	friend bool operator==(const ReverseIterator<T1>& x, const ReverseIterator<T2>& y) { return x._iter == y._iter; }
	template <typename T1, typename T2> 
	friend bool operator!=(const ReverseIterator<T1>& x, const ReverseIterator<T2>& y) { return !(x._iter == y._iter); }
	template <typename T1, typename T2> 
	friend bool operator<(const ReverseIterator<T1>& x, const ReverseIterator<T2>& y) { return y._iter < x._iter; }
	template <typename T1, typename T2> 
	friend bool operator>(const ReverseIterator<T1>& x, const ReverseIterator<T2>& y) { return x._iter < y._iter; }
	template <typename T1, typename T2> 
	friend bool operator<=(const ReverseIterator<T1>& x, const ReverseIterator<T2>& y) { return !(x._iter < y._iter); }
	template <typename T1, typename T2> 
	friend bool operator>=(const ReverseIterator<T1>& x, const ReverseIterator<T2>& y) { return !(y._iter < x._iter); }

};

}

#endif
