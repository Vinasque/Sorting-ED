#include <iostream>
using namespace std;

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
void insertNode(Node*, Node*);
void insertionSort(Node**);
void bucketSort(Node**);
void explicaBucket();

int main()
{
    explicaBucket();

    return 0;
}

void explicaBucket()
{
    int arriNumbers[] = {1, 19, 13, 32, 23, 42, 96, 75, 89, 81, 51, 69, 63, 87, 84};
    int iArraySize = sizeof(arriNumbers) / sizeof(arriNumbers[0]);
    
    Node* head = nullptr;
    for (int i = 0; i < iArraySize; ++i) 
    {
        insertEnd(&head, arriNumbers[i]);
    }

    cout << "Lista original: ";
    displayList(head);
    
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

    // Passo 1: Determine o numero de buckets e o maior valor
    cout << "Passo 1: Determinando o numero de buckets e o maior valor...\n" << endl;
    int iLength = 0;
    Node* outer = head;
    int iMaxValue = outer->iPayload;
    while (outer != nullptr) {
        if (iMaxValue < outer->iPayload) iMaxValue = outer->iPayload;
        iLength++;
        outer = outer->ptrNext;
    }
    cout << "Comprimento da lista: " << iLength << "\n";
    cout << "Maior valor na lista: " << iMaxValue << "\n";
    
    cout << "------------------------------------------------------------" << endl;

    // Passo 2: Criar os buckets
    cout << "Passo 2: Criando os buckets... \n" << endl;
    cout << "O tamanho dos buckets e dado por: (MaiorValor / 10) + 1\n";
    int iBucketSize = (iMaxValue / 10) + 1;
    Node* nodeArray[10] = {nullptr};
    
    cout << "------------------------------------------------------------" << endl;

    // Passo 3: Distribuir os elementos nos buckets
    cout << "Passo 3: Distribuindo os elementos nos buckets...\n" << endl;
    outer = head;
    while (outer != nullptr) {
        int bucketIndex = outer->iPayload / iBucketSize;
        if (bucketIndex > 9) bucketIndex = 9;
        insertEnd(&nodeArray[bucketIndex], outer->iPayload);
        cout << "Elemento " << outer->iPayload << " distribuido para o bucket " << bucketIndex << ".\n";
        outer = outer->ptrNext;
    }
    
    cout << "------------------------------------------------------------" << endl;

    // Passo 4: Ordenar individualmente cada bucket
    cout << "Passo 4: Ordenando individualmente cada bucket...\n";
    cout << "OBS: optamos por usar o metodo Insertion.\n" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "Ordenando bucket " << i << "...\n";
        insertionSort(&nodeArray[i]);
        cout << "Bucket " << i << " apos ordenacao: ";
        displayList(nodeArray[i]);
    }
    
    cout << "------------------------------------------------------------" << endl;

    // Passo 5: Concatenar todos os buckets ordenados
    cout << "Passo 5: Concatenando todos os buckets ordenados...\n" << endl;
    head = nullptr;
    for (int i = 0; i < 10; i++) {
        Node* current = nodeArray[i];
        while (current != nullptr) {
            insertEnd(&head, current->iPayload);
            current = current->ptrNext;
        }
    }
    cout << "Lista apos concatenacao: ";
    displayList(head);
    
    cout << "------------------------------------------------------------" << endl;

    // Limpar os buckets
    cout << "Passo 6: Limpando os buckets...\n";
    for (int i = 0; i < 10; i++) {
        deleteList(&nodeArray[i]);
    }

    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    
    cout << "Lista ordenada final: ";
    displayList(head);

    // Limpar a lista principal
    deleteList(&head);
}

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

void bucketSort(Node** head)
{
    if (*head == nullptr || (*head)->ptrNext == nullptr) return;

    int iLength = 0;
    Node* outer = *head;
    int iMaxValue = outer->iPayload;

    // Determina o comprimento da lista e o maior valor
    while (outer != nullptr) 
    {
        if (iMaxValue < outer->iPayload) iMaxValue = outer->iPayload;
        iLength++;
        outer = outer->ptrNext;
    }

    int iBucketSize = (iMaxValue / 10) + 1; // Para evitar bucket 0 em alguns casos

    outer = *head;

    Node* nodeArray[10] = {nullptr};

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

        Node* current = nodeArray[i];
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