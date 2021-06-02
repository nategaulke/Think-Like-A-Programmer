#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Write a function to find the sum of all the positive numbers in an array
// First iteratively then recursively

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

int findPositiveSumIterative(int array[], int size)
{
    int i, sum = 0;
    for (i = 0; i < size; i++)
    {
        if (array[i] > 0)
            sum += array[i];
    }
    return sum;
}

int findPositiveSumRecursive(int array[], int size)
{
    // Simplest case
    if (size == 0)
        return 0;

    // Find sum of the rest of the array
    int sum = findPositiveSumRecursive(array, size - 1);

    // If current number is positive, add to sum
    if (array[size - 1] > 0)
        sum += array[size - 1];

    return sum;
}

int main()
{
    srand((unsigned)time(0));
    const int ARRAY_SIZE = 20;
    int iterativeSum, recursiveSum;

    int *array = new int[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        // Generating random numbers from -20 to 20
        array[i] = rand() % 41 - 20;
    }

    printArray(array, ARRAY_SIZE);
    cout << "\n";

    iterativeSum = findPositiveSumIterative(array, ARRAY_SIZE);
    cout << "Iterative Sum: " << iterativeSum << "\n";
    recursiveSum = findPositiveSumRecursive(array, ARRAY_SIZE);
    cout << "Resursive Sum: " << recursiveSum << "\n";

    if (iterativeSum == recursiveSum)
        cout << "Hooray! The iterative and recursive function returned the same result\n";

    delete[] array;
    return 0;
}
