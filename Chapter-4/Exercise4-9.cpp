#include <iostream>
using namespace std;

// Converts an integer into a linked list, each node containing one digit

struct node
{
    int digit;
    node *next;
};

typedef node *Number;

// Recursive function to print full string
void printNum(Number num)
{
    if (num == NULL)
    {
        return;
    }
    cout << num->digit;
    printNum(num->next);
}

// Recursive function to delete all string nodes
void deleteNum(Number num)
{
    if (num == NULL)
        return;
    deleteNum(num->next);
    delete num;
}

// Initializes a new node at beginning of list so that original first index
// is chained to the new first index
void headinsert(Number &num, int data)
{
    node *newNode = new node;
    newNode->digit = data;
    newNode->next = num;
    num = newNode;
}

void intToList(Number &num, int convert)
{
    // Checking if a previous value needs need to deleted
    if (num != NULL)
    {
        deleteNum(num);
        num = NULL;
    }
    if (convert == 0)
    {
        headinsert(num, convert);
    }

    // While convert still has more digits, take the least significant digit
    // Insert it at the beginning then remove that digit from the integer
    while (convert != 0)
    {
        headinsert(num, convert % 10);
        convert /= 10;
    }
}

int main()
{
    Number num = NULL;
    int convert = 149;
    cout << "Convert a positive integer to linked list\n";
    cout << "Before: " << convert << "\n\n";
    intToList(num, convert);
    cout << "After: ";
    printNum(num);
    cout << "\n";
    deleteNum(num);
    return 0;
}
