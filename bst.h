#ifndef BINARYSEARCHITEM_H
#define BINARYSEARCHITEM_H

#include<functional>
#include<iostream>
#include<assert.h>

template<typename Type>
struct Node {
	Node(Type i, Node* l, Node* r) :item(i), left(l), right(r) {}
	Node() :Node(0, nullptr, nullptr) {}

	Type item;
	Node* left, *right;
};

template<typename Type>
class BinarySearchTree {

public:
	BinarySearchTree();
	~BinarySearchTree();

	void	printInorder() const;
	void	printPostorder() const;
	void	printPreorder() const;
	void	insert(Type item);

	void	remove(Type item);

	Type	min() const;
	Type	max() const;
	int		height() const;
	bool	search(Type item) const;

	bool	empty() const;

	void	printTree() const;

private:

	// Member variable root
	Node<Type>* root;

	//Auxillary recursive bst functions
	//public interface functions call these

	// Tree traversal, second parameter is a "function" with 
	// return type void and parameter Node*, i.e: 
	//					void process(Node* )
	void inorder(Node<Type>* node, std::function<void(Node<Type>*)> proc);
	void preorder(Node<Type>* node, std::function<void(Node<Type>*)> proc);
	void postorder(Node<Type>* node, std::function<void(Node<Type>*)> proc);

	Node<Type>* min(Node<Type> *node) const;
	Node<Type>* max(Node<Type> *node) const;

	int   height(Node<Type>* node) const;

	bool  search(Node<Type>* node, Type item) const;

	Node<Type>* insert(Node<Type>* node, Type item);
	Node<Type>* remove(Node<Type>* node, Type item);
	
	void  printTree(Node<Type>* node, int space) const;
};




//----------------------------------------------------------
//-------------- Binary Search Tree Function Implementations 
// 

// Constructor
template<typename Type>
BinarySearchTree<Type>::BinarySearchTree() :root(nullptr) {}

// Destructor
template<typename Type>
BinarySearchTree<Type>::~BinarySearchTree() {

	//Use the post order traversal to delete the nodes.
	//lambda function to delete a node n: 
	//				[](Node* n) {delete n; } 
	postorder(root, [](Node<Type>* n) {delete n; });
}
template<typename Type>
void BinarySearchTree<Type>::printInorder() const {

	//Use inorder traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item << std::endl; }"
	const_cast<BinarySearchTree<Type>*>(this)->inorder(root,      [](Node<Type>* n) {std::cout << n->item << " "; });

	std::cout << std::endl;
}
template<typename Type>
void BinarySearchTree<Type>::printPreorder() const {

	//Use pre order traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item << std::endl; }"
	const_cast<BinarySearchTree<Type>*>(this)->preorder(root, [](Node<Type>* n) {std::cout << n->item << " "; });
	std::cout << std::endl;
}
template<typename Type>
void BinarySearchTree<Type>::printPostorder() const {

	//Use post order traversal to print items in a node in the tree.
	//lambda function to print the item in a node:
	//lambda to print->	"[](Node* n) {std::cout << n->item << std::endl; }"
	const_cast<BinarySearchTree<Type>*>(this)->postorder(root, [](Node<Type>* n) {std::cout << n->item << " "; });
	std::cout << std::endl;
}
template<typename Type>
void BinarySearchTree<Type>::insert(Type item) {
	root = insert(root, item);
}
template<typename Type>
void BinarySearchTree<Type>::remove(Type item) {
	root = remove(root, item);
}
template<typename Type>
Type	BinarySearchTree<Type>::min() const {

	assert(root != nullptr);

	Node<Type>* node = min(root);
	return node->item;
}
template<typename Type>
Type	BinarySearchTree<Type>::max() const {

	assert(root != nullptr);

	Node<Type>* node = max(root);
	return node->item;
}
template<typename Type>
int	BinarySearchTree<Type>::height() const {

	return height(root);
}
template<typename Type>
bool BinarySearchTree<Type>::search(Type item) const {
	return search(root, item);
}
template<typename Type>
bool BinarySearchTree<Type>::empty() const {
	return (root == nullptr);
}
template<typename Type>
void BinarySearchTree<Type>::printTree() const {
	printTree(root, 0);
}

//----------------------------------------------------------
//
// Private Recursive Functions: You Implement These.
//

// Inorder Traversal: The second parameter, proc, is a function and we see that its return type is void and it 
// has a Node* as a parameter.  Any function of that form passed into inorder will be
// called as seen below.  
// If we assume that we use the printing lambda defined above you can imagine that proc 
// is defined as:
//		void proc(Node<Type> * n){std::cout << n->item << " "; }
template<typename Type>
void BinarySearchTree<Type>::inorder(Node<Type>* node, std::function<void(Node<Type>*)> proc) {
	if (node == nullptr)
		return;

	inorder(node->left, proc);
	proc(node);
	inorder(node->right, proc);

}

