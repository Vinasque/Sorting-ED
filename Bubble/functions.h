#pragma once

typedef struct Node 
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertEnd(Node**, int);
void displayList(Node*);
void swapNodes(Node*, Node*);
void deleteList(Node** head);
void bubbleSort(Node*);
void optimizedBubbleSort(Node*);