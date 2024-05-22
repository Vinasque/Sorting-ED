#pragma once

template <typename T>
struct Node 
{
    T iPayload;
    Node* ptrNext;
    Node* ptrPrev;
};

namespace functionsBubble {
    template <typename T>
    Node<T>* createNode(T);
    template <typename T>
    void insertEnd(Node<T>**, T);
    template <typename T>
    void displayList(Node<T>*);
    template <typename T>
    void swapNodes(Node<T>*, Node<T>*);
    template <typename T>
    void deleteList(Node<T>** head);
    template <typename T>
    void bubbleSort(Node<T>*);
    template <typename T>
    void optimizedBubbleSort(Node<T>*);
}