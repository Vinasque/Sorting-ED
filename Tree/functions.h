#pragma once

template <typename T>
struct Node
{
    T iPayload;
    Node* ptrLeft;
    Node* ptrRight;
};

template <typename T>
struct ListNode
{
    Node<T>* ptrTreeEquivalent;
    ListNode<T>* ptrNext;
    T iPayload;
};

namespace functionsTree {
    template <typename T>
    Node<T>* createNode(T iData);
    template <typename T>
    ListNode<T>* createListNode(Node<T>* node);
    template <typename T>
    void insertEnd(ListNode<T>** head, Node<T>* node); 
    template <typename T>
    Node<T>* insertNode(Node<T>* root, T iData);
    template <typename T>
    Node<T>* searchNode(Node<T>* root, T iData);
    template <typename T>
    Node<T>* searchNodeBFS(Node<T>* root, T iData);
    template <typename T>
    Node<T>* deleteNode(Node<T>* root, T iData);
    template <typename T>
    void deleteListNode(ListNode<T>** head);;
    template <typename T>
    Node<T>* lesserLeaf(Node<T>* root);
    // template <typename T>
    // void bfsTraversal(Node<T>* root, T iData);
    template <typename T>
    int treeHeight(Node<T>* root);
}