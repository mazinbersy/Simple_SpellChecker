#ifndef BST_H
#define BST_H
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const T& value);
    bool search(Node* node, const T& value) const;
    void inorderTraversal(Node* node, std::vector<T>& result) const;
    void destroyTree(Node* node);
    Node* findMin(Node* node);
    Node* remove(Node* node, const T& value);
    void preorderTraversal(Node* node, std::vector<T>& result) const;
    void levelorderTraversal(Node* node, std::vector<T>& result) const;

public:
    BST();
    ~BST();
    void insert(const T& value);
    bool search(const T& value) const;
    void deleteNode(const T& value);
    bool empty() const;
    vector<T> inorderTraversal() const;
    vector<T> preorder() const;
    vector<T> levelorder() const;

};
#endif