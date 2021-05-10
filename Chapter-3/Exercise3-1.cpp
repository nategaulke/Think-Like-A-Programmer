#include <iostream>
#include <string>
using namespace std;

// Use qsort to sort array of student structs (by grade, then by student ID)
// Using the example student Array list (p. 70, Fourth Printing)
// Issue printing out the student names but the IDS associated with the grade do print out correctly

struct student
{
    int grade;
    int studentID;
    string name;
};

// qsort function for sorting by grade
int compareGrade(const void *A, const void *B)
{
    student *stuA = (student *)A;
    student *stuB = (student *)B;
    return stuA->grade - stuB->grade;
}

// qsort function for sorting by studentID
int compareID(const void *A, const void *B)
{
    student *stuA = (student *)A;
    student *stuB = (student *)B;
    return stuA->studentID - stuB->studentID;
}

int main()
{
    const int ARRAY_SIZE = 10;
    student studentArray[ARRAY_SIZE] =
        {
            {87, 10001, "Fred"},
            {28, 10002, "Tom"},
            {100, 10003, "Alistair"},
            {78, 10004, "Sasha"},
            {84, 10005, "Erin"},
            {98, 10006, "Belinda"},
            {75, 10007, "Leslie"},
            {70, 10008, "Candy"},
            {81, 10009, "Aretha"},
            {68, 10010, "Veronica"},
        };

    // Since I will sort it back in order, I won't create a copy array of students to sort the data
    qsort(studentArray, ARRAY_SIZE, sizeof(student), compareGrade);
    cout << "Sorted by Grade:\n";
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << "Grade: " << studentArray[i].grade << "\tID: " << studentArray[i].studentID << "\n";
    }

    qsort(studentArray, ARRAY_SIZE, sizeof(student), compareID);
    cout << "\nSorted by ID:\n";
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << "Grade: " << studentArray[i].grade << "\tID: " << studentArray[i].studentID << "\n";
    }
    return 0;
}
