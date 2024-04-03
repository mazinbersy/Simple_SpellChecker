#include "BST.h"

// Constructor
template <typename T>
BST<T>::BST() : root(nullptr) {}

// Destructor
template <typename T>
BST<T>::~BST() {
    destroyTree(root); // Call the helper function to delete all nodes
}

// Insert function
template <typename T>
void BST<T>::insert(const T& value) {
    root = insert(root, value);
}

// Search function
template <typename T>
bool BST<T>::search(const T& value) const {
    return search(root, value);
}

// Inorder Traversal
template <typename T>
std::vector<T> BST<T>::inorderTraversal() const {
    std::vector<T> result;
    inorderTraversal(root, result);
    return result;
}

// Delete Node
template <typename T>
void BST<T>::deleteNode(const T& value) {
    root = remove(root, value);
}

// Private insert helper function
template <typename T>
typename BST<T>::Node* BST<T>::insert(Node* node, const T& value) {
    if (node == nullptr) {
        return new Node(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    }
    else if (value > node->data) {
        node->right = insert(node->right, value);
    }

    return node;
}

// Private search helper function
template <typename T>
bool BST<T>::search(Node* node, const T& value) const {
    if (node == nullptr) {
        return false;
    }

    if (value == node->data) {
        return true;
    }
    else if (value < node->data) {
        return search(node->left, value);
    }
    else {
        return search(node->right, value);
    }
}

// Private inorder traversal helper function
template <typename T>
void BST<T>::inorderTraversal(Node* node, std::vector<T>& result) const {
    if (node != nullptr) {
        inorderTraversal(node->left, result);
        result.push_back(node->data);
        inorderTraversal(node->right, result);
    }
}

// Helper function to destroy the tree
template <typename T>
void BST<T>::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Private remove helper function
template <typename T>
typename BST<T>::Node* BST<T>::remove(Node* node, const T& value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = remove(node->left, value);
    }
    else if (value > node->data) {
        node->right = remove(node->right, value);
    }
    else {
        // Node to be deleted found

        // Case 1: Node has no children or only one child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case 2: Node has two children
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }

    return node;
}

// Helper function to find the minimum value node in a subtree
template <typename T>
typename BST<T>::Node* BST<T>::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Check if the tree is empty
template <typename T>
bool BST<T>::empty() const {
    return root == nullptr;
}

// Preorder Traversal
template <typename T>
void BST<T>::preorderTraversal(Node* node, std::vector<T>& result) const {
    if (node != nullptr) {
        result.push_back(node->data); // Visit the current node
        preorderTraversal(node->left, result); // Traverse left subtree
        preorderTraversal(node->right, result); // Traverse right subtree
    }
}

// Public function to perform preorder traversal
template <typename T>
std::vector<T> BST<T>::preorder() const {
    std::vector<T> result;
    preorderTraversal(root, result);
    return result;
}

// Level-order Traversal
template <typename T>
void BST<T>::levelorderTraversal(Node* node, std::vector<T>& result) const {
    if (node == nullptr) {
        return;
    }

    std::queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        result.push_back(current->data); // Visit the current node

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

// Public function to perform level-order traversal
template <typename T>
std::vector<T> BST<T>::levelorder() const {
    std::vector<T> result;
    levelorderTraversal(root, result);
    return result;
}

// Explicit instantiation of template class for string
//Prevents Linker Errors
template class BST<std::string>;
