#pragma once
#ifndef Header
#define Heder
template <typename Type>

class Node {
public:
	Type item;
	Node<Type>* left;
	Node<Type>* right;
	Node<Type>* parent;

	Node(Type name, Node<Type>* parent);
	Node(const Node<Type>&);
	Node();
	~Node();
};

template <typename Type>

class Tree {
	Node<Type>* root;
	Node<Type>* added;
	int level;
	void sift_up();
	void sift_down(Node<Type>*);
	void change_added();
	void destroy(Node<Type>* t);
public:

	Tree(Type item);
	void add(Type item);
	void del(Node<Type>*, Type item);
	Node<Type>* find(Node<Type>* root,Type item);
	void print(Node<Type>* t, int level);
	
	
	~Tree();
	
	Node<Type>* get_last_added();
	Node<Type>* get_root();
	int get_level();

};
#endif