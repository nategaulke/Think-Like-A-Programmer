#include <iostream>
using namespace std;

// Write boolean function that determines whether an array is sorted
// Using the example array from p. 57, Fourth Printing

bool isSorted(int array[], int ARRAY_SIZE)
{
    for (int i = 0; i < ARRAY_SIZE - 1; i++)
        if (array[i] > array[i + 1])
            return false;
    return true;
}

int compare(const void *voidA, const void *voidB)
{
    int *intA = (int *)(voidA);
    int *intB = (int *)(voidB);
    return *intA - *intB;
}

void printArray(int array[], int ARRAY_SIZE)
{
    int i, size = ARRAY_SIZE - 1;
    cout << "Array: ";
    for (i = 0; i < size; i++)
        cout << array[i] << ", ";
    cout << array[i] << "\n";
}

int main()
{
    int tenIntegerArray[10] = {4, 5, 9, 12, -4, 0, -57, 30987, -287, 1};

    // Function should confirm that the array is not sorted
    printArray(tenIntegerArray, 10);
    if (!isSorted(tenIntegerArray, 10))
        cout << "The array is not sorted\n";

    // Sort the array
    qsort(tenIntegerArray, 10, sizeof(int), compare);
    cout << "\n";

    // Function should confirm that the array has now been sorted
    printArray(tenIntegerArray, 10);
    if (isSorted(tenIntegerArray, 10))
        cout << "The array is now sorted\n";
    return 0;
}
