#include <iostream>
using namespace std;

// create removeRecord, which takes a student Collection and removes student
// with matching studentNum from collection
// Using node struct, addRecord function, and data that was used in Chapter 4

struct node
{
    int studentNum;
    int grade;
    node *next;
};

typedef node *studentCollection;

void addRecord(studentCollection &sc, int stuNum, int gr)
{
    node *newNode = new node;
    newNode->studentNum = stuNum;
    newNode->grade = gr;
    newNode->next = sc;
    sc = newNode;
}

node *removeRecord(studentCollection sc, int stuNum)
{
    node *loopPtr = sc;

    // If no records exist, can't remove anything
    if (loopPtr == NULL)
    {
        return sc;
    }
    // If first record matches, then don't need to worry about keeping list chained
    else if (loopPtr->studentNum == stuNum)
    {
        node *temp = loopPtr->next;
        delete loopPtr;
        sc = temp;
        return sc;
    }

    // Assumes we have at least two non-NULL pointers
    while (loopPtr->next != NULL)
    {
        if (loopPtr->next->studentNum == stuNum)
        {
            node *temp = loopPtr->next->next;
            delete loopPtr->next;
            loopPtr->next = temp;
            break;
        }
        loopPtr = loopPtr->next;
    }
    return sc;
}

// Recursive function to print all student records (using knowledge from previous class)
void printRecords(studentCollection sc)
{
    if (sc == NULL)
        return;
    cout << "Student Number: " << sc->studentNum << "\tStudent Grade: " << sc->grade << "\n";
    printRecords(sc->next);
}

// Recursive function to remove all records (using knowledge from previous class)
void removeAll(studentCollection sc)
{
    if (sc == NULL)
        return;
    removeAll(sc->next);
    delete sc;
}

int main()
{
    studentCollection sc = NULL;
    addRecord(sc, 1001, 78);
    addRecord(sc, 1012, 93);
    addRecord(sc, 1076, 85);
    addRecord(sc, 1027, 45);
    addRecord(sc, 1098, 73);
    cout << "Before:\n";
    printRecords(sc);
    sc = removeRecord(sc, 1098);
    sc = removeRecord(sc, 1001);
    sc = removeRecord(sc, 1076);
    cout << "\nAfter:\n";
    printRecords(sc);
    removeAll(sc);
    return 0;
}
