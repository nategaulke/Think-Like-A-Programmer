#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Building from previous exercises, create remove function
// that takes a start and end position and removes those
// characters from char array

class stringClass
{
private:
    typedef char *arrayString;

public:
    stringClass()
    {
        s = new char[1];
        s[0] = '\0';
        setLength(0);
    }

    stringClass(string str)
    {
        s = new char[str.length() + 1];
        strcpy(s, str.c_str());
        setLength(str.length());
    }

    ~stringClass()
    {
        delete[] s;
    }

    stringClass &operator=(stringClass &rhs)
    {
        // Don't use same class address; delete lhs, copy rhs to lhs
        if (this != &rhs)
        {
            delete[] s;
            s = copy(rhs.getArrayString(), rhs.getLength());
            setLength(rhs.getLength());
        }
        return *this;
    }

    // Overloaded operator that returns character at that position
    // in char array s
    char operator[](int position)
    {
        if (position >= 0 && position < length)
            return s[position];
        else
            return '\0';
    }

    int getLength()
    {
        return length;
    }

    void setLength(int length)
    {
        if (length >= 0)
            this->length = length;
    }

    // Also works like a "toString" method
    arrayString getArrayString()
    {
        return s;
    }

    void append(char c)
    {
        int oldLength = length;
        arrayString newS = new char[oldLength + 2];

        // Copy previous contents then add new character and null character
        for (int i = 0; i < oldLength; i++)
        {
            newS[i] = s[i];
        }
        newS[oldLength] = c;
        newS[oldLength + 1] = '\0';

        // Set the new values
        setLength(oldLength + 1);
        delete[] s;
        s = newS;
    }

    void concatenate(stringClass &s2)
    {
        int i;
        int s_OldLength = length;
        int s2_Length = s2.getLength();
        int s_NewLength = s_OldLength + s2_Length;
        arrayString newS = new char[s_NewLength + 1];

        // Copy values of current char array into new one
        for (i = 0; i < s_OldLength; i++)
        {
            newS[i] = s[i];
        }

        // Copy values of second char array into new one
        arrayString s2Array = s2.getArrayString();
        for (i = 0; i < s2_Length; i++)
        {
            newS[s_OldLength + i] = s2Array[i];
        }
        newS[s_NewLength] = '\0';
        delete[] s;

        // Set new values
        setLength(s_NewLength);
        s = newS;
    }

    // Only accepts valid starting indexes
    void remove(int start, int len)
    {
        if (start < 0 || start >= length)
            return;
        int end = start + len, i, s_NewLength, index = 0;
        arrayString newS;

        //  Allocate only necessary space depending on where endpoint is
        if (end <= length)
        {
            newS = new char[length - len + 1];
            s_NewLength = length - len;
        }
        else
        {
            newS = new char[start + 1];
            s_NewLength = start;
        }

        // Assign indices before removed portion
        for (i = 0; i < start; i++)
        {
            newS[index] = s[i];
            index++;
        }

        // Assign indices after removed portion
        for (i = end; i < length; i++)
        {
            newS[index] = s[i];
            index++;
        }
        newS[s_NewLength] = '\0';

        // Set the string up
        delete[] s;
        setLength(s_NewLength);
        s = newS;
    }

private:
    arrayString s;
    int length;

    // Copies char array and returns char array
    arrayString copy(arrayString s2, int s2_length)
    {
        int i;
        arrayString newS = new char[s2_length + 1];
        for (i = 0; i < s2_length; i++)
        {
            newS[i] = s2[i];
        }
        newS[s2_length] = '\0';
        return newS;
    }
};

int main()
{
    // Construct
    stringClass test1("testbed");
    stringClass test2("testbed");
    stringClass test3("testbed");
    stringClass test4("testbed");
    cout << "Original char array: " << test1.getArrayString() << " Length: " << test1.getLength() << "\n\n";

    // Deleting from beginning
    test1.remove(0, 4);
    cout << "Deleting from index 0, 4 characters: " << test1.getArrayString() << "\tLength: " << test1.getLength() << "\n";

    // Deleting from end
    test2.remove(4, 3);
    cout << "Deleting from index 4, 3 characters: " << test2.getArrayString() << "\tLength: " << test2.getLength() << "\n";

    // Deleting longer than the length of the string
    test3.remove(1, 20);
    cout << "Deleting from index 1, 20 characters: " << test3.getArrayString() << "\t\tLength: " << test3.getLength() << "\n";

    // Deleting in the middle
    test4.remove(1, 4);
    cout << "Deleting from index 1, 4 characters: " << test4.getArrayString() << "\tLength: " << test4.getLength() << "\n";

    return 0;
}
