#include <iostream>
#include <chrono>
#include <cstdlib>
#include "functions.h"

using namespace std;

namespace functionsBubble {
    template <typename T>
    Node<T>* createNode(T iPayload) 
    {
        Node<T>* temp = (Node<T>*)malloc(sizeof(Node<T>));
        temp->iPayload = iPayload;
        temp->ptrNext = nullptr;
        temp->ptrPrev = nullptr;
        return temp;
    }

    template <typename T>
    void insertEnd(Node<T>** head, T iPayload) 
    {
        Node<T>* newNode = createNode(iPayload);

        if (*head == nullptr) 
        {
            *head = newNode;
        } 
        else 
        {
            Node<T>* temp = *head;
            
            while (temp->ptrNext != nullptr) 
            {
                temp = temp->ptrNext;
            }
            
            temp->ptrNext = newNode;
            newNode->ptrPrev = temp;
        }
    }

    template <typename T>
    void displayList(Node<T>* node) 
    {
        if (node == nullptr) 
        {
            cout << "Lista vazia." << endl;
            return;
        }

        while (node != nullptr) 
        {
            cout << node->iPayload << " ";
            node = node->ptrNext;
        }
        
        cout << endl;
    }

    template <typename T>
    void deleteList(Node<T>** head) {
        if (*head == nullptr) {
            cout << "Lista já está vazia." << endl;
            return;
        }

        Node<T>* current = *head;
        Node<T>* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->ptrNext;
            free(current);
            current = nextNode;
        }

        *head = nullptr;
    }

    template <typename T>
    void swapNodes(Node<T>* node1, Node<T>* node2) 
    {
        T temp = node1->iPayload;
        node1->iPayload = node2->iPayload;
        node2->iPayload = temp;
    }

    template <typename T>
    void bubbleSort(Node<T>* head)
    {
        if (head == nullptr || head->ptrNext == nullptr) return;

        int iLength = 0;
        Node<T>* current = head;
        
        // Determina o comprimento da lista
        while (current != nullptr) 
        {
            iLength++;
            current = current->ptrNext;
        }

        for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++) 
        {
            current = head;

            for (int iInnerLoop = 0; iInnerLoop < iLength - 1; iInnerLoop++) 
            {
                if (current->iPayload > current->ptrNext->iPayload) 
                {
                    swapNodes(current, current->ptrNext);
                }
                
                current = current->ptrNext;
            }
        }
    }

    template <typename T>
    void optimizedBubbleSort(Node<T>* head)
    {
        if (head == nullptr || head->ptrNext == nullptr) return;

        int iLength = 0;
        Node<T>* current = head;
        bool bSwapped = true;

        // Determina o comprimento da lista
        while (current != nullptr) 
        {
            iLength++;
            current = current->ptrNext;
        }

        for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++) 
        {
            bSwapped = false;
            current = head;

            for (int iInnerLoop = 0; iInnerLoop < iLength - 1 - iOuterLoop; iInnerLoop++) 
            {
                if (current->iPayload > current->ptrNext->iPayload) 
                {
                    bSwapped = true;
                    swapNodes(current, current->ptrNext);
                }
                
                current = current->ptrNext;
            }
            if (!bSwapped)
            {
                return;
            }
        }
    }

    template Node<int>* createNode<int>(int iPayload);
    template void insertEnd<int>(Node<int>** head, int iPayload);
    template void displayList<int>(Node<int>* head);
    template void swapNodes<int>(Node<int>* node1, Node<int>* node2);
    template void deleteList<int>(Node<int>** head);
    template void bubbleSort<int>(Node<int>* node);
    template void optimizedBubbleSort<int>(Node<int>* node);
}