#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Create a class for variable length string functions
// Include append, concatenate, and characterAt (adapted from Chapter 4)
// Include constructor, destructor, overloaded assignment operator

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

    char characterAt(int position)
    {
        if (position >= 0 && position < length)
            return s[position];
        else
            return '\0';
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
    stringClass test("tes");
    cout << "Original char array: " << test.getArrayString() << "\n\n";

    // CharacterAt
    cout << "CharacterAt\n";
    cout << "The character at index 1 is: " << test.characterAt(1) << "\n\n";

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
    cout << "\tLength 1: " << test.getLength() << " Length 2: " << test2.getLength() << "\n";
    return 0;
}
