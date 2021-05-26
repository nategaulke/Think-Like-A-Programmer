#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Review string class and considering refactoring

// Expanded the use of the private copy method
// Also assignment overload with a string

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
            int rhs_length = rhs.getLength();
            s = new char[rhs_length + 1];
            copy(s, rhs.getArrayString(), 0, rhs_length);
            s[rhs_length] = '\0';
            setLength(rhs.getLength());
        }
        return *this;
    }

    stringClass &operator=(const string &rhs)
    {
        if (getArrayString() != rhs)
        {
            delete[] s;
            s = new char[rhs.length() + 1];
            strcpy(s, rhs.c_str());
            setLength(rhs.length());
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
        copy(newS, s, 0, oldLength);
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
    void copy(arrayString &str1, arrayString str2, int start, int end)
    {
        for (int i = start; i < end; i++)
        {
            str1[i] = str2[i];
        }
    }
};

int main()
{
    // Construct
    stringClass test;
    test = "tes";

    cout << "Original char array: " << test.getArrayString() << "\n\n";

    // CharacterAt
    cout << "CharacterAt\n";
    cout << "The character at index 1 is: " << test[1] << "\n\n";

    // Append
    cout << "Append\n";
    cout << "Before: " << test.getArrayString() << "\tLength is: " << test.getLength() << "\n";
    test.append('t');
    cout << "After: " << test.getArrayString() << "\tLength is: " << test.getLength() << "\n\n";

    // Construct new stringClass
    stringClass test2("bed");

    // Concatenate
    cout << "Concatenate\n";
    cout << "Before: " << test.getArrayString() << " " << test2.getArrayString();
    cout << "\tLength 1: " << test.getLength() << " Length 2: " << test2.getLength() << "\n";
    test.concatenate(test2);
    cout << "After: " << test.getArrayString() << " " << test2.getArrayString();
    cout << "\tLength 1: " << test.getLength() << " Length 2: " << test2.getLength() << "\n\n";

    // Overloaded Assignment Operator
    cout << "Overloaded Assignment Operator\n";
    cout << "Before: " << test.getArrayString() << " " << test2.getArrayString();
    cout << "\tLength 1: " << test.getLength() << " Length 2: " << test2.getLength() << "\n";
    test2 = test;
    cout << "After: " << test.getArrayString() << " " << test2.getArrayString();
    cout << "\tLength 1: " << test.getLength() << " Length 2: " << test2.getLength() << "\n\n";

    // Removal operation
    cout << "Removing Characters From Array\n";
    cout << "Before: " << test.getArrayString() << "\tLength is: " << test.getLength() << "\n";
    cout << "Deleting 4 characters, starting at index 1\n";
    test.remove(1, 4);
    cout << "After: " << test.getArrayString() << "\tLength is: " << test.getLength() << "\n";
    return 0;
}
