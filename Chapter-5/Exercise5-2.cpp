#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Building from the previous exercise, write two methods:
// One that outputs a string with the car's information
// The other listing how old the car is in years
// Search internet for string formatting/time setup questions

class automobile
{
public:
    automobile()
    {
        maker = "";
        model = "";
        year = -1;
    }
    automobile(string maker, string model, int year)
    {
        setMaker(maker);
        setModel(model);
        setYear(year);
    }
    string getMaker()
    {
        return maker;
    }
    void setMaker(string maker)
    {
        this->maker = maker;
    }
    string getModel()
    {
        return model;
    }
    void setModel(string model)
    {
        this->model = model;
    }
    int getYear()
    {
        return year;
    }
    void setYear(int year)
    {
        this->year = year;
    }

    string getDescription()
    {
        string retval = to_string(this->getYear()) + " " + this->getMaker() + " " + this->getModel();
        return retval;
    }

    int findAge()
    {
        int age, curYear;
        time_t current = time(0);
        tm *rightNow = localtime(&current);
        curYear = 1900 + rightNow->tm_year;
        age = curYear - year;
        return age;
    }

private:
    string maker;
    string model;
    int year;
};

int main()
{
    automobile car("Chevrolet", "Impala", 1957);
    cout << "Car Information: " << car.getDescription() << "\n";
    cout << "The automobile is " << car.findAge() << " year(s) old.\n";
    return 0;
}
