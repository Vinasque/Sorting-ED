#include <iostream>
#include "functions.h"

Node* createNode(int iPayload) 
{
    Node* temp = new Node;
    temp->iPayload = iPayload;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    return temp;
}

void insertEnd(Node** head, int iPayload) 
{
    Node* newNode = createNode(iPayload);

    if (*head == nullptr) 
    {
        *head = newNode;
    } 
    else 
    {
        Node* temp = *head;
        
        while (temp->ptrNext != nullptr) 
        {
            temp = temp->ptrNext;
        }
        
        temp->ptrNext = newNode;
        newNode->ptrPrev = temp;
    }
}

void displayList(Node* node) 
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

void swapNodes(Node* node1, Node* node2) 
{
    int temp = node1->iPayload;
    node1->iPayload = node2->iPayload;
    node2->iPayload = temp;
}

void insertNodeBefore(Node* node, Node* nodeToInsert) 
{
    Node* nodePrev = node->ptrPrev;
    Node* nodeNext = node;
    
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

void insertionSort(Node** head)
{
    if (*head == nullptr || (*head)->ptrNext == nullptr) return;

    int iLength = 0;
    Node* outer = *head;
    
    // Determina o comprimento da lista
    while (outer != nullptr) 
    {
        iLength++;
        outer = outer->ptrNext;
    }

    outer = *head;
    Node* inner = *head;

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