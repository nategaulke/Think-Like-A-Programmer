#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Building from previous exercise, replace characterAt
// with overloaded [] operator

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
    stringClass test("test");
    int i, strlen = test.getLength();
    cout << "Original char array: " << test.getArrayString() << "\n\n";

    // Demonstrating overloaded [] operator
    cout << "Printing each character individually:\n";
    for (int i = 0; i < strlen; i++)
    {
        cout << test[i];
    }
    cout << "\n\n";

    // Showing that invalid positions are just NULL
    cout << "Invalid Indexes\n";
    cout << "test[-1]: " << test[-1];
    cout << " test[5]: " << test[5] << "\n";
    return 0;
}
