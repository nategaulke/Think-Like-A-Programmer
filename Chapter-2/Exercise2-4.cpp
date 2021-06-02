#include <iostream>
using namespace std;

/*
  My own pattern of hash marks to reproduce with program
  # # # # # # # # # #
   # # # # # # # # # 
  # # # # # # # # # # 
   # # # # # # # # # 
  # # # # # # # # # # 
   # # # # # # # # # 
  # # # # # # # # # # 
   # # # # # # # # # 
*/

int main()
{
    for (int row = 0; row < 8; row++)
    {
        // Even rows have columns start with '#'
        if (row % 2 == 0)
        {
            for (int col = 0; col < 19; col++)
            {
                if (col % 2 == 0)
                    cout << "#";
                else
                    cout << " ";
            }
        }
        // Odd rows have columns that start with ' '
        else
        {
            for (int col = 0; col < 19; col++)
            {
                if (col % 2 == 0)
                    cout << " ";
                else
                    cout << "#";
            }
        }
        cout << "\n";
    }
    return 0;
}
