#include <iostream>
using namespace std;

// Using a substitution cipher & const array, read a message, output ciphertext (only uppercase letters)

int main()
{
    char charDigit, charCipher;
    const int NUM_LETTERS = 26;
    const char cipher[NUM_LETTERS] = {'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                                      'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                                      'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A',
                                      'B', 'C'};
    cout << "Enter the plaintext: ";
    charDigit = cin.get();
    cout << "Ciphertext: ";
    while (charDigit != '\n')
    {
        // If part of uppercase alphabet, encrypt; Otherwise, just output with no change
        if (charDigit >= 'A' && charDigit <= 'Z')
        {
            charCipher = cipher[charDigit - 'A'];
            cout << charCipher;
        }
        else
            cout << charDigit;

        charDigit = cin.get();
    }
    cout << "\n";
    return 0;
}