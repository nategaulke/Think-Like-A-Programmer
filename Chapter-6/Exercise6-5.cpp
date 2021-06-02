#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Write a function to find the sum of all the positive numbers
// in an linked list (same as 6-1 but with linked lists)
// First iteratively then recursively
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

int findPositiveSumIterative(node *head)
{
    int sum = 0;
    for (node *loopPtr = head; loopPtr != NULL; loopPtr = loopPtr->next)
    {
        if (loopPtr->number > 0)
            sum += loopPtr->number;
    }
    return sum;
}

int findPositiveSumRecursive(node *head)
{
    if (head == NULL)
        return 0;

    int sum = findPositiveSumRecursive(head->next);
    if (head->number > 0)
        sum += head->number;

    return sum;
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
    int iterativeSum, recursiveSum;

    node *head = NULL;

    for (int i = 0; i < SIZE; i++)
    {
        // Generating random numbers from -20 to 20
        headInsert(head, rand() % 41 - 20);
    }

    printList(head);
    cout << "\n";

    iterativeSum = findPositiveSumIterative(head);
    cout << "Iterative Sum: " << iterativeSum << "\n";
    recursiveSum = findPositiveSumRecursive(head);
    cout << "Resursive Sum: " << recursiveSum << "\n";

    if (iterativeSum == recursiveSum)
        cout << "Hooray! The iterative and recursive function returned the same result\n";

    deleteList(head);
    head = NULL;
    return 0;
}