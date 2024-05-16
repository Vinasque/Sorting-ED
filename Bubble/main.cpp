#include <iostream>
#include <chrono>
#include "functions.h"

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

int main() 
{
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

     cout << "\nUsando 100 listas com 10000 termos:\n" << endl;

    Node* headBig = nullptr;
    Node* headBigOptimized = nullptr;
    
    for (int j = 1; j < 101; j++)
    {
        for (int i = 0; i < 10000; ++i) 
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
        cout << "(" << j << ") Função original: " << timeDurationBig.count() << " nanosegundos." << endl;
    
        auto timeDurationBigOptimized = duration_cast<nanoseconds>(timeStopBigOptimized - timeStartBigOptimized);
        cout << "(" << j << ") Função otimizada: " << timeDurationBigOptimized.count() << " nanosegundos." << endl;
    }

    return 0;
}