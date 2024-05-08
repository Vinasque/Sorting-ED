#include <iostream>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

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
void bubbleSort(Node*);
void optimizedBubbleSort(Node*);

int main() {
    Node* head = nullptr;
    Node* headOptimized = nullptr;
    
    insertEnd(&head, 42);
    insertEnd(&head, 7);
    insertEnd(&head, 0);
    insertEnd(&head, 3);
    insertEnd(&head, 666);
    insertEnd(&head, 1);
    insertEnd(&head, 111);
    insertEnd(&head, 10);
    insertEnd(&head, 13);
    
    insertEnd(&headOptimized, 42);
    insertEnd(&headOptimized, 7);
    insertEnd(&headOptimized, 0);
    insertEnd(&headOptimized, 3);
    insertEnd(&headOptimized, 666);
    insertEnd(&headOptimized, 1);
    insertEnd(&headOptimized, 111);
    insertEnd(&headOptimized, 10);
    insertEnd(&headOptimized, 13);
    
    cout << "Teste com a função original:\n" << endl;
    
    cout << "Lista original: ";
    displayList(head);

    auto timeStart = high_resolution_clock::now();
    bubbleSort(head);
    auto timeStop = high_resolution_clock::now();

    cout << "Lista ordenada: ";
    displayList(head);
    
    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;
    
    cout << "\nTeste com a função otimizada:\n" << endl;
    
    cout << "Lista original: ";
    displayList(headOptimized);

    auto timeStartOptimized = high_resolution_clock::now();
    bubbleSort(headOptimized);
    auto timeStopOptimized = high_resolution_clock::now();

    cout << "Lista ordenada: ";
    displayList(headOptimized);
    
    auto timeDurationOptimized = duration_cast<nanoseconds>(timeStopOptimized - timeStartOptimized);
    cout << "Tempo utilizado: " << timeDurationOptimized.count() << " nanosegundos." << endl;

     cout << "\nUsando listas com 1000 termos:\n" << endl;

    Node* headBig = nullptr;
    Node* headBigOptimized = nullptr;

    for (int i = 0; i < 1000; ++i) 
    {
        int iRandNum = rand() % 101; //Entre 0 e 100
        insertEnd(&headBig, iRandNum);
        insertEnd(&headBigOptimized, iRandNum);
    }

    auto timeStartBigOptimized = high_resolution_clock::now();
    optimizedBubbleSort(headBigOptimized);
    auto timeStopBigOptimized = high_resolution_clock::now();

    auto timeStartBig = high_resolution_clock::now();
    bubbleSort(headBig);
    auto timeStopBig = high_resolution_clock::now();

    auto timeDurationBig = duration_cast<nanoseconds>(timeStopBig - timeStartBig);
    cout << "Tempo utilizado com a função original: " << timeDurationBig.count() << " nanosegundos." << endl;

    auto timeDurationBigOptimized = duration_cast<nanoseconds>(timeStopBigOptimized - timeStartBigOptimized);
    cout << "Tempo utilizado com a função otimizada: " << timeDurationBigOptimized.count() << " nanosegundos." << endl;

    return 0;
}

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