#include <iostream>
#include <string>
using namespace std;

// Create a Automobile class with manufacturer, model, and year; Add the setters and getters

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

private:
    string maker;
    string model;
    int year;
};

int main()
{
    automobile car("Toyota", "Camry", 2002);
    cout << "Car Information: " << car.getMaker() << " " << car.getModel() << " " << car.getYear() << "\n";
    cout << "Changing Car's Information\n";
    car.setModel("Corolla");
    car.setYear(2021);
    cout << "New Car Information: " << car.getMaker() << " " << car.getModel() << " " << car.getYear() << "\n";
    return 0;
}
