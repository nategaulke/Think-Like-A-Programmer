#include <iostream>
using namespace std;

// Store strings in a linked list instead of char *array
// Building from Exercise 4-7, implement concatenate (must copy second string)

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
    str word1 = NULL;
    str word2 = NULL;
    word1 = append(word1, 't');
    word1 = append(word1, 'e');
    word1 = append(word1, 's');
    word1 = append(word1, 't');
    word2 = append(word2, 'b');
    word2 = append(word2, 'e');
    word2 = append(word2, 'd');

    cout << "Concatenate:\nBefore\n";
    printString(word1);
    cout << " ";
    printString(word2);
    cout << "\n\n";

    word1 = concatenate(word1, word2);

    cout << "After\n";
    printString(word1);
    cout << " ";
    printString(word2);
    cout << "\n";

    deleteString(word1);
    deleteString(word2);
    return 0;
}
