#pragma once

template<typename T>
class BSTree {
private:
	struct Node {
		T mData;
		Node* left = nullptr;
		Node* right = nullptr;

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
	BSTree() = default;
	BSTree(const BSTree& other);
	BSTree(BSTree&& other);
	BSTree& operator=(const BSTree& other);
	BSTree& operator=(BSTree&& other);
	~BSTree();

	void print();

	bool insert(const T& element);
	bool insert(T&& element);
	bool remove(const T& element);

	void clear();
	bool isEmpty();
	bool find(const T& element);

private:
	void deleteNodes(Node* root);
	Node* copyTree(Node* root);
	void print(Node* root);


	Node* insert(Node* root, const T& element);
	Node* insert(Node* root, T&& element);
	Node* remove(Node* root, const T& element);

	bool rightNodeOnly(Node* root);
	bool leftNodeOnly(Node* root);
	
	Node* findLargestInLeft(Node* node); // finds largest node in left subtree
	bool find(Node* root, const T& element);

};

template<typename T>
BSTree<T>::BSTree(const BSTree& other)
{
	this->root = copyTree(other.root);
}

template<typename T>
BSTree<T>::BSTree(BSTree&& other)
{
	this->root = other.root;
	other.root = nullptr;
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& other)
{
	if (this == &other)
		return *this;

	deleteNodes(this->root);
	this->root = copyTree(other.root);
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(BSTree&& other)
{
	if (this == &other)
		return *this;

	deleteNodes(this->root);
	this->root = other.root;
	other.root = nullptr;
}

template<typename T>
BSTree<T>::~BSTree()
{
	deleteNodes(this->root);
	root = nullptr;
}

template<typename T>
void BSTree<T>::print()
{
	print(root);
}


template<typename T>
bool BSTree<T>::insert(const T& element)
{
	if (root && root->mData == element)
		return false;

	root = insert(root, element);
	return true;
}

template<typename T>
bool BSTree<T>::insert(T&& element)
{
	if (find(root, element))
		return false;

	root = insert(root, std::move(element));
	return true;
}

template<typename T>
bool BSTree<T>::remove(const T& element)
{
	if (!find(root, element))
		return false;

	root = remove(root, element);
	return true;
}

template<typename T>
bool BSTree<T>::isEmpty()
{
	return !root;
}

template<typename T>
void BSTree<T>::clear()
{
	deleteNodes(root);
	root = nullptr;
}

template<typename T>
bool BSTree<T>::find(const T& element)
{
	if (find(root, element))
		return true;

	return false;
}

template<typename T>
void BSTree<T>::deleteNodes(Node* root)
{
	if (!root)
		return;

	deleteNodes(root->left);
	deleteNodes(root->right);
	delete root;
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::copyTree(Node* root)
{
	if (!root)
		return nullptr;

	Node* newNode = new Node(root->mData);
	newNode->left = copyTree(root->left);
	newNode->right = copyTree(root->right);

	return newNode;
}

template<typename T>
void BSTree<T>::print(Node* root)
{
	if (!root)
		return;

	print(root->left);
	std::cout << root->mData << ' ';
	print(root->right);
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::insert(Node* root, const T& element)
{
	if (!root)
		return new Node(element);

	if (element < root->mData)
		root->left = insert(root->left, element);
	else if (element > root->mData)
		root->right = insert(root->right, element);

	return root;
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::insert(Node* root, T&& element)
{
	if (!root)
		return new Node(std::move(element));

	if (element < root->mData)
		root->left = insert(root->left, element);
	else if (element > root->mData)
		root->right = insert(root->right, element);

	return root;
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::remove(Node* root, const T& element)
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

	return root;
}

template<typename T>
bool BSTree<T>::rightNodeOnly(Node* root)
{
	return !root->left;
}

template<typename T>
bool BSTree<T>::leftNodeOnly(Node* root)
{
	return !root->right;
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::findLargestInLeft(Node* node)
{
	Node* largestNode = node;

	while (largestNode->right)
		largestNode = largestNode->right;

	return largestNode;
}

template<typename T>
bool BSTree<T>::find(Node* root, const T& element)
{
	if (!root)
		return false;

	if (element < root->mData)
	{
		if (find(root->left, element))
			return true;

		return false;
	}
	else if (element > root->mData)
	{
		if (find(root->right, element))
			return true;

		return false;
	}
	else if (element == root->mData)
	{
		return true;
	}

	return false;
}

// ---------------------------------------------------------------------
