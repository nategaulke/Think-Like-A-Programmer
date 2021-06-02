#include <iostream>
using namespace std;

// Write a function that checks whether a binary tree
// is a max heap (node is greater than its lift & right subtrees)

struct node
{
    int data;
    node *left;
    node *right;
};

node *create_node(int num)
{
    node *newNode = new node;
    newNode->data = num;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool checkForHeap(node *root)
{
    // Simplest case; A null tree technically could be a heap
    if (root == NULL)
        return true;

    // Short circuits if left is null but otherwise if greater than root
    // then not max heap (same applies for right branch)
    if (root->left != NULL && root->left->data > root->data)
        return false;
    if (root->right != NULL && root->right->data > root->data)
        return false;
    // Otherwise go further down tree to find out if rest of tree follows rules of heap
    return checkForHeap(root->left) && checkForHeap(root->right);
}

void inOrder(node *root)
{
    if (root == NULL)
        return;

    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

// Recursive function to delete all nodes
void deleteTree(node *root)
{
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    /*
            Binary Tree(Heap)
                  100
               /      \
              90       80
             /  \     /  \ 
            70  60   50  40
    */
    node *root = create_node(100);
    root->left = create_node(90);
    root->right = create_node(80);
    root->left->left = create_node(70);
    root->left->right = create_node(60);
    root->right->left = create_node(50);
    root->right->right = create_node(40);

    cout << "Inorder: ";
    inOrder(root);
    cout << "\n";

    if (checkForHeap(root))
        cout << "The binary tree is indeed a heap\n";
    else
        cout << "The binary tree is not a heap\n";

    deleteTree(root);
    root = NULL;
    cout << "\n";

    /*
        Binary Tree(NOT a Heap)
                  60
               /      \
              70       80
             /  \     /  \ 
            90  3   50   40
    */
    root = create_node(60);
    root->left = create_node(70);
    root->right = create_node(80);
    root->left->left = create_node(90);
    root->left->right = create_node(3);
    root->right->left = create_node(50);
    root->right->right = create_node(40);

    cout << "Inorder: ";
    inOrder(root);
    cout << "\n";

    if (checkForHeap(root))
        cout << "The binary tree is indeed a heap\n";
    else
        cout << "The binary tree is not a heap\n";

    deleteTree(root);
    return 0;
}