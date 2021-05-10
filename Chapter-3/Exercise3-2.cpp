#include <iostream>
using namespace std;

// Find the agent with the highest median sales
// Using the example sales agent array (p. 71, Fourth Printing)

// Compare function for qsort
int compare(const void *voidA, const void *voidB)
{
    int *intA = (int *)(voidA);
    int *intB = (int *)(voidB);
    return *intA - *intB;
}

int arrayMedian(int intArray[], int ARRAY_SIZE)
{
    int median;
    int mid = ARRAY_SIZE / 2;

    // Sort array to easily find the value(s) in the middle
    qsort(intArray, ARRAY_SIZE, sizeof(int), compare);

    // If there is an even amount of data, must find average of two midpoints
    if (ARRAY_SIZE % 2 == 0)
        median = (intArray[mid] + intArray[mid - 1]) / 2;
    else
        median = intArray[mid];
    return median;
}

int main()
{
    const int NUM_AGENTS = 3;
    const int NUM_MONTHS = 12;
    int greatestMedian, median, **copySales;
    int sales[NUM_AGENTS][NUM_MONTHS] = {
        {1856, 498, 30924, 87478, 328, 2653, 387, 3754, 387587, 2873, 276, 32},
        {5865, 5456, 3983, 6464, 9957, 4785, 3875, 3838, 4959, 1122, 7766, 2534},
        {23, 55, 67, 99, 265, 376, 232, 223, 4546, 564, 4544, 3434}};

    // Copying sales array to keep original sales data associated with correct month
    copySales = new int *[NUM_AGENTS];
    for (int agent = 0; agent < NUM_AGENTS; agent++)
        copySales[agent] = new int[NUM_MONTHS];
    for (int agent = 0; agent < NUM_AGENTS; agent++)
        for (int month = 0; month < NUM_MONTHS; month++)
            copySales[agent][month] = sales[agent][month];

    greatestMedian = arrayMedian(copySales[0], NUM_MONTHS);
    cout << "The median of agent 1 is: " << greatestMedian << "\n";
    for (int agent = 1; agent < NUM_AGENTS; agent++)
    {
        median = arrayMedian(copySales[agent], NUM_MONTHS);
        cout << "The median of agent " << agent + 1 << " is: " << median << "\n";
        if (median > greatestMedian)
            greatestMedian = median;
    }

    cout << "Highest median this year: " << greatestMedian << "\n";

    // Free allocated memory
    for (int i = 0; i < NUM_AGENTS; i++)
        delete[] copySales[i];
    delete[] copySales;

    return 0;
}
