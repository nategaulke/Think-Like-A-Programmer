#include <iostream>
using namespace std;

// Building from Exercise 4-9, create a linked list number that
// adds two linked list integers together

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
        return;

    printNum(num->next);
    cout << num->digit;
}

// Recursive function to delete all string nodes
void deleteNum(Number num)
{
    if (num == NULL)
        return;
    deleteNum(num->next);
    delete num;
}

// Inserting at end of list since easier to add digits this way
// least significant digit is put at beginning of linked list
void tailinsert(Number &num, int data)
{
    // If no node at front yet, create it
    if (num == NULL)
    {
        num = new node;
        num->digit = data;
        num->next = NULL;
        return;
    }

    // Otherwise iterate to end of list & initialize new node
    node *temp = num;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new node;
    temp->next->digit = data;
    temp->next->next = NULL;
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
        tailinsert(num, convert);
    }
    // While convert still has more digits, take the least significant digit
    // Insert it at the beginning then remove that digit from the integer
    while (convert != 0)
    {
        tailinsert(num, convert % 10);
        convert /= 10;
    }
}

void addIntLists(Number num1, Number num2, Number &num3)
{
    int add, carry = 0;
    // Can't add the values if one of them is NULL
    if (num1 == NULL || num2 == NULL)
    {
        cout << "One or both numbers are unitialized and can't be summed\n";
        return;
    }
    // If num3 was already initialized, erase the previous value
    if (num3 != NULL)
    {
        deleteNum(num3);
        num3 = NULL;
    }
    node *num1Ptr = num1;
    node *num2Ptr = num2;

    // Add all non-NULL digits together, keeping track of any carry over values
    while (num1Ptr != NULL || num2Ptr != NULL)
    {
        if (num1Ptr == NULL)
        {
            add = carry + num2Ptr->digit;
            tailinsert(num3, add % 10);
            num2Ptr = num2Ptr->next;
            carry = add / 10;
        }
        else if (num2Ptr == NULL)
        {
            add = carry + num1Ptr->digit;
            tailinsert(num3, add % 10);
            num1Ptr = num1Ptr->next;
            carry = add / 10;
        }
        else
        {
            add = carry + num1Ptr->digit + num2Ptr->digit;
            tailinsert(num3, add % 10);
            carry = add / 10;
            num1Ptr = num1Ptr->next;
            num2Ptr = num2Ptr->next;
        }
    }

    if (carry != 0)
    {
        tailinsert(num3, carry);
    }
}

int main()
{
    Number num1 = NULL;
    Number num2 = NULL;
    Number num3 = NULL;
    intToList(num1, 48);
    intToList(num2, 152);

    addIntLists(num1, num2, num3);

    cout << "Adding linked list integers together\n";
    printNum(num1);
    cout << " + ";
    printNum(num2);
    cout << " = ";
    printNum(num3);
    cout << "\n";

    deleteNum(num1);
    deleteNum(num2);
    deleteNum(num3);
    return 0;
}
