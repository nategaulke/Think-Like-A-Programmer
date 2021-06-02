#include <iostream>
#include <climits>
using namespace std;

// Write recursive function to check if binary tree is a binary search tree
// (Left subtree less than root, right subtree greater than root)

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

// Should confirm if binary search tree since will print from least to greatest
void inOrder(node *root)
{
    if (root == NULL)
        return;

    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

// Greatest node in BST is rightmost node
int find_maxBST(node *root)
{
    if (root == NULL)
        return INT_MIN;

    while (root->right != NULL)
        root = root->right;

    return root->data;
}

// Smallest node in BST is leftmost node
int find_minBST(node *root)
{
    if (root == NULL)
        return INT_MAX;

    while (root->left != NULL)
        root = root->left;

    return root->data;
}

bool checkIfBST(node *root)
{
    if (root == NULL)
        return true;

    // Greatest value in left subtree should still be smaller than root
    if (root->left != NULL && find_maxBST(root->left) > root->data)
        return false;

    // Similarly, smallest value in right subtree should still be greater than root
    if (root->right != NULL && find_minBST(root->right) < root->data)
        return false;

    return checkIfBST(root->left) && checkIfBST(root->right);
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
            Binary Search Tree
                  50
               /      \
              40       60
             /  \     /  \ 
            35  45   55  75
    */
    node *root = create_node(50);
    root->left = create_node(40);
    root->right = create_node(60);
    root->left->left = create_node(35);
    root->left->right = create_node(45);
    root->right->left = create_node(55);
    root->right->right = create_node(75);

    cout << "Inorder: ";
    inOrder(root);
    cout << "\n";

    if (checkIfBST(root))
        cout << "The binary tree is indeed a binary search tree\n";
    else
        cout << "The binary tree is not a binary search tree\n";

    deleteTree(root);
    root = NULL;
    cout << "\n";

    /*
            Binary Tree (Not BST)
                  50
               /      \
              40       60
             /  \     /  \ 
            35  62   55  75
    */

    root = create_node(50);
    root->left = create_node(40);
    root->right = create_node(60);
    root->left->left = create_node(35);
    root->left->right = create_node(62);
    root->right->left = create_node(55);
    root->right->right = create_node(75);

    cout << "Inorder: ";
    inOrder(root);
    cout << "\n";

    if (checkIfBST(root))
        cout << "The binary tree is indeed a binary search tree\n";
    else
        cout << "The binary tree is not a binary search tree\n";

    deleteTree(root);
    return 0;
}