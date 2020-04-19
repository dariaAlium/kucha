#include "Header.h"
#include <iostream>
using namespace std;

template <typename Type>
Node<Type>::Node(Type item, Node<Type>* parent) {
	this->item = item;
	left = nullptr;
	right = nullptr;
	this->parent = parent;
}

template <typename Type>
Node<Type>::Node() {
	item = NULL;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

template <typename Type>
Node<Type>::Node(const Node<Type>& node) {
	node->item = item;
	node->parent = parent;
	node->left = left;
	node->right = right;
}

template <typename Type>
Node<Type>::~Node() {
}

template <typename Type>
Tree<Type>::Tree(Type item) {
	root = new Node<Type>(item, nullptr);
	root->parent = root;
	added = root;
	level = 0;
}

template <typename Type>
void Tree<Type>::sift_up(){
	Node<Type>* tmp_added = added;
	while (tmp_added->item > tmp_added->parent->item) {
		Type tmp = tmp_added->item;
		Type p_tmp = tmp_added->parent->item;
		tmp_added->item = tmp_added->parent->item;
		tmp_added->parent->item = tmp;
		tmp_added = tmp_added->parent;
	}

}

template <typename Type>
void Tree<Type>::change_added() {
	if (root->left == nullptr && root->right == nullptr) //if there are only root
		return;
	if (added->parent->right == added) { //был справа, сейчас слева
		added = added->parent->left;
		return;
	}
	
	Node<Type>* tmp = added;

	while (tmp->parent->right != tmp) {
		tmp = tmp->parent;
		//когда самый крайний
		if (tmp == root)
		{
			while (tmp->right->right != 0)
				tmp = tmp->right;
			added = tmp->right;
			level--;
			return;
		}
	}
	tmp = tmp->parent->left;
	if (tmp->right != nullptr) {
		while (tmp->right->right != nullptr)
			tmp = tmp->right;
		added = tmp->right->right;
	}
	else 
		added = tmp->right;
}

template <typename Type>
void Tree<Type>::sift_down(Node<Type>* deleted) {
	Type last_added = added->item;
		while (deleted->left != nullptr) {
			Type tmp = deleted->item;
			if (deleted->left->item > deleted->item) {
				deleted->item = deleted->left->item;
				deleted->left->item = tmp;
				deleted = deleted->left;
			}
			else { //если правый больше левого
				deleted->item = deleted->right->item;
				deleted->right->item = tmp;
				deleted = deleted->right;
			}
			

		}
}

template <typename Type>
void Tree<Type>::add(Type item){
	//когда только корень
	if (root->left == 0) { 
		added->left = 
			new Node<Type>(item, root);
		added = root->left;
		level++;
		return;
	}
		//когда в одной ветке
	if (added->parent->right == nullptr) {
		added->parent->right = new Node<Type>(item, added->parent);
		added = added->parent->right;
		sift_up();
		return;
	}
	
	Node<Type>* tmp = added;
	
	while (tmp->parent->left != tmp) {
		tmp = tmp->parent;
		//когда самый крайний
		if (tmp == root)
		{
			while (tmp->left->left != 0)
				tmp = tmp->left;
			tmp->left->left = new Node<Type>(item, tmp->left);
			added = tmp->left->left;
			level++;
			sift_up();
			return;
		}
	}
	tmp = tmp->parent->right;
	if (tmp->left != nullptr) {
		while (tmp->left->left != nullptr)
			tmp = tmp->left;
		tmp->left->left = new Node<Type>(item, tmp->left);
		added = tmp->left->left;
	}
	else {
		tmp->left = new Node<Type>(item, tmp);
		added = tmp->left;
	}

	sift_up();
}

template <typename Type>
void Tree<Type>::del(Node<Type>* t, Type item) {

	if (t != NULL) {
		if (t->item == item) {

			if (t == root && t->left == nullptr && t->right == nullptr)
				throw exception();
				
			t->item = added->item;
			Node<Type>* tmp = added;
			change_added();
			if (tmp->parent->right == tmp)
				tmp->parent->right = nullptr;
			else
				tmp->parent->left = nullptr;
			
			sift_down(t);
			t = t->parent;
			
		}
		del(t->left, item);
		del(t->right, item);

		
	}
}


template <typename Type>
Node<Type>* Tree<Type>::find(Node<Type> *t, Type item) {
	
	if (t != NULL) {

		if (find(t->right, item) == nullptr){
if (t->item == item) 
		  return t;
			return find(t->left, item);
		
		
		}
	}
	return t;
}

template <typename Type>
void Tree<Type>::print(Node<Type>* t, int level){
	if (t == nullptr) 
		return; 
	else {
		print(t->left, level - 1); 
		if (level == 0) 
			cout << t->item << "; "; 
		print(t->right, level - 1);  
	}
}

template <typename Type>
void Tree<Type>::destroy(Node<Type>* n)  // Удаление дерева
{
	if (n != NULL)
	{
		Node<Type>* r = n->right;
		Node<Type>* l = n->left;
		destroy(r);
		destroy(l);
		delete n;
		n = NULL;
	}
}

template <typename Type>
Tree<Type>::~Tree() {
	
	destroy(root);
}

template <typename Type>
Node<Type>* Tree<Type>::get_last_added() {
	return added;
}

template <typename Type>
Node<Type>* Tree<Type>::get_root() {
	return root;
}

template <typename Type>
int Tree<Type>::get_level() {
	return level;
}

int main(){
	/*
	Tree<int> check(6);
	check.add(6);
	check.add(5);
	try {
		check.del(check.get_root(), 6);
	}
	catch (exception a) {
		cout << "You r trying to delete last item. M b you should exit?" << endl;
	}
	for (int i = 0; i <= check.get_level(); i++) {
		cout << i << ":";
		check.print(check.get_root(), i);
		cout << endl;
	}
	*/
	
	int num;
	int choice = 0;
	cout << "Welcome to the KUCHA" << "First, you should put there any num:";
	cin >> num;
	Tree<int> check(num);
	while (choice != 5) {
		cout << "What do u wanna to do:" << endl << "1. add new num" << endl << "2. delete all num eq to" << endl << "3. find num" << endl
			<< "4. print tree" << "5. exit" <<endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Add item:" << endl;
			cin >> num;
			check.add(num);
			break;
		case 2:
			cout << "Num:" << endl;
			cin >> num;
			try {
				check.del(check.get_root(), num);
			}
			catch (exception a) {
				cout << "You r trying to delete last item. M b you should exit?"<<endl;
			}
			break;
		case 3:
			cout << "Num:" << endl;
			cin >> num;
			if (check.find(check.get_root(), num))
				cout << "YES"<<endl;
			else
				cout << "NO"<<endl;
			break;
		case 4:
			for (int i = 0; i <= check.get_level(); i++) {
					cout << i << ":";
					check.print(check.get_root(), i);
					cout << endl;
				}
			break;
		case 5:
			cout << "FINALLY";
		}
	}


	
	
	/*bool result = false;*/
	//check.find(result, check.get_root(), 36);
	
	return 0;
}