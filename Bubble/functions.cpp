#include <iostream>
#include <chrono>
#include <cstdlib>
#include "functions.h"

using namespace std;

Node* createNode(int iPayload) 
{
    Node* temp = (Node*)malloc(sizeof(Node));
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

    while (node != nullptr) 
    {
        cout << node->iPayload << " ";
        node = node->ptrNext;
    }
    
    cout << endl;
}

void deleteList(Node** head) {
    if (*head == nullptr) {
        cout << "Lista já está vazia." << endl;
        return;
    }

    Node* current = *head;
    Node* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->ptrNext;
        free(current);
        current = nextNode;
    }

    *head = nullptr;
}

void swapNodes(Node* node1, Node* node2) 
{
    int temp = node1->iPayload;
    node1->iPayload = node2->iPayload;
    node2->iPayload = temp;
}

void bubbleSort(Node* head)
{
    if (head == nullptr || head->ptrNext == nullptr) return;

    int iLength = 0;
    Node* current = head;
    
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

void optimizedBubbleSort(Node* head)
{
    if (head == nullptr || head->ptrNext == nullptr) return;

    int iLength = 0;
    Node* current = head;
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