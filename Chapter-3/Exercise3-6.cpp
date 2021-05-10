#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// Use a randomly generated cipher to encrpyt then decrypt a text

int indexFind(char value, char array[], int ARRAY_SIZE)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
        if (array[i] == value)
            return i;

    // If the letter is not in the array, return -1
    return -1;
}

// prints out vector contents
void print(vector<char> text)
{
    for (int i = 0; i < text.size(); i++)
        cout << text[i];
    cout << "\n";
}

// Uses rand() to create the cipher
void initCipher(char cipher[], int SIZE)
{
    int random;
    char randLetter;
    char alphabet[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                           'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                           'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for (int i = 0; i < SIZE; i++)
    {
        random = rand() % SIZE;
        // Keep generating new number/ltter while the result is same position
        // or the letter has already been used
        while (random == i || indexFind(random + 'A', alphabet, SIZE) == -1)
            random = rand() % SIZE;

        randLetter = random + 'A';
        cipher[i] = randLetter;
        alphabet[random] = '!';
    }
}

int main()
{
    char charDigit, charCipher;
    const int NUM_LETTERS = 26;
    vector<char> encrypted;
    char cipher[NUM_LETTERS];

    // srand ensures that the same numbers aren't "randomly" generated
    srand((unsigned)time(0));

    initCipher(cipher, NUM_LETTERS);

    cout << "Enter the plaintext: ";
    charDigit = cin.get();
    while (charDigit != '\n')
    {
        // If part of uppercase alphabet, encrypt; Otherwise, just push with no change
        if (charDigit >= 'A' && charDigit <= 'Z')
        {
            charCipher = cipher[charDigit - 'A'];
            encrypted.push_back(charCipher);
        }
        else
            encrypted.push_back(charDigit);

        charDigit = cin.get();
    }

    cout << "Ciphertext: ";
    print(encrypted);

    cout << "Plaintext: ";
    for (int i = 0; i < encrypted.size(); i++)
    {
        // If part of uppercase alphabet, decrypt; Otherwise, just output with no change
        if (encrypted[i] >= 'A' && encrypted[i] <= 'Z')
        {
            charCipher = 'A' + indexFind(encrypted[i], cipher, NUM_LETTERS);
            cout << charCipher;
        }
        else
            cout << encrypted[i];
    }
    cout << "\n";
    return 0;
}