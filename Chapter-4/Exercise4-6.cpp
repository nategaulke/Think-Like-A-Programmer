#include <iostream>
using namespace std;

// Store strings in a linked list instead of char *array
// Implement append and characterAt

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

// Recursive function to print full string
void printString(str s)
{
    if (s == NULL)
    {
        cout << "\n";
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
    str word = new node;
    word->c = 't';
    word->next = NULL;
    cout << "Before Appending: ";
    printString(word);
    word = append(word, 'e');
    word = append(word, 's');
    word = append(word, 't');
    cout << "After Appending: ";
    printString(word);
    cout << "Character at Index 2: " << characterAt(word, 2) << "\n";
    deleteString(word);
    return 0;
}
