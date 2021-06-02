#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Write a function that returns the number of times target
// appears in a list (like Exercise 6-3 but with linked lists)
// First solve iteratively then recursively
// Reusing previous functions

struct node
{
    int number;
    node *next;
};

// Iterative function to print full string
void printList(node *head)
{
    cout << "Array: ";

    for (node *loopPtr = head; loopPtr != NULL; loopPtr = loopPtr->next)
        cout << loopPtr->number << " ";

    cout << "\n";
}

// Initializes a new node at beginning of list so that original first index
// is chained to the new first index
void headInsert(node *&head, int num)
{
    node *newNode = new node;
    newNode->number = num;
    newNode->next = head;
    head = newNode;
}

int countTargetIterative(node *head, int target)
{
    int i, targetCount = 0;
    for (node *loopPtr = head; loopPtr != NULL; loopPtr = loopPtr->next)
    {
        if (loopPtr->number == target)
            targetCount++;
    }
    return targetCount;
}

int countTargetRecursive(node *head, int target)
{
    // Simplest case
    if (head == NULL)
        return 0;

    // Count of instances of target in rest of list
    int targetCount = countTargetRecursive(head->next, target);

    // If current index is instance of target, add 1 to total
    if (head->number == target)
        targetCount++;

    return targetCount;
}

// Recursive function to delete all nodes
void deleteList(node *head)
{
    if (head == NULL)
        return;
    deleteList(head->next);
    delete head;
}

int main()
{
    srand((unsigned)time(0));
    const int SIZE = 20;
    const int TARGET = 7;
    int iterativeCount, recursiveCount;

    node *head = NULL;

    for (int i = 0; i < SIZE; i++)
    {
        // Generating random number from 1 to 10
        headInsert(head, rand() % 10 + 1);
    }

    printList(head);
    cout << "\n";

    iterativeCount = countTargetIterative(head, TARGET);
    cout << "Occurences of " << TARGET << "(Iterative): " << iterativeCount << "\n";
    recursiveCount = countTargetRecursive(head, TARGET);
    cout << "Occurences of " << TARGET << "(Recursive): " << recursiveCount << "\n";

    if (iterativeCount == recursiveCount)
        cout << "Hooray! The iterative and recursive function returned the same result\n";

    deleteList(head);
    head = NULL;
    return 0;
}