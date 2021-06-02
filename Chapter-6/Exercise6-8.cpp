#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Write a function for a linked list that is difficult for
// iteration but easier with recursion

// My example: Add node to tail (end) of linked list instead of head (front)

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

node *create_node(int num)
{
    node *newNode = new node;
    newNode->number = num;
    newNode->next = NULL;
    return newNode;
}

void tailInsert(node *&head, int num)
{
    // If list has not been initialized yet
    if (head == NULL)
    {
        head = create_node(num);
        return;
    }
    // Base next: next node will be tail
    if (head->next == NULL)
    {
        head->next = create_node(num);
        return;
    }

    // Keep going to find end
    tailInsert(head->next, num);
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
    const int SIZE = 10;
    int randomNum;

    node *head = NULL;

    for (int i = 0; i < SIZE; i++)
    {
        // Generating random number from 1 to 10
        randomNum = rand() % 10 + 1;
        cout << "Adding " << randomNum << " to the list...\n";
        tailInsert(head, randomNum);
    }

    cout << "Printing list from first inserted to last inserted\n";
    printList(head);
    cout << "\n";

    deleteList(head);
    head = NULL;
    return 0;
}