#include <iostream>
using namespace std;

// Modify append, concatenate, and characterAt (from Chapter 4) for arrayStrings where
// index 0 indicates the length of the string instead of using null character

typedef char *arrayString;

// Won't modify characterAt, assuming user enters valid position to keep quick runtime
char characterAt(arrayString s, int position)
{
    return s[position];
}

void append(arrayString &s, char c)
{
    int oldLength = s[0];
    arrayString newS = new char[oldLength + 2];
    for (int i = 1; i <= oldLength; i++)
    {
        newS[i] = s[i];
    }
    newS[oldLength + 1] = c;
    newS[0] = oldLength + 1;
    delete[] s;
    s = newS;
}

void concatenate(arrayString &s1, arrayString s2)
{
    int s1_OldLength = s1[0];
    int s2_Length = s2[0];
    int s1_NewLength = s1_OldLength + s2_Length;
    arrayString newS = new char[s1_NewLength + 1];
    newS[0] = s1_NewLength;
    for (int i = 1; i <= s1_OldLength; i++)
    {
        newS[i] = s1[i];
    }
    for (int i = 1; i <= s2_Length; i++)
    {
        newS[s1_OldLength + i] = s2[i];
    }
    delete[] s1;
    s1 = newS;
}

void output(arrayString out)
{
    int length = out[0];
    for (int i = 1; i <= length; i++)
    {
        cout << out[i];
    }
    cout << "\n";
}

void characterTester()
{
    cout << "Character At Third Index:\n";
    arrayString a = new char[5];
    a[0] = 4;
    a[1] = 't';
    a[2] = 'e';
    a[3] = 's';
    a[4] = 't';
    char c = characterAt(a, 3);
    delete[] a;
    cout << c << "\n\n";
}

void appendTester()
{
    cout << "Append:\n";
    arrayString a = new char[5];
    a[0] = 4;
    a[1] = 't';
    a[2] = 'e';
    a[3] = 's';
    a[4] = 't';
    output(a);
    append(a, '!');
    output(a);
    delete[] a;
    cout << "\n";
}

void concatenateTester()
{
    cout << "Concatenate:\n";
    arrayString a = new char[5];
    a[0] = 4;
    a[1] = 't';
    a[2] = 'e';
    a[3] = 's';
    a[4] = 't';
    arrayString b = new char[4];
    b[0] = 3;
    b[1] = 'b';
    b[2] = 'e';
    b[3] = 'd';
    output(a);
    output(b);
    concatenate(a, b);
    output(a);
    output(b);
    delete[] a;
    delete[] b;
}

int main()
{
    characterTester();
    appendTester();
    concatenateTester();
    return 0;
}
