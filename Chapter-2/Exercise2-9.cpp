#include <iostream>
using std::cin;
using std::cout;

/*
    Take a line of text, give the the number of words in the line, the length of the longest word, the number of vowels in the word with the most vowels
*/

int main()
{
    char pointer;
    int words = 0, length = 0, bigWord = 0, vowels = 0, mostVowels = 0;
    cout << "Begin entering the line of text for analysis(only lowercase, no special characters): ";
    pointer = cin.get();
    while (pointer != '\n')
    {
        // If a space is recorded
        if (pointer == 32)
        {
            length = 0;
            vowels = 0;
            words++;
        }
        else
        {
            length++;
            if (pointer == 'a' || pointer == 'e' || pointer == 'i' || pointer == 'o' || pointer == 'u')
                vowels++;
        }

        if (length > bigWord)
            bigWord = length;

        if (vowels > mostVowels)
            mostVowels = vowels;
        pointer = cin.get();
    }
    words++;
    cout << "The number of words in the line is: " << words << "\n";
    cout << "The longest word is " << bigWord << "\n";
    cout << "There are " << mostVowels << "vowels in the word with the most vowels\n";

    return 0;
}
