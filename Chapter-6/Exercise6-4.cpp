#include <cstdlib>
#include <ctime>
#include <iostream>
#include <climits>
using namespace std;

// Write a recursive function for an array
// that is trivial to solve iteratively

// My example: Creating a finding max number function

void printArray(int array[], int size)
{
    cout << "Array: ";
    for (int i = 0; i < size; i++)
    {
        if (i + 1 == size)
        {
            cout << array[i] << "\n";
            break;
        }
        else
        {
            cout << array[i] << ", ";
        }
    }
}

int findMaxIterative(int array[], int size)
{
    // No number can be smaller than INT_MIN in computer
    int i, max = INT_MIN;

    for (i = 0; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }

    return max;
}

int findMaxRecursive(int array[], int size)
{
    // Simplest case, no number can be smaller than INT_MIn in computer
    if (size == 0)
        return INT_MIN;

    // Find max number in rest of array
    int max = findMaxRecursive(array, size - 1);

    // If current number is greater then the max of rest of array
    // Set the new max number
    if (array[size - 1] > max)
        max = array[size - 1];

    return max;
}

int main()
{
    srand((unsigned)time(0));
    const int ARRAY_SIZE = 10;
    const int TARGET = 7;
    int iterativeMax, recursiveMax;

    int *array = new int[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        // Generating random numbers from 1 to INT_MAX
        array[i] = rand() % 100 + 1;
    }

    printArray(array, ARRAY_SIZE);
    cout << "\n";

    iterativeMax = findMaxIterative(array, ARRAY_SIZE);
    cout << "Greatest number in array (iterative): " << iterativeMax << "\n";
    recursiveMax = findMaxRecursive(array, ARRAY_SIZE);
    cout << "Greatest number in array (recursive): " << recursiveMax << "\n";

    if (iterativeMax == recursiveMax)
        cout << "Hooray! The iterative and recursive function returned the same result\n";

    delete[] array;
    return 0;
}