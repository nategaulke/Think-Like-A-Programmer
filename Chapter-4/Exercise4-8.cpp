#include <iostream>
using namespace std;

// Store strings in a linked list instead of char *array
// Remove a substring of characters from the linked list

struct node
{
    char c;
    node *next;
};

typedef node *str;

// Assumes indices start at 0 and position given is valid;
char characterAt(str s, int position)
{
    node *loopPtr = s;
    for (int i = 0; i < position; i++)
    {
        loopPtr = loopPtr->next;
    }
    return loopPtr->c;
}

// Only words if str is already initialized
node *append(str s, char newC)
{
    // Create the new node
    node *newNode = new node;
    newNode->c = newC;
    newNode->next = NULL;

    // If string is unitialized, use new node to intialize it
    if (s == NULL)
        return newNode;

    // Otherwise loop through, until find next NULL node
    node *loopPtr = s;
    while (loopPtr->next != NULL)
    {
        loopPtr = loopPtr->next;
    }
    loopPtr->next = newNode;
    return s;
}

node *concatenate(str s1, str s2)
{
    // If both are NULL, return nothing
    if (s1 == NULL && s2 == NULL)
    {
        return NULL;
    }

    // If one of the strings is NULL, then return the non-NULL string
    if (s1 == NULL)
    {
        return s2;
    }
    if (s2 == NULL)
    {
        return s1;
    }

    // Otherwise both strings are non-NULL, iterate to end of s1
    node *loopPtr = s1;
    while (loopPtr->next != NULL)
    {
        loopPtr = loopPtr->next;
    }

    // While second string still has characters, create a new node
    // and copy the character
    node *copy = s2;
    while (copy != NULL)
    {
        loopPtr->next = new node;
        loopPtr->next->c = copy->c;
        loopPtr->next->next = NULL;
        copy = copy->next;
        loopPtr = loopPtr->next;
    }
    return s1;
}

node *removeChars(str s1, int position, int length)
{
    if (s1 == NULL)
        return NULL;

    int i = 1, currNode = 0;
    node *loopPtr = s1;
    node *temp = loopPtr;
    node *delNode;

    // Go to the position where we begin deleting or until we reach end of
    while (i < position && loopPtr->next != NULL)
    {
        temp = loopPtr;
        loopPtr = loopPtr->next;
        i++;
    }
    // Temp now points to the node before the chain is deleted
    // LoopPtr points to the first node to be deleted

    if (i == position)
    {
        // Position was valid, so we can begin removing nodes
        // until we've deleted length amount OR we reach the end of the chain
        while (currNode < length && loopPtr != NULL)
        {
            delNode = loopPtr;
            loopPtr = loopPtr->next;
            delete delNode;
            currNode++;
        }
    }

    // If the first node deleted was the original head,
    // then new head is where loopPtr is pointed
    if (position == 1)
    {
        s1 = loopPtr;
    }
    // Otherwise connect the chain to the next node that was not deleted
    else
    {
        temp->next = loopPtr;
    }
    return s1;
}

// Recursive function to print full string
void printString(str s)
{
    if (s == NULL)
    {
        return;
    }
    cout << s->c;
    printString(s->next);
}

// Recursive function to delete all string nodes
void deleteString(str s)
{
    if (s == NULL)
        return;
    deleteString(s->next);
    delete s;
}

int main()
{
    str word = NULL;
    word = append(word, 't');
    word = append(word, 'e');
    word = append(word, 's');
    word = append(word, 't');
    word = append(word, 'b');
    word = append(word, 'e');
    word = append(word, 'd');

    cout << "Remove Substring:\nBefore\n";
    printString(word);
    cout << "\n\n";

    word = removeChars(word, 3, 4);

    cout << "After\n";
    printString(word);
    cout << "\n";

    deleteString(word);
    return 0;
}
