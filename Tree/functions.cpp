#include <iostream>
#include "functions.h"

using namespace std;

namespace functionsTree {
    template <typename T>
    Node<T>* createNode(T iData) {
        Node<T>* temp = (Node<T>*)malloc(sizeof(Node<T>));
        
        if (temp == nullptr) {
            cerr << "Erro em createNode: malloc" << endl;
            exit(1);
        }
        
        temp->iPayload = iData;
        temp->ptrLeft = nullptr;
        temp->ptrRight = nullptr;
        
        return temp;
    }

    template <typename T>
    ListNode<T>* createListNode(Node<T>* node) {
        ListNode<T>* temp = (ListNode<T>*)malloc(sizeof(ListNode<T>));
        
        if (temp == nullptr) {
            cerr << "Erro em createNode: malloc" << endl;
            exit(1);
        }
        
        temp->iPayload = node->iPayload;
        temp->ptrNext = nullptr;
        temp->ptrTreeEquivalent = node;
        
        return temp;
    }

    template <typename T>
    void insertEnd(ListNode<T>** head, Node<T>* node) 
    {
        ListNode<T>* newNode = createListNode(node);

        if (*head == nullptr) 
        {
            *head = newNode;
        } 
        else 
        {
            ListNode<T>* temp = *head;
            
            while (temp->ptrNext != nullptr) 
            {
                temp = temp->ptrNext;
            }

            temp->ptrNext = newNode;
        }
    }

    template <typename T>
    void insertEndLinkedList(Node<T>** head, T iPayload) 
    {
        Node<T>* newNode = createNode(iPayload);

        if (*head == nullptr) 
        {
            *head = newNode;
        } 
        else 
        {
            Node<T>* temp = *head;
            
            while (temp->ptrRight != nullptr) 
            {
                temp = temp->ptrRight;
            }
            
            temp->ptrRight = newNode;
            newNode->ptrLeft = temp;
        }
    }

    template <typename T>
    Node<T>* insertNode(Node<T>* root, T iData) {
        if (root == nullptr) {
            return createNode(iData);
        }
        
        if (iData < root->iPayload) {
            root->ptrLeft = insertNode(root->ptrLeft, iData);
        } else {
            root->ptrRight = insertNode(root->ptrRight, iData);
        }
        
        return root;
    }

    template <typename T>
    Node<T>* searchNode(Node<T>* root, T iData)
    {
        if (root == nullptr) return nullptr;
        else if (iData == root->iPayload) return root;
        else if (iData < root->iPayload) return searchNode(root->ptrLeft, iData);
        else return searchNode(root->ptrRight, iData);
    }

    template <typename T>
    Node<T>* searchNodeBFS(Node<T>* root, T iData) {
        if (root == nullptr) return nullptr;

        ListNode<T>* head = nullptr;
        insertEnd(&head, root);
        
        ListNode<T>* QueueFront = head;
        ListNode<T>* QueueRear = head;
        int iQueueFront = 0;

        while (QueueFront != nullptr) {
            Node<T>* currentNode = QueueFront->ptrTreeEquivalent;
            
            if (currentNode->iPayload == iData) {
                return currentNode;
            }

            if (currentNode->ptrLeft != nullptr) {
                insertEnd(&head, currentNode->ptrLeft);
            }

            if (currentNode->ptrRight != nullptr) {
                insertEnd(&head, currentNode->ptrRight);
            }

            QueueFront = QueueFront->ptrNext;
        }

        deleteListNode(&head);

        return nullptr;
    }

    template <typename T>
    Node<T>* deleteNode(Node<T>* root, T iData)
    {
        if (root == nullptr) return nullptr;
        
        if (iData < root->iPayload) root->ptrLeft = deleteNode(root->ptrLeft, iData);
        else if (iData > root->iPayload) root->ptrRight = deleteNode(root->ptrRight, iData);
        else
        {
            Node<T>* ptrTemp = nullptr;
            
            if (root != nullptr)
            {
                ptrTemp = root->ptrRight;
                free(root);
                
                return ptrTemp;
            }
            else if (root->ptrRight == nullptr)
            {
                ptrTemp = root->ptrLeft;
                free(root);
                
                return ptrTemp;
            }
        }
        
        Node<T>* ptrTemp = lesserLeaf(root->ptrRight);
        
        root->iPayload = ptrTemp->iPayload;
        
        root->ptrRight = deleteNode(root->ptrRight, ptrTemp->iPayload);
        
        return root;
    }

