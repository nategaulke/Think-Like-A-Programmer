#include <iostream>
using std::cin;
using std::cout;

/*
  #            #
   ##        ##
    ###    ###
     ########
     ########
    ###    ###
   ##        ##
  #            #
*/

int main()
{
    for (int row = 0; row < 4; row++)
    {
        for (int space = 0; space < row; space++)
        {
            cout << " ";
        }
        for (int hash = 0; hash < row + 1; hash++)
        {
            cout << "#";
        }
        for (int space = 0; space < 12 - row * 4; space++)
        {
            cout << " ";
        }
        for (int hash = 0; hash < row + 1; hash++)
        {
            cout << "#";
        }
        cout << "\n";
    }
    for (int row = 3; row >= 0; row--)
    {
        for (int space = 0; space < row; space++)
        {
            cout << " ";
        }
        for (int hash = 0; hash < row + 1; hash++)
        {
            cout << "#";
        }
        for (int space = 0; space < 12 - row * 4; space++)
        {
            cout << " ";
        }
        for (int hash = 0; hash < row + 1; hash++)
        {
            cout << "#";
        }
        cout << "\n";
    }
    return 0;
}
