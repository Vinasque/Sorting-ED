#include <iostream>
#include <chrono>
#include <cstdlib>
#include "functions.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

using std::rand;

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

    cout << "\nUsando 100 listas com 10000 termos:\n" << endl;

    Node* headBig = nullptr;
    Node* headBigOptimized = nullptr;

    for (int j = 1; j < 101; j++)
    {
        for (int i = 0; i < 1000; ++i) 
        {
            int iRandNum = rand() % 101; //Entre 0 e 100
            insertEnd(&headBig, iRandNum);
            insertEnd(&headBigOptimized, iRandNum);
        }

        auto timeStartBigOptimized = high_resolution_clock::now();
        optimizedSelectionSort(headBigOptimized);
        auto timeStopBigOptimized = high_resolution_clock::now();

        auto timeStartBig = high_resolution_clock::now();
        selectionSort(headBig);
        auto timeStopBig = high_resolution_clock::now();

        auto timeDurationBig = duration_cast<nanoseconds>(timeStopBig - timeStartBig);
        cout << "(" << j << ") Função original: " << timeDurationBig.count() << " nanosegundos." << endl;

        auto timeDurationBigOptimized = duration_cast<nanoseconds>(timeStopBigOptimized - timeStartBigOptimized);
        cout << "(" << j << ") Função otimizada: " << timeDurationBigOptimized.count() << " nanosegundos." << endl;

        deleteList(&headBig);
        deleteList(&headBigOptimized);
    }

    return 0;
}