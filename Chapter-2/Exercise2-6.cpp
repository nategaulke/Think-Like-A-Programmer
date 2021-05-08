#include <iostream>
using std::cin;
using std::cout;

/*
  Convert from binary to decimal, decimal to binary
  (will not cheat with format specifiers)
*/

int main()
{
    int option, binary = 0, decimal = 0, power = 1;
    cout << "Press 1 to calculate binary to decimal or 2 to calculate decimal to binary: ";
    cin >> option;
    if (option == 1)
    {
        cout << "Enter binary number: ";
        cin >> binary;
        while (binary != 0)
        {
            decimal += (binary % 10) * power;
            binary /= 10;
            power *= 2;
        }
        cout << "The decimal conversion is " << decimal << "\n";
    }
    else if (option == 2)
    {
        cout << "Enter decimal number: ";
        cin >> decimal;
        while (decimal != 0)
        {
            binary += (decimal % 2) * power;
            decimal /= 2;
            power *= 10;
        }
        cout << "The binary conversion is " << binary << "\n";
    }
    else
    {
        cout << "This is an invalid option :(";
    }
    cout << "Have a good day!\n";
    return 0;
}
