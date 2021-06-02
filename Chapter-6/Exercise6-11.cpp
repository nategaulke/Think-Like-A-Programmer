#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Recursive function that correctly inserts new node into binary search tree

// Using a class
class BinarySearchTree
{
private:
    struct node
    {
        int data;
        node *left;
        node *right;
    };

public:
    BinarySearchTree()
    {
        root = NULL;
    }

    ~BinarySearchTree()
    {
        deleteTree(root);
        root = NULL;
    }

    void insert(int num)
    {
        BSTinsert(root, num);
    }

    void print()
    {
        cout << "Inorder Traversal: ";
        inOrder(root);
        cout << "\n";
    }

private:
    node *root;

    node *create_node(int num)
    {
        node *newNode = new node;
        newNode->data = num;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    void BSTinsert(node *&rootPtr, int num)
    {
        // Insert new number into tree
        if (rootPtr == NULL)
            rootPtr = create_node(num);
        // Otherwise check where to properly insert
        else if (rootPtr->data > num)
            BSTinsert(rootPtr->left, num);
        else if (rootPtr->data < num)
            BSTinsert(rootPtr->right, num);
        // No duplicates
        else
            ;
    }

    // Should confirm if binary search tree since will print from least to greatest
    void inOrder(node *rootPtr)
    {
        if (rootPtr == NULL)
            return;

        inOrder(rootPtr->left);
        cout << rootPtr->data << " ";
        inOrder(rootPtr->right);
    }

    // Recursive function to delete all nodes
    void deleteTree(node *rootPtr)
    {
        if (rootPtr == NULL)
            return;

        deleteTree(rootPtr->left);
        deleteTree(rootPtr->right);
        delete rootPtr;
    }
};

int main()
{
    BinarySearchTree tree;
    srand((unsigned)time(0));
    const int SIZE = 8;
    int randomNum;

    for (int i = 0; i < SIZE; i++)
    {
        // Generating random number from 1 to 100
        randomNum = rand() % 100 + 1;
        cout << "Adding " << randomNum << " to the tree...\n";
        tree.insert(randomNum);
    }

    tree.print();

    return 0;
}