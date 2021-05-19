#include <iostream>
using namespace std;

// Create a function substring (parameters: arrayString, starting position, length of characters)
// Returns pointer to new dynamic arrayString of the substring
// When calculating starting position start index with 1 not 0
// Assumes valid starting position but will check if and readjust if length is not valid

typedef char *arrayString;

int length(arrayString s)
{
    int count = 0;
    while (s[count] != '\0')
    {
        count++;
    }
    return count;
}

arrayString substring(arrayString &string, int start, int len)
{
    arrayString newS;
    int end = start + len - 1, strlen = length(string), i, index = 0;

    // Allocates only space needed, not extraneous space if string is smaller
    if (end <= strlen)
        newS = new char[len + 1];
    else
        newS = new char[strlen - start + 2];
    for (i = start - 1; i < end && i < strlen; i++)
    {
        newS[index] = string[i];
        index++;
    }
    newS[index] = '\0';
    return newS;
}

int main()
{
    arrayString a = new char[8];
    arrayString b;
    a[0] = 't';
    a[1] = 'e';
    a[2] = 's';
    a[3] = 't';
    a[4] = 'i';
    a[5] = 'n';
    a[6] = 'g';
    a[7] = '\0';
    cout << "Original String: " << a << "\n";
    b = substring(a, 1, 4);
    cout << "Original String & Substring: " << a << "\t" << b << "\n";
    delete[] a;
    delete[] b;
    return 0;
}
