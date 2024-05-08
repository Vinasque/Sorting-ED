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
void selectionSort(Node*);
void optimizedSelectionSort(Node*);

int main() {
    cout << "Teste com a função original:\n" << endl;
    
    int arriNumbers1[] = {42, 7, 0, 3, 666, 1, 111, 10, 13};
    int iArraySize = 9;
    
    Node* head = nullptr;
    for (int i = 0; i < iArraySize; ++i) 
    {
        insertEnd(&head, arriNumbers1[i]);
    }

    cout << "Lista original: ";
    displayList(head);

    auto timeStart = high_resolution_clock::now();
    selectionSort(head);
    auto timeStop = high_resolution_clock::now();

    cout << "Lista ordenada: ";
    displayList(head);

    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;

    cout << "\nTeste com a função otimizada:\n" << endl;

    Node* headOptimized = nullptr;
    for (int i = 0; i < iArraySize; ++i) 
    {
        insertEnd(&headOptimized, arriNumbers1[i]);
    }

    cout << "Lista original: ";
    displayList(headOptimized);

    auto timeStartOptimized = high_resolution_clock::now();
    optimizedSelectionSort(headOptimized);
    auto timeStopOptimized = high_resolution_clock::now();

    cout << "Lista ordenada: ";
    displayList(headOptimized);

    auto timeDurationOptimized = duration_cast<nanoseconds>(timeStopOptimized - timeStartOptimized);
    cout << "Tempo utilizado: " << timeDurationOptimized.count() << " nanosegundos." << endl;

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