template<typename Type>
void BinarySearchTree<Type>::postorder(Node<Type>* node, std::function<void(Node<Type>*)> proc) {
	if (node == nullptr)
		return;

	postorder(node->left, proc);
	postorder(node->right, proc);
	proc(node);

}
template<typename Type>
void BinarySearchTree<Type>::preorder(Node<Type>* node, std::function<void(Node<Type>*)> proc) {
	if (node == nullptr)
		return;

	proc(node);
	preorder(node->left, proc);
	preorder(node->right, proc);
}

// BinarySearchTree::insert recursively inserts into the BST according 
// to the rules of the BST.  
template<typename Type>
Node<Type>* BinarySearchTree<Type>::insert(Node<Type>* node, Type item) {
	if (node == nullptr)
		return new Node<Type>(item, nullptr, nullptr);
	if (item < node->item)
		node->left = insert(node->left, item);

	if (item > node->item)
		node->right = insert(node->right, item);
	return node;
}

// BinarySearchTree<Type>::search recursively searches the tree for item.
template<typename Type>
bool BinarySearchTree<Type>::search(Node<Type>* node, Type item) const {
	if (node == nullptr)
		return false;
	else if (item == node->item)
		return true;
	else if (item < node->item)
		return search(node->left, item);
	else
		return search(node->right, item);
}

// BinarySearchTree<Type>::height
// Height of a binary tree is the height of the largest subtree + 1
// An empty tree has height 0;
template<typename Type>
int	BinarySearchTree<Type>::height(Node<Type>* node) const {
	if (node == nullptr)
		return 0;
	
	int leftHeight = height(node->left);
	int rightHeight = height(node->right);
	if (leftHeight > rightHeight)
		return leftHeight + 1;
	else
		return rightHeight + 1;
}
// BinarySearchTree<Type>::min recursively obtain the node with the minimum item
template<typename Type>
Node<Type>* BinarySearchTree<Type>::min(Node<Type>* node) const {

	//********* TODO **********
	if (node->left == nullptr)
		return node;
	return min(node->left);
}

// BinarySearchTree<Type>::max recursively obtain the node with the minimum item
template<typename Type>
Node<Type>* BinarySearchTree<Type>::max(Node<Type>* node) const {
	if (node->right == nullptr)
		return node;
	return max(node->right);
}

// BinarySearchTree<Type>::printTree
// Prints the BST in a tree format rotated -90 degrees.  Uses space to 
// signify the space between levels of the tree. Uses the inorder 
// traversal but traverses right first, rather than left. Cannot use
// any of the other travel functions because of this.
//
// parameter space determines the number of spaces needed for each level.
// Example binary shows 5 spaces between levels. 
//
// i.e. traverse right 
//		print appropriate number of spaces 
//		print item 
//		traverse left
template<typename Type>
void BinarySearchTree<Type>::printTree(Node<Type>* node, int space) const {
	if (node == nullptr)
		return;
	printTree(node->right, space + 5);
	for (int i = 0; i < space; i++)
		std::cout << " ";
	std::cout << node->item << std::endl;
	printTree(node->left, space + 5);
}


//BinarySearchTree<Type>::remove
//
// Recursively removes an Item node in the binary tree.  The recursive algorithm will 
// be different than the iterative algorithm.  The iterative algorithm conisted
// of first finding the node using two pointers so that we know how to rearrange
// the children of the deleted node. In recursion, we are passing in the sub trees
// each recursive step, so by definition we already have a handle on each subtrees'
// parents (it is the node that is passed into the previous recursive step).
// After we search the node to remove (if it is in the tree) everything else is the same, we  
// handle the three cases: leaf, one child (which consist of two cases: left vs right),
// and two children.  With iterative algorithm there were subcases regardling if the 
// node was root or not, with recursion we get that for free.  
//
// In dealing with a node with two children, we choose items from one of the appropriate 
// nodes in either subtree.  We then just want to write the subtree node's item into the 
// node to be deleted, this will result having two instances of the subtree value. So we 
// can recurse on that subtree and recursively call remove on that item (not the original) 
// to remove that redundant node.  
// 
template<typename Type>
Node<Type>* BinarySearchTree<Type>::remove(Node<Type>* node, Type item) {

	//********* TODO **********
	if (node == nullptr)
		return node;
	if (item < node->item) {
		node->left = remove(node->left, item);
		return node;
	}
	else if (item > node->item) {
		node->right = remove(node->right, item);
		return node;
	}
	else { //we found the node to be deleted as node->item == item
		if (node->left == nullptr) { //if the node only has right child or no child
			Node<Type>* temp = node->right;
			delete node;
			return temp;
		}
		else if (node->right == nullptr) { //if the node only has left child or no child
			Node<Type>* temp = node->left;
			delete node;
			return temp;
		}
		else { //the node has 2 children
			Node<Type>* minRST = node->right; //find the min item of the right subtree
			while (minRST->left != nullptr) {
				minRST = minRST->left;
			}
			//replace the min item with the node to be deleted
			node->item = minRST->item;
			//recursively delete the node with min item in the right subtree
			node->right = remove(node->right, minRST->item);
			return node;
		}
	}

}































































































































#endif//BINARYSEARCHITEM_H_H_MMXXI