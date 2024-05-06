#include <iostream>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

// Estrutura do Nó
typedef struct Node 
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

// Funções para a Lista Duplamente Encadeada
Node* createNode(int);
void insertEnd(Node**, int);
void displayList(Node*);
void swapNodes(Node*, Node*);
void bubbleSort(Node*);

int main() {
    Node* head = nullptr;
    
    // Insere elementos na lista
    insertEnd(&head, 42);
    insertEnd(&head, 7);
    insertEnd(&head, 0);
    insertEnd(&head, 3);
    insertEnd(&head, 666);
    insertEnd(&head, 1);
    insertEnd(&head, 111);
    insertEnd(&head, 10);
    insertEnd(&head, 13);

    // Exibe a lista antes da ordenação
    cout << "Lista original: ";
    displayList(head);

    auto timeStart = high_resolution_clock::now();
    bubbleSort(head);
    auto timeStop = high_resolution_clock::now();

    // Exibe a lista ordenada
    cout << "Lista ordenada: ";
    displayList(head);
    
    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;

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
    int swapped;
    Node* ptr;
    Node* lastPtr = nullptr;

    if (head == nullptr) return;

    do 
    {
        swapped = 0;
        ptr = head;

        while (ptr->ptrNext != lastPtr) 
        {
            if (ptr->iPayload > ptr->ptrNext->iPayload) 
            {
                swapNodes(ptr, ptr->ptrNext);
                swapped = 1;
            }
            
            ptr = ptr->ptrNext;
        }
        
        lastPtr = ptr;
        
    } while (swapped);
}