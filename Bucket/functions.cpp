#include <iostream>
#include "functions.h"

using namespace std;

namespace functionsBucket {
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

        cout << "Payload: ";
        while (node != nullptr) 
        {
            cout << node->iPayload << " ";
            node = node->ptrNext;
        }
        
        cout << endl;
    }

    template <typename T>
    void swapNodes(Node<T>* node1, Node<T>* node2) 
    {
        T temp = node1->iPayload;
        node1->iPayload = node2->iPayload;
        node2->iPayload = temp;
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
    void insertNodeBefore(Node<T>* node, Node<T>* nodeToInsert) 
    {
        Node<T>* nodePrev = node->ptrPrev;
        Node<T>* nodeNext = node;
        
        if (nodeToInsert->ptrNext == nullptr)
        {
            nodeToInsert->ptrPrev->ptrNext = nullptr;
        }
        else 
        {
            nodeToInsert->ptrNext->ptrPrev = nodeToInsert->ptrPrev;
            nodeToInsert->ptrPrev->ptrNext = nodeToInsert->ptrNext;
        }
        
        if (nodePrev == nullptr)
        {
            nodeNext->ptrPrev = nodeToInsert;
            nodeToInsert->ptrNext = nodeNext;
            nodeToInsert->ptrPrev = nullptr;
        }
        else 
        {
            nodeNext->ptrPrev = nodeToInsert;
            nodePrev->ptrNext = nodeToInsert;
        
            nodeToInsert->ptrPrev = nodePrev;
            nodeToInsert->ptrNext = nodeNext;
        }
    }

    template <typename T>
    void insertionSort(Node<T>** head)
    {
        if (*head == nullptr || (*head)->ptrNext == nullptr) return;

        int iLength = 0;
        Node<T>* outer = *head;
        
        // Determina o comprimento da lista
        while (outer != nullptr) 
        {
            iLength++;
            outer = outer->ptrNext;
        }

        outer = *head;
        Node<T>* inner = *head;

        for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++) 
        {
            if (outer->iPayload > outer->ptrNext->iPayload) 
            {
                while (inner->ptrPrev != nullptr && inner->ptrPrev->iPayload > outer->ptrNext->iPayload) 
                {
                    inner = inner->ptrPrev;
                }

                if (inner->ptrPrev == nullptr)
                {
                    *head = outer->ptrNext;
                    insertNodeBefore(outer, outer->ptrNext);
                }
                else
                {
                    insertNodeBefore(inner, outer->ptrNext);
                }
                
                inner = outer;
            }
            else
            {
                outer = outer->ptrNext;
                inner = outer;
            }
        }
    }

    template <typename T>
    void bucketSort(Node<T>** head)
    {
        if (*head == nullptr || (*head)->ptrNext == nullptr) return;

        int iLength = 0;
        Node<T>* outer = *head;
        T iMaxValue = outer->iPayload;

        // Determina o comprimento da lista e o maior valor
        while (outer != nullptr) 
        {
            if (iMaxValue < outer->iPayload) iMaxValue = outer->iPayload;
            iLength++;
            outer = outer->ptrNext;
        }

        int iBucketSize = (iMaxValue / 10) + 1; // Para evitar bucket 0 em alguns casos

        outer = *head;

        Node<T>* nodeArray[10] = {nullptr};

        // Distribui os elementos nos buckets
        while (outer != nullptr) 
        {
            int bucketIndex = outer->iPayload / iBucketSize;
            if (bucketIndex > 9) bucketIndex = 9; // O índice do bucket não pode ser maior que 9
            insertEnd(&nodeArray[bucketIndex], outer->iPayload);
            outer = outer->ptrNext;
        }

        // Ordena cada bucket e reinsere na lista original
        *head = nullptr; // Reseta a lista original

        for (int i = 0; i < 10; i++)
        {
            insertionSort(&nodeArray[i]);

            Node<T>* current = nodeArray[i];
            while (current != nullptr)
            {
                insertEnd(head, current->iPayload);
                current = current->ptrNext;
            }
        }

        // Limpa os buckets
        for (int i = 0; i < 10; i++)
        {
            deleteList(&nodeArray[i]);
        }
    }

    template Node<int>* createNode<int>(int iPayload);
    template void insertEnd<int>(Node<int>** head, int iPayload);
    template void displayList<int>(Node<int>* head);
    template void swapNodes<int>(Node<int>* node1, Node<int>* node2);
    template void deleteList<int>(Node<int>** head);
    template void insertNodeBefore<int>(Node<int>* node, Node<int>* nodeToInsert);
    template void insertionSort<int>(Node<int>** head);
    template void bucketSort<int>(Node<int>** head);
}