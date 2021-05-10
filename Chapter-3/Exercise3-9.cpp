#include <iostream>
using namespace std;

// Find the averages and medians of sales agent
// skipping months they were not working (marked with -1)
// Array adapted from the example sales agent array (p. 71, Fourth Printing)

// Compare function for qsort
int compare(const void *voidA, const void *voidB)
{
    int *intA = (int *)(voidA);
    int *intB = (int *)(voidB);
    return *intA - *intB;
}

// Finds median in a sorted array
int arrayMedian(int intArray[], int size)
{
    int median, mid, start = 0;

    // Size readjusted to months worked by agent
    while (intArray[start] == -1)
    {
        size--;
        start++;
    }

    mid = size / 2;

    // If there is an even amount of data, must find average of two midpoints
    if (size % 2 == 0)
        median = (intArray[start + mid] + intArray[start + mid - 1]) / 2;
    else
        median = intArray[start + mid];
    return median;
}

// Finds average of array
double arrayAverage(int intArray[], int size)
{
    int average = 0, start = 0, i;
    double numData = size;

    // Start adjusted to first real sale and
    // number of months worked readjusted
    while (intArray[start] == -1)
    {
        numData--;
        start++;
    }

    for (i = start; i < size; i++)
    {
        average += intArray[i];
    }

    average /= numData;

    return average;
}

// Used for testing
void printArray(int array[], int ARRAY_SIZE)
{
    int i, size = ARRAY_SIZE - 1;
    cout << "Agent: ";
    for (i = 0; i < size; i++)
        if (array[i] != -1)
            cout << array[i] << ", ";

    cout << array[i] << "\n";
}

int main()
{
    const int NUM_AGENTS = 3;
    const int NUM_MONTHS = 12;
    int greatestMedian, median, **copySales;
    double greatestAverage, average;
    int sales[NUM_AGENTS][NUM_MONTHS] = {
        {-1, -1, -1, -1, 328, 2653, 387, 3754, 387587, 2873, 276, 32},
        {-1, 5456, 3983, 6464, 9957, 4785, 3875, 3838, 4959, 1122, -1, -1},
        {23, 55, 67, 99, 265, 376, 232, 223, 4546, 564, 4544, -1}};

    // Copying sales array to keep original sales data associated with correct month
    copySales = new int *[NUM_AGENTS];
    for (int agent = 0; agent < NUM_AGENTS; agent++)
        copySales[agent] = new int[NUM_MONTHS];
    for (int agent = 0; agent < NUM_AGENTS; agent++)
        for (int month = 0; month < NUM_MONTHS; month++)
            copySales[agent][month] = sales[agent][month];

    // Initialize greatest values of median & average
    qsort(copySales[0], NUM_MONTHS, sizeof(int), compare);
    greatestMedian = arrayMedian(copySales[0], NUM_MONTHS);
    greatestAverage = arrayAverage(copySales[0], NUM_MONTHS);

    cout << "Agent 1\tMedian: " << greatestMedian << "\tAverage: " << greatestAverage << "\n";

    // Find & print median & average of every agent excluding months they did not work
    // Determine the greatest median/average as we go through the list
    for (int agent = 1; agent < NUM_AGENTS; agent++)
    {
        qsort(copySales[agent], NUM_MONTHS, sizeof(int), compare);
        median = arrayMedian(copySales[agent], NUM_MONTHS);
        average = arrayAverage(copySales[agent], NUM_MONTHS);

        cout << "Agent " << agent + 1 << "\tMedian: " << median << "\tAverage: " << average << "\n";

        if (median > greatestMedian)
            greatestMedian = median;
        if (average > greatestAverage)
            greatestAverage = average;
    }

    cout << "Highest median this year: " << greatestMedian << "\n";
    cout << "Highest average this year: " << greatestAverage << "\n";

    // Free allocated memory
    for (int i = 0; i < NUM_AGENTS; i++)
        delete[] copySales[i];
    delete[] copySales;

    return 0;
}