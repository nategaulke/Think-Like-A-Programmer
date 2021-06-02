#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Write a function that returns the number of times target
// appears in an array; First solve iteratively then recursively

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

int countTargetIterative(int array[], int size, int target)
{
    int i, targetCount = 0;
    for (i = 0; i < size; i++)
    {
        if (array[i] == target)
            targetCount++;
    }
    return targetCount;
}

int countTargetRecursive(int array[], int size, int target)
{
    // Simplest case
    if (size == 0)
        return 0;

    // Count of instances of target in rest of array
    int targetCount = countTargetRecursive(array, size - 1, target);

    // If current index is instance of target, add 1 to total
    if (array[size - 1] == target)
        targetCount++;

    return targetCount;
}

int main()
{
    srand((unsigned)time(0));
    const int ARRAY_SIZE = 20;
    const int TARGET = 7;
    int iterativeCount, recursiveCount;

    int *array = new int[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        // Generating random numbers from 1 to 10
        array[i] = rand() % 10 + 1;
    }

    printArray(array, ARRAY_SIZE);
    cout << "\n";

    iterativeCount = countTargetIterative(array, ARRAY_SIZE, TARGET);
    cout << "Occurences of " << TARGET << "(Iterative): " << iterativeCount << "\n";
    recursiveCount = countTargetRecursive(array, ARRAY_SIZE, TARGET);
    cout << "Occurences of " << TARGET << "(Recursive): " << recursiveCount << "\n";

    if (iterativeCount == recursiveCount)
        cout << "Hooray! The iterative and recursive function returned the same result\n";

    delete[] array;
    return 0;
}