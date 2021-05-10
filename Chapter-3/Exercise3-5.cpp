#include <iostream>
using namespace std;

// Building on Exercise 3-4, decrypt ciphertext back to plaintext

// Index of the encrypted letter is the same index of decrypted letter
int indexFind(char value, const char array[], int ARRAY_SIZE)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
        if (array[i] == value)
            return i;

    // If the letter is not in the array, return -1
    // (impossible to happen in this case)
    return -1;
}

int main()
{
    char charDigit, charCipher;
    const int NUM_LETTERS = 26;
    const char cipher[NUM_LETTERS] = {'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                                      'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                                      'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'A',
                                      'B', 'C'};
    cout << "Enter the ciphertext: ";
    charDigit = cin.get();
    cout << "Plaintext: ";
    while (charDigit != '\n')
    {
        // If part of uppercase alphabet, decrypt; Otherwise, just output with no change
        if (charDigit >= 'A' && charDigit <= 'Z')
        {
            charCipher = 'A' + indexFind(charDigit, cipher, NUM_LETTERS);
            cout << charCipher;
        }
        else
            cout << charDigit;

        charDigit = cin.get();
    }
    cout << "\n";
    return 0;
}