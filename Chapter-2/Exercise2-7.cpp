#include <iostream>
using std::cin;
using std::cout;

/*
  Convert from decimal, binary, or hexadecimal to decimal, binary, or hexadecimal
  Input must be valid
*/

int main()
{
    int option, number, fromBase, toBase, base10 = 0, conversion, power = 1, position = 0;
    char digitChar;
    char output[32];
    cout << "Enter the base you are converting from and the base you want to convert to:\n";
    cin >> fromBase;
    cin >> toBase;
    digitChar = cin.get();
    cout << "Enter the number you would like to convert(only use lowercase for letters): ";
    digitChar = cin.get();
    if (digitChar <= '9')
        number = (digitChar - '0');
    else
        number = (digitChar - 'a');

    // Convert from base to base 10
    while (digitChar != 10)
    {
        base10 *= fromBase;
        base10 += number;
        digitChar = cin.get();
        if (digitChar <= '9')
            number = (digitChar - '0');
        else
            number = (digitChar - 'a' + 10);
    }

    // Convert from base 10 to base requested
    while (base10 != 0)
    {
        conversion = base10 % toBase;
        if (conversion < 10)
            output[position] = conversion + '0';
        else
            output[position] = conversion - 10 + 'a';
        base10 /= toBase;
        position++;
        power *= 10;
    }

    cout << "The conversion is ";
    for (int i = position - 1; i >= 0; i--)
    {
        cout << output[i];
    }
    cout << "\n";
    cout << "Have a good day!\n";
    return 0;
}
