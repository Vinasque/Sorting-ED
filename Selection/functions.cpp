#include <iostream>
#include "functions.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

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

void selectionSort(Node* head) 
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

    current = head;

    for (int iOuterLoop = 0; iOuterLoop < iLength; iOuterLoop++) 
    {        
        Node* temp = current->ptrNext;

        for (int iInnerLoop = iOuterLoop + 1; iInnerLoop < iLength; iInnerLoop++) 
        {
            if (current->iPayload > temp->iPayload) 
            {
                swapNodes(current, temp);
            }
            
            temp = temp->ptrNext;
        }

        current = current->ptrNext;
    }
}

void optimizedSelectionSort(Node* head) 
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

    current = head;

    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++) 
    {
        Node* temp = current->ptrNext;
        Node* smallest = current->ptrNext;

        for (int iInnerLoop = iOuterLoop + 1; iInnerLoop < iLength; iInnerLoop++) 
        {
            if (smallest->iPayload > temp->iPayload) 
            {
                smallest = temp;
            }

            temp = temp->ptrNext;
        }

        if (smallest->iPayload < current->iPayload)
        {
            swapNodes(current, smallest);
        }

        current = current->ptrNext;
    }
}