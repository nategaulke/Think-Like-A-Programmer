#include <iostream>
using std::cin;
using std::cout;

/*
########
 ######
  ####
   ##
*/

int main() {
  for (int row = 0; row < 4; row++)
  {
    for (int space = 0; space < row; space++)
    {
      cout << " ";
    }
    for (int hash = 0; hash < 8 - row * 2; hash++)
    {
      cout << "#";
    }
    cout << "\n";
  }


  return 0;
}
