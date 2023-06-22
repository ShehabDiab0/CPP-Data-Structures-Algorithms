#pragma once

template<typename T>
class AVLTree {
private:
	struct Node {
		T mData;
		Node* left = nullptr;
		Node* right = nullptr;
		int balanceFactor = 0;
		int height = 0;

		Node() = default;
		Node(const T& val)
			: mData(val)
		{}
		Node(T&& val)
			: mData(std::move(val))
		{}
	};

	Node* root = nullptr;

public:
	AVLTree() = default;
	AVLTree(const AVLTree& other);
	AVLTree(AVLTree&& other);
	AVLTree& operator=(const AVLTree& other);
	AVLTree& operator=(AVLTree&& other);
	~AVLTree();
	
	void print();

	bool insert(const T& element);
	bool insert(T&& element);
	bool remove(const T& element);

	bool find(const T& element);
	bool isEmpty();
	void clear();

private:
	Node* copyTree(Node* root);
	void deleteNodes(Node* root);
	void print(Node* root);


	Node* rightRotate(Node* oldRoot);
	Node* leftRotate(Node* oldRoot);


	Node* insert(Node* root, const T& element);
	Node* insert(Node* root, T&& element);
	Node* remove(Node* root, const T& element);

	void updateHeight(Node* node);
	Node* balance(Node* root);
	bool rightNodeOnly(Node* root);
	bool leftNodeOnly(Node* root);
	Node* findLargestInLeft(Node* node);

	bool find(Node* root, const T& element);
};


template<typename T>
AVLTree<T>::AVLTree(const AVLTree& other)
{
	this->root = copyTree(other.root);
}

template<typename T>
AVLTree<T>::AVLTree(AVLTree&& other)
{
	this->root = other.root;
	other.root = nullptr;
}

template<typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree& other)
{
	if (this == &other)
		return *this;

	deleteNodes(this->root);
	root = copyTree(other.root);
}

template<typename T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree&& other)
{
	if (this == &other)
		return *this;

	deleteNodes(this->root);
	root = other.root;
	other.root = nullptr;
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	deleteNodes(root);
}


template<typename T>
void AVLTree<T>::print()
{
	print(root);
}

template<typename T>
bool AVLTree<T>::insert(const T& element)
{
	if (find(root, element))
		return false;

	root = insert(root, element);
	return true;
}

template<typename T>
bool AVLTree<T>::insert(T&& element)
{
	if (find(root, element))
		return false;

	root = insert(root, std::move(element));
	return true;
}

template<typename T>
bool AVLTree<T>::remove(const T& element)
{
	if (!find(root, element))
		return false;

	root = remove(root, element);
	return true;
}

template<typename T>
bool AVLTree<T>::find(const T& element)
{
	if (find(root, element))
		return true;

	return false;
}

template<typename T>
inline bool AVLTree<T>::isEmpty()
{
	return !root;
}

template<typename T>
void AVLTree<T>::clear()
{
	deleteNodes(root);
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::copyTree(Node* root)
{
	if (!root)
		return nullptr;

	Node* newNode = new Node(root->mData);
	newNode->left = copyTree(root->left);
	newNode->right = copyTree(root->right);

	return newNode;
}

template<typename T>
void AVLTree<T>::deleteNodes(Node* root)
{
	if (!root)
		return;

	deleteNodes(root->left);
	deleteNodes(root->right);
	delete root;
}


template<typename T>
void AVLTree<T>::print(Node* root)
{
	if (!root)
		return;

	print(root->left);
	std::cout << root->mData << ' ';
	print(root->right);
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::rightRotate(Node* oldRoot)
{
	Node* newRoot = oldRoot->left;
	oldRoot->left = newRoot->right;
	newRoot->right = oldRoot;

	updateHeight(oldRoot);
	updateHeight(newRoot);

	return newRoot;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::leftRotate(Node* oldRoot)
{
	Node* newRoot = oldRoot->right;
	oldRoot->right = newRoot->left;
	newRoot->left = oldRoot;

	updateHeight(oldRoot);
	updateHeight(newRoot);

	return newRoot;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::insert(Node* root, const T& element)
{
	if (!root)
		return new Node(element);

	if (element < root->mData)
		root->left = insert(root->left, element);
	else if (element > root->mData)
		root->right = insert(root->right, element);

	updateHeight(root);
	return balance(root);
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::insert(Node* root, T&& element)
{
	if (!root)
		return new Node(std::move(element));

	if (element < root->mData)
		root->left = insert(root->left, element);
	else if (element > root->mData)
		root->right = insert(root->right, element);

	updateHeight(root);
	return balance(root);
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::remove(Node* root, const T& element)
{
	if (!root)
		return nullptr;

	if (element < root->mData)
	{
		root->left = remove(root->left, element);
	}
	else if (element > root->mData)
	{
		root->right = remove(root->right, element);
	}
	else
	{
		if (leftNodeOnly(root)) // works with leaf nodes
		{
			Node* newRoot = root->left;
			root->left = nullptr;
			delete root;

			return newRoot;
		}

		if (rightNodeOnly(root))
		{
			Node* newRoot = root->right;
			root->right = nullptr;
			delete root;

			return newRoot;
		}

		// has both left and right subtrees
		Node* newRoot = findLargestInLeft(root->left);

		root->mData = newRoot->mData;
		root->left = remove(root->left, newRoot->mData);
	}

	updateHeight(root);
	return balance(root);
}

template<typename T>
void AVLTree<T>::updateHeight(Node* node)
{
	int leftHeight = (node->left) ? (node->left->height + 1) : 0;
	int rightHeight = (node->right) ? (node->right->height + 1) : 0;

	node->height = std::max(leftHeight, rightHeight);
	node->balanceFactor = rightHeight - leftHeight;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::balance(Node* root)
{
	if (root->balanceFactor == 2)
	{
		if (root->right->balanceFactor >= 0)
			return leftRotate(root);

		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	if (root->balanceFactor == -2)
	{
		if (root->left->balanceFactor <= 0)
			return rightRotate(root);

		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	return root;
}

template<typename T>
bool AVLTree<T>::rightNodeOnly(Node* root)
{
	return !root->left;
}

template<typename T>
bool AVLTree<T>::leftNodeOnly(Node* root)
{
	return !root->right;
}

template<typename T>
bool AVLTree<T>::find(Node* root, const T& element)
{
	if (!root)
		return false;

	if (element < root->mData)
	{
		if (find(root->left, std::move(element)))
			return true;

		return false;
	}
	else if (element > root->mData)
	{
		if (find(root->right, std::move(element)))
			return true;

		return false;
	}
	else if (element == root->mData)
	{
		return true;
	}

	return false;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::findLargestInLeft(Node* node)
{
	Node* largestNode = node;

	while (largestNode->right)
		largestNode = largestNode->right;

	return largestNode;
}
