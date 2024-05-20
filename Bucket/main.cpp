#include <iostream>
#include <chrono>
#include <cstdlib>
#include "functions.h"

using namespace std;
using namespace std::chrono;

int main() {
    cout << "Teste com a função original:\n" << endl;
    
    int arriNumbers1[] = {42, 7, 2, 3, 12, 1, 4, 10, 13};
    int iArraySize = 9;
    
    Node* head = nullptr;
    for (int i = 0; i < iArraySize; ++i) 
    {
        insertEnd(&head, arriNumbers1[i]);
    }

    cout << "Lista original: ";
    displayList(head);

    auto timeStart = high_resolution_clock::now();
    bucketSort(&head);
    auto timeStop = high_resolution_clock::now();

    cout << "Lista ordenada: ";
    displayList(head);

    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;

    cout << "\nUsando 100 listas com 10000 termos:\n" << endl;

    Node* headBig = nullptr;
    Node* headBigOptimized = nullptr;

    // for (int j = 1; j < 101; j++)
    // {
    //     for (int i = 0; i < 10000; ++i) 
    //     {
    //         int iRandNum = rand() % 100 + 1; //Entre 1 e 100
    //         insertEnd(&headBig, iRandNum);
    //         insertEnd(&headBigOptimized, iRandNum);
    //     }

    //     auto timeStartBig = high_resolution_clock::now();
    //     bucketSort(&headBig);
    //     auto timeStopBig = high_resolution_clock::now();

    //     auto timeDurationBig = duration_cast<nanoseconds>(timeStopBig - timeStartBig);
    //     cout << "(" << j << ") Função original: " << timeDurationBig.count() << " nanosegundos." << endl;

    //     deleteList(&headBig);
    //     deleteList(&headBigOptimized);
    // }

    return 0;
}