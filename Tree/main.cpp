#include <iostream>
#include <chrono>
#include <cstdlib>
#include "functions.h"

using namespace std;
using namespace functionsTree;
using namespace std::chrono;

int main()
{
    Node<int>* root = nullptr;
    
    root = insertNode(root, 42);
    root = insertNode(root, 13);
    root = insertNode(root, 11);
    root = insertNode(root, 10);
    root = insertNode(root, 28);
    root = insertNode(root, 51);
    root = insertNode(root, 171);
    
    cout << "BFS Traversal:" << endl;
    Node<int>* foundNode = nullptr;
    foundNode = searchNodeBFS(root, 10);
    cout << "Value Found: " <<  foundNode->iPayload << endl;
    cout << endl;
    
    cout << "Tree height:";
    cout << treeHeight(root) << endl;
    
    Node<int>* rootBig = nullptr;

    for (int j = 1; j < 101; j++)
    {
        for (int i = 0; i < 10000; ++i) 
        {
            int iRandNum = rand() % 100 + 1; //Entre 1 e 100
            rootBig = insertNode(rootBig, iRandNum);
        }

        int iRandom = rand() % 100 + 1;

        auto timeStartDFS = high_resolution_clock::now();
        searchNode(rootBig, iRandom);
        auto timeStopDFS = high_resolution_clock::now();

        auto timeDurationDFS = duration_cast<nanoseconds>(timeStopDFS - timeStartDFS);
        cout << "(" << j << ") DFS Search: " << timeDurationDFS.count() << " nanosegundos." << endl;

        auto timeStartBFS = high_resolution_clock::now();
        searchNodeBFS(rootBig, iRandom);
        auto timeStopBFS = high_resolution_clock::now();

        auto timeDurationBFS = duration_cast<nanoseconds>(timeStopBFS - timeStartBFS);
        cout << "(" << j << ") BFS Search: " << timeDurationBFS.count() << " nanosegundos." << endl;

        deleteTree(&rootBig);
        rootBig = nullptr;
    }

    return 0;
}