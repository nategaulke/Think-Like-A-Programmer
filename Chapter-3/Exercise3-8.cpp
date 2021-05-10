#include <iostream>
#include <string>
using namespace std;

// Find the quartiles of a group of students
// Using the example student Array list (p. 70, Fourth Printing)

struct student
{
    int grade;
    int studentID;
    string name;
};

// Compare function for qsort
int compare(const void *voidA, const void *voidB)
{
    int *intA = (int *)(voidA);
    int *intB = (int *)(voidB);
    return *intA - *intB;
}

// Instead of sorting students, copy their grades into a separate array
void copyGrades(student stuArray[], int grades[], int ARRAY_SIZE)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
        grades[i] = stuArray[i].grade;
}

int main()
{
    const int QUARTER = 3;
    const int ARRAY_SIZE = 10;
    int split, mid;
    double q1, q2, q3;
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

    int grades[ARRAY_SIZE];
    copyGrades(studentArray, grades, ARRAY_SIZE);
    qsort(grades, ARRAY_SIZE, sizeof(int), compare);

    // "Split up" the array into 4 sections
    split = ARRAY_SIZE / QUARTER;

    // Calculate the quartiles
    q1 = (double)grades[split - 1];

    if (split * QUARTER != ARRAY_SIZE)
        q3 = (double)grades[split * 2];
    else
        q3 = (double)grades[split * 2 - 1];

    mid = ARRAY_SIZE / 2;

    // If there is an even amount of data, must find average of two midpoints
    if (ARRAY_SIZE % 2 == 0)
        q2 = (grades[mid] + grades[mid - 1]) / 2.0;
    else
        q2 = grades[mid];

    cout << "Sorted by Grade: ";
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << grades[i] << ", ";
    }
    cout << "\n";
    cout << "To score better than 25% of students(1st quartile), a student must get a grade better than " << q1 << "\n";
    cout << "To score better than 50% of students(2nd quartile), a student must get a grade better than " << q2 << "\n";
    cout << "To score better than 75% of students(3rd quartile), a student must get a grade better than " << q3 << "\n";
    return 0;
}