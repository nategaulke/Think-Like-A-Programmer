#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Write a boolean function to find whether a binary number (in linked list)
// has odd parity (odd number of 1 bits); (Same as Exercise 6-2 but with linked lists)
// first iteratively then recursively
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

bool determineOddParityIterative(node *head)
{
    int i, oneCount = 0;
    for (node *loopPtr = head; loopPtr != NULL; loopPtr = loopPtr->next)
    {
        if (loopPtr->number == 1)
            oneCount++;
    }
    if (oneCount % 2 == 0)
        return false;
    else
        return true;
}

bool determineOddParityRecursive(node *head)
{
    // Simplest case
    if (head == NULL)
        return false;

    // Determine if rest of list has odd parity
    bool odd = determineOddParityRecursive(head->next);

    // Find out if current number is 1
    bool curr = (head->number == 1);

    // If the rest of list has odd parity, then current digit must
    // be 0 to maintain "true" for odd parity
    if (odd)
    {
        if (curr)
            return false;
        else
            return true;
    }
    // If the rest of the list does not have odd parity, then current
    // digit must be 1 for their to be odd parity
    else
    {
        if (curr)
            return true;
        else
            return false;
    }
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
    const int SIZE = 8;

    node *head = NULL;

    for (int i = 0; i < SIZE; i++)
    {
        // Generating random order of 0s and 1s
        headInsert(head, rand() % 2);
    }

    printList(head);
    cout << "\n";

    bool iterativeAnswer = determineOddParityIterative(head);
    cout << "The iterative answer is " << iterativeAnswer << "\n";
    bool recursiveAnswer = determineOddParityRecursive(head);
    cout << "The recursive answer is " << recursiveAnswer << "\n";

    if (iterativeAnswer == recursiveAnswer)
        cout << "Hooray! Our answers match.\n";

    deleteList(head);
    head = NULL;
    return 0;
}