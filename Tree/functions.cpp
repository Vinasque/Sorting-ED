#include <iostream>
#include "functions.h"

using namespace std;

namespace functionsTree {
    template <typename T>
    Node<T>* createNode(T iValue) {
        Node<T>* temp = (Node<T>*)malloc(sizeof(Node<T>));
        
        if (temp == nullptr) {
            cerr << "Erro em createNode: malloc" << endl;
            exit(1);
        }
        
        temp->iPayload = iValue;
        temp->ptrLeft = nullptr;
        temp->ptrRight = nullptr;
        
        return temp;
    }

    template <typename T>
    Node<T>* insertNode(Node<T>* startingNode, T iData) {
        if (startingNode == nullptr) {
            return createNode(iData);
        }
        
        if (iData < startingNode->iPayload) {
            startingNode->ptrLeft = insertNode(startingNode->ptrLeft, iData);
        } else {
            startingNode->ptrRight = insertNode(startingNode->ptrRight, iData);
        }
        
        return startingNode;
    }

    template <typename T>
    void bfsTraversal(Node<T>* ptrStartingNode) {
        if (ptrStartingNode == nullptr) return;
        
        // Parte 1 do trabalho: Alterar para lista encadeada
        Node<T>* nodeQueue[100];
        int iQueueFront = 0;
        int iQueueRear = 0;
        
        nodeQueue[iQueueRear] = ptrStartingNode;
        iQueueRear++;
        
        while (iQueueFront < iQueueRear) {
            Node<T>* currentNode = nodeQueue[iQueueFront];
            iQueueFront++;
            
            cout << currentNode->iPayload << " ";
            
            if (currentNode->ptrLeft != nullptr) {
                nodeQueue[iQueueRear] = currentNode->ptrLeft;
                iQueueRear++;
            }
            
            if (currentNode->ptrRight != nullptr) {
                nodeQueue[iQueueRear] = currentNode->ptrRight;
                iQueueRear++;
            }
        }
    }

    // Parte 2 do trabalho: Elaborar busca utilizando BFS (já fizemos o DFS)
    // Parte 3 do trabalho: Monitorar o desempenho de busca em árvore utiliando DFS e BFS
    // Parte 4 do trabalho: Monitorar o desempenho de criação de listas
    // Parte 5 do trabalho: Monitorar o desempenho de criação de árvores

    template <typename T>
    int treeHeight(Node<T>* ptrStartingNode) {
        if (ptrStartingNode == nullptr) return 0;
        else {
            int iLeftHeight = treeHeight(ptrStartingNode->ptrLeft);
            int iRightHeight = treeHeight(ptrStartingNode->ptrRight);
            
            return max(iLeftHeight, iRightHeight) + 1;
        }
    }

    template Node<int>* createNode(int iValue);
    template Node<int>* insertNode(Node<int>* root, int iValue);
    template void bfsTraversal(Node<int>* root);
    template int treeHeight(Node<int>* root);
}