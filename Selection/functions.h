#pragma once

template <typename T>
struct Node 
{
    T iPayload;
    Node* ptrNext;
    Node* ptrPrev;
};

namespace functionsSelection {
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
    void selectionSort(Node<T>*);
    template <typename T>
    void optimizedSelectionSort(Node<T>*);
}