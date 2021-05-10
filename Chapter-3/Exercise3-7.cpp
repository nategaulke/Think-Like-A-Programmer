#include <iostream>
using namespace std;

// Find the mode in an array of integers

// Simple swap of two elements in array
void swap(int array[], int a, int b)
{
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

// Modified from book example (p. 60, Fourth Printing) using knowledge from Computer Science I
void insertionSort(int array[], int size)
{
    int i, j, curr;
    for (i = 0; i < size; i++)
    {
        for (j = i; j > 0 && array[j] < array[j - 1]; j--)
        {
            swap(array, j, j - 1);
        }
    }
}

void printArray(int array[], int ARRAY_SIZE)
{
    int i, size = ARRAY_SIZE - 1;
    for (i = 0; i < size; i++)
        cout << array[i] << ", ";
    cout << array[i] << "\n";
}

int main()
{
    int i = 0, frequency, mostFrequent, mode;
    const int ARRAY_SIZE = 20;
    int array[ARRAY_SIZE] = {80, 71, 60, 80, 95, 91, 92, 85, 97, 40,
                             80, 95, 20, 83, 68, 71, 89, 86, 44, 100};

    insertionSort(array, ARRAY_SIZE);

    cout << "Sorted Array: ";
    printArray(array, ARRAY_SIZE);

    // Once we sort the array, all common elements will be place together
    // Thus we can count their frequency together and compare to find the mode
    while (i < ARRAY_SIZE - 1)
    {
        frequency = 1;
        while (array[i] == array[i + 1] && i < ARRAY_SIZE - 1)
        {
            frequency++;
            i++;
        }

        // If there are numbers that appear with the same frequency, returns the greatest value mode
        if (frequency >= mostFrequent)
        {
            mostFrequent = frequency;
            mode = array[i];
        }
        i++;
    }

    cout << "The mode of the array is: " << mode << "\n";
    return 0;
}