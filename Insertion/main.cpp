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
    insertionSort(&head);
    auto timeStop = high_resolution_clock::now();

    cout << "Lista ordenada: ";
    displayList(head);

    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;

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

        auto timeStartBig = high_resolution_clock::now();
        insertionSort(&headBig);
        auto timeStopBig = high_resolution_clock::now();

        auto timeDurationBig = duration_cast<nanoseconds>(timeStopBig - timeStartBig);
        cout << "(" << j << ") Função original: " << timeDurationBig.count() << " nanosegundos." << endl;
    }

    return 0;
}