    template <typename T>
    void deleteTree(Node<T>** root)
    {
        deleteTreeRecursive(*root);

        *root = nullptr;
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
            nextNode = current->ptrRight;
            free(current);
            current = nextNode;
        }

        *head = nullptr;
    }

    template <typename T>
    void deleteTreeRecursive(Node<T>* node)
    {
        if (node == nullptr) return;
        
        deleteTreeRecursive(node->ptrLeft);
        deleteTreeRecursive(node->ptrRight);

        free(node);
    }

    template <typename T>
    void deleteListNode(ListNode<T>** head) {
        if (*head == nullptr) {
            cout << "Lista já está vazia." << endl;
            return;
        }

        ListNode<T>* current = *head;
        ListNode<T>* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->ptrNext;
            free(current);
            current = nextNode;
        }

        *head = nullptr;
    }

    template <typename T>
    Node<T>* lesserLeaf(Node<T>* root)
    {
        Node<T>* ptrCurrent = root;
        
        while (ptrCurrent && ptrCurrent->ptrLeft != nullptr) ptrCurrent = ptrCurrent->ptrLeft;
        
        return ptrCurrent;
    }


    // template <typename T>
    // void bfsTraversal(Node<T>* root, T iData) {
    //     if (root == nullptr) return nullptr;

    //     int iQueueFront = 0;
    //     int iQueueSize = 0;

    //     Node<T>* head = nullptr;
    //     insertEnd(&head, root->iPayload);
    //     iQueueSize++;
        
    //     Node<T>* QueueFront = head;

    //     while (iQueueFront < iQueueSize) {
    //         Node<T>* currentNode = QueueFront;
    //         QueueFront = QueueFront->ptrRight;
    //         iQueueFront++;

    //         if (currentNode->iPayload == iData) {
    //             return currentNode;
    //         }

    //         if (currentNode->ptrLeft != nullptr) {
    //             insertEnd(&head, currentNode->ptrLeft->iPayload);
    //             iQueueSize++;
    //         }

    //         if (currentNode->ptrRight != nullptr) {
    //             insertEnd(&head, currentNode->ptrRight->iPayload);
    //             iQueueSize++;
    //         }
    //     }

    //     return nullptr;
    // }

    // Parte 3 do trabalho: Monitorar o desempenho de busca em árvore utiliando DFS e BFS
    // Parte 4 do trabalho: Monitorar o desempenho de criação de listas
    // Parte 5 do trabalho: Monitorar o desempenho de criação de árvores

    template <typename T>
    int treeHeight(Node<T>* root) {
        if (root == nullptr) return 0;
        else {
            int iLeftHeight = treeHeight(root->ptrLeft);
            int iRightHeight = treeHeight(root->ptrRight);
            
            return max(iLeftHeight, iRightHeight) + 1;
        }
    }

    template Node<int>* createNode(int iData);
    template ListNode<int>* createListNode(Node<int>* node);
    template void insertEnd(ListNode<int>** head, Node<int>* node); 
    template void insertEndLinkedList(Node<int>** head, int iPayload); 
    template Node<int>* insertNode(Node<int>* root, int iData);
    template Node<int>* searchNode(Node<int>* root, int iData);
    template Node<int>* searchNodeBFS(Node<int>* root, int iData);
    template Node<int>* deleteNode(Node<int>* root, int iData);
    template void deleteTree(Node<int>** root);
    template void deleteTreeRecursive(Node<int>* node);
    template void deleteList(Node<int>** head);
    template void deleteListNode(ListNode<int>** head);
    template Node<int>* lesserLeaf(Node<int>* root);
    // template void bfsTraversal(Node<int>* root, int iData);
    template int treeHeight(Node<int>* root);
}