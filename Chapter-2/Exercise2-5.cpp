#include <iostream>
using std::cin;
using std::cout;

/*
  Calculate Check digit for 13 digit ISBN System
  1) Take first 12 digits, multiply odd digits by 1 (if starting at index 1)
     and even digits by 3.
  2) Add the digits together
  3) mod result by 10
  4) Take that new result. If it is 0, then append it to ISBN. Otherwise append ISBN with (10 - result)
*/

int main()
{
  int option, digit, numCount = 0, isbn = 0, check, lastDigit;
  // The book processed each digit one by one for one of the examples and
  // for consistency I will also each digit one by one
  cout << "Press 1 to calculate a check digit or 2 to check a check digit for accuracy: ";
  cin >> option;
  cout << "Begin entering 12 digits: ";
  while (numCount < 12)
  {
    cin >> digit;
    if (numCount % 2 == 0)
      isbn += digit;
    else
      isbn += 3 * digit;
    numCount++;
  }
  check = isbn % 10;
  if (check != 0)
    check = 10 - check;
  if (option == 1)
  {
    cout << "Check digit is: " << check << "\n";
  }
  else if (option == 2)
  {
    cout << "Enter the last digit of the isbn number: ";
    cin >> lastDigit;
    if (lastDigit == check)
      cout << "Hooray the check digits match!\n";
    else
      cout << "The last digit is miscalculated. The check digit should actually be " << check << "\n";
  }
  cout << "Have a good day!\n";
  return 0;
}
