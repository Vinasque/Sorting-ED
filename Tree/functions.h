#pragma once

template <typename T>
struct Node
{
    T iPayload;
    Node* ptrLeft;
    Node* ptrRight;
};

namespace functionsTree {
    template <typename T>
    Node<T>* createNode(T value);
    template <typename T>
    Node<T>* insertNode(Node<T>* root, T value);
    template <typename T>
    void bfsTraversal(Node<T>* root);
    template <typename T>
    int treeHeight(Node<T>* root);
}