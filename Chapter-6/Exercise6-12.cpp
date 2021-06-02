#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
using namespace std;

// Attempt to write recursive functions for the
// average, median, and mode of binary search tree

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
        while (!s.empty())
            s.pop();
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

    double average()
    {
        // Store values in stack
        buildStack(root);

        double sum = 0.0;
        int count = s.size();
        // Prevents division by 0 error
        if (count == 0)
            return 0.0;

        // Count up the total of all the nodes
        while (!s.empty())
        {
            sum += s.top();
            s.pop();
        }

        return sum / count;
        // return countTotalSum(root) / countTotalNodes(root);
    }

    int median()
    {
        // Store values in stack
        buildStack(root);

        int retval, i, size = s.size();

        // If no values, then return 0
        if (size == 0)
            retval = 0;
        // If size is even, then two middle values make median
        else if (size % 2 == 0)
        {
            for (i = 1; i < size / 2; i++)
                s.pop();

            int val1, val2;
            val1 = s.top();
            s.pop();
            val2 = s.top();
            retval = (val1 + val2) / 2;
        }
        // Otherwise value directly in middle is median
        else
        {
            for (i = 0; i < size / 2; i++)
                s.pop();

            retval = s.top();
        }

        // Remove rest of values
        while (!s.empty())
            s.pop();

        return retval;
    }

    int mode()
    {
        // Store values in stack
        buildStack(root);

        int size = s.size();
        // Return 0 if no values
        if (size == 0)
            return 0;
        int mostFrequent, current;
        int greatestFrequency = 0, frequency = 0;
        while (!s.empty())
        {
            // Current value from top of stack
            current = s.top();
            // Increase frequency based on how many values match current value
            // (inorder traversal when building stack ensures values are next to each other)
            while (!s.empty() && s.top() == current)
            {
                frequency++;
                s.pop();
            }
            // If frequency of the current value is greater than the greatest frequency
            // Store the new greatest frequency and the most frequent value
            if (frequency > greatestFrequency)
            {
                greatestFrequency = frequency;
                mostFrequent = current;
            }
            frequency = 0;
        }
        return mostFrequent;
        /* int *solution = modeRecursive(root);
        int retval = solution[0];
        delete[] solution;
        return retval; */
    }

private:
    node *root;
    stack<int> s;
    /* Eventually decided implementing stack (using previous course knowledge)
       was best for a good runtime for giving the statistics. I came up with a
       solution without using a stack for average & mode but neither were as 
       efficient. There might be a better way to implement but did not want
       to look at other's solutions */

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
        // Greater/Duplicates go to right subtree
        else if (rootPtr->data <= num)
            BSTinsert(rootPtr->right, num);
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

    // Should confirm if binary search tree since will print from least to greatest
    void buildStack(node *rootPtr)
    {
        if (rootPtr == NULL)
            return;

        buildStack(rootPtr->left);
        s.push(rootPtr->data);
        buildStack(rootPtr->right);
    }

    // Sums all the nodes in the tree
    double countTotalSum(node *rootPtr)
    {
        if (rootPtr == NULL)
            return 0.0;

        return rootPtr->data + countTotalSum(rootPtr->left) + countTotalSum(rootPtr->right);
    }

    // Counts # of nodes in binary tree
    int countTotalNodes(node *rootPtr)
    {
        if (rootPtr == NULL)
            return 0;

        return 1 + countTotalNodes(rootPtr->left) + countTotalNodes(rootPtr->right);
    }

    // Returns the number of times a certain number appears in a binary tree
    int findTarget(node *rootPtr, int target)
    {
        if (rootPtr == NULL)
            return 0;

        int count = 0;

        if (rootPtr->data == target)
            count = 1;

        count += findTarget(rootPtr->left, target) + findTarget(rootPtr->right, target);

        return count;
    }

    /*
    // Inefficient solution to finding mode recursively
    int *modeRecursive(node *rootPtr)
    {
        if (rootPtr == NULL)
        {
            int *error = new int[2];
            error[0] = INT_MIN;
            error[1] = 0;
            return error;
        }

        int *rootCount = new int[2];

        int *left = modeRecursive(rootPtr->left);
        int *right = modeRecursive(rootPtr->right);

        // First index is the number
        rootCount[0] = rootPtr->data;
        // Second index is the number of times it appears in the tree
        rootCount[1] = findTarget(rootPtr, rootPtr->data);

        // Checking which subtree has value that appears most often or if
        // root has the value that appears most often in the tree
        // deallocates the arrays that don't appear as often
        if (left[1] > rootCount[1] && left[1] > right[1])
        {
            delete[] rootCount;
            delete[] right;
            return left;
        }
        else if (right[1] > rootCount[1] && right[1] >= left[1])
        {
            delete[] rootCount;
            delete[] left;
            return right;
        }
        else
        {
            delete[] left;
            delete[] right;
            return rootCount;
        }
    } */

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
    const int SIZE = 10;
    int randomNum;

    for (int i = 0; i < SIZE; i++)
    {
        // Generating random number from 1 to 15
        randomNum = rand() % 15 + 1;
        tree.insert(randomNum);
    }

    tree.print();

    cout << "The average of this tree is: " << tree.average() << "\n";
    cout << "The median of this tree is: " << tree.median() << "\n";
    cout << "The mode of this tree is: " << tree.mode() << "\n";

    return 0;
}