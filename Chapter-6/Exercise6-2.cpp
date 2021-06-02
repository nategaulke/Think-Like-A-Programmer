#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Write a boolean function to find whether a binary number has odd parity
// (odd number of 1 bits), first iteratively then recursively

void printArray(int array[], int size)
{
    cout << "Binary String: ";
    for (int i = 0; i < size; i++)
    {
        if (i + 1 == size)
        {
            cout << array[i] << "\n";
            break;
        }
        else
        {
            cout << array[i];
        }
    }
}

bool determineOddParityIterative(int array[], int size)
{
    int i, oneCount = 0;
    for (i = 0; i < size; i++)
    {
        if (array[i] == 1)
            oneCount++;
    }
    if (oneCount % 2 == 0)
        return false;
    else
        return true;
}

bool determineOddParityRecursive(int array[], int size)
{
    // Simplest case
    if (size == 0)
        return false;

    // Determine if rest of array has odd parity
    bool odd = determineOddParityRecursive(array, size - 1);

    // Find out if current number is 1
    bool curr = (array[size - 1] == 1);

    // If the rest of array has odd parity, then current digit must
    // be 0 to maintain "true" for odd parity
    if (odd)
    {
        if (curr)
            return false;
        else
            return true;
    }
    // If the rest of the array does not have odd parity, then current
    // digit must be 1 for their to be odd parity
    else
    {
        if (curr)
            return true;
        else
            return false;
    }
}

int main()
{
    srand((unsigned)time(0));
    const int ARRAY_SIZE = 8;

    int *array = new int[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        // Randomly generating 0s & 1s
        array[i] = rand() % 2;
    }

    printArray(array, ARRAY_SIZE);
    cout << "\n";

    bool iterativeAnswer = determineOddParityIterative(array, ARRAY_SIZE);
    cout << "The iterative answer is " << iterativeAnswer << "\n";
    bool recursiveAnswer = determineOddParityRecursive(array, ARRAY_SIZE);
    cout << "The recursive answer is " << recursiveAnswer << "\n";

    if (iterativeAnswer == recursiveAnswer)
        cout << "Hooray! Our answers match.\n";

    delete[] array;
    return 0;
}
