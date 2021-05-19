#include <iostream>
#include <cstring>
using namespace std;

// replaceString: Replaces instances of "target" in "source" with "replaceText"
// Using strcpy instead of manually inserting each letter

typedef char *arrayString;

// Simple length function derived from example in Chapter 4
int length(arrayString s)
{
    int count = 0;
    while (s[count] != '\0')
    {
        count++;
    }
    return count;
}

void replaceString(arrayString &source, arrayString &target, arrayString &replaceText)
{
    int i, sourceIndex, targetIndex, count = 0, newLen, originalSource = 0, replaceIndex;
    int sourceLen = length(source), targetLen = length(target), replaceLen = length(replaceText);

    // Loop through to find instances of target substring
    for (i = 0; i < sourceLen; i++)
    {
        sourceIndex = i;
        targetIndex = 0;
        while (source[sourceIndex++] == target[targetIndex])
        {
            targetIndex++;

            // If equal, then match is found, added, and letters are skipped
            // To avoid accidental double count of target
            if (targetIndex == targetLen)
            {
                count++;
                i += targetLen - 1;
                break;
            }
        }
    }

    // Allocate space for source - (instances of target) + (new instances of replaceText)
    newLen = sourceLen - (targetLen * count) + (replaceLen * count);
    arrayString temp = new char[newLen + 1];

    // Copy letters into temp
    for (i = 0; i < newLen; i++)
    {
        temp[i] = source[originalSource];
        sourceIndex = originalSource;
        targetIndex = 0;

        // Copy of original Source is used to determine if target is up ahead
        while (source[sourceIndex++] == target[targetIndex])
        {
            targetIndex++;
            if (targetIndex == targetLen)
            {
                // If target is found, copy replaceText into temp, incrementing temp's index
                for (replaceIndex = 0; replaceIndex < replaceLen; replaceIndex++)
                {
                    temp[i] = replaceText[replaceIndex];
                    i++;
                }
                // skip over the target in the original source
                originalSource += targetLen - 1;
                i--;
                break;
            }
        }
        originalSource++;
    }

    // Delete original source and set the new address to temp
    temp[newLen] = '\0';
    delete[] source;
    source = temp;
}

int main()
{
    string a("abcdabee");
    string b("ab");
    string c("xyz");
    arrayString source = new char[a.length() + 1];
    arrayString target = new char[b.length() + 1];
    arrayString replaceText = new char[c.length() + 1];
    strcpy(source, a.c_str());
    strcpy(target, b.c_str());
    strcpy(replaceText, c.c_str());

    cout << "Before Replacement of Target: " << source << " " << target << " " << replaceText << "\n";
    replaceString(source, target, replaceText);
    cout << "After Replacement of Target: " << source << " " << target << " " << replaceText << "\n";

    delete[] source;
    delete[] target;
    delete[] replaceText;
    return 0;
}