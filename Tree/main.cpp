#include <iostream>
#include "functions.h"

using namespace std;
using namespace functionsTree;

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
    
    cout << "BFS Traversal:";
    bfsTraversal(root);
    cout << endl;
    
    cout << "Tree height:";
    cout << treeHeight(root) << endl;
    
    return 0;
}