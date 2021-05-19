#include <iostream>
using namespace std;

// Solve an array problem that is limited by the size of its array
// using dynamically allocated arrays instead

// Problem: Allow user to add student grades without knowing how many students there are

void doubleArray(int *&array, int size)
{
    int *temp = new int[size * 2];
    // Copy old values of array
    for (int i = 0; i < size; i++)
    {
        temp[i] = array[i];
    }

    // Destry old array and give new doubled array address
    delete[] array;
    array = temp;
}

int addValue(int *&grades, int size, int grade)
{
    int ptr = 0;

    // Find the next empty space(marked with '-1')
    while (grades[ptr] != -1)
    {
        ptr++;
    }

    // If last space is last space allocated, double the array size
    if (ptr == size - 1)
    {
        doubleArray(grades, size);
        size = size * 2;
    }

    // Add value, mark next empty space
    grades[ptr] = grade;
    grades[ptr + 1] = -1;

    return size;
}

double average(int *array, int size)
{
    double avg = 0;
    int data = 0;
    for (int i = 0; i < size && array[i] != -1; i++)
    {
        avg += array[i];
        data++;
    }
    return avg / data;
}

int main()
{
    int grade, size = 5;
    int *grades = new int[size];
    grades[0] = -1;
    cout << "Add the grades of students. To stop adding grades, enter -1.\n";
    cin >> grade;
    while (grade != -1)
    {
        size = addValue(grades, size, grade);
        cin >> grade;
    }
    cout << "Mode: " << average(grades, size) << "\n";
    delete[] grades;
    grades = NULL;
    cout << "Thank you and goodbye\n";
    return 0;
}
