#include <iostream>
#include <cstring>
#include <list>
#include <unordered_map>
using namespace std;

// Building from the previous exercise, make it possible for user
// to add any field they want to the Student Record class

// Each Student record will have a unorder map, where the category will
// be the key, and the data is the value of it

// Simple Student Record w/ grade & ID Number
class StuRecord
{
public:
    StuRecord()
    {
        setStudentNumber(-1);
        setGrade(0);
        setName("");
    }

    StuRecord(int stuNum, int gr, string name)
    {
        setStudentNumber(stuNum);
        setGrade(gr);
        setName(name);
    }

    int getGrade()
    {
        return grade;
    }

    // Inputs grades on 0 - 100 scale (no Extra Credit)
    void setGrade(int grade)
    {
        if (grade < 0)
            this->grade = 0;
        else if (grade > 100)
            this->grade = 100;
        else
            this->grade = grade;
    }

    int getStudentNumber()
    {
        return studentNumber;
    }

    void setStudentNumber(int studentNumber)
    {
        this->studentNumber = studentNumber;
    }

    string getName()
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void addExtraField(string field, string data)
    {
        extraField[field] = data;
    }

    string retrieveField(string field)
    {
        if (extraField.find(field) == extraField.end())
            return field + " does not exist";
        return extraField.at(field);
    }

    // Puts the onus on creating a string for output on the class not the user
    // Also makes it less likely that user will know about/see fields they didn't add
    void print()
    {
        cout << "Name: " << getName();
        cout << "\tID: " << getStudentNumber();
        cout << "\tGrade: " << getGrade();
        auto iter = extraField.begin();
        while (iter != extraField.end())
        {
            cout << "\t" << iter->first << ": " << iter->second;
            iter++;
        }
        cout << "\n";
    }

private:
    int grade;
    int studentNumber;
    string name;
    // Add any number of fields with values to an individual record
    unordered_map<string, string> extraField;
};

int main()
{
    list<StuRecord> students;
    students.push_front(StuRecord(10001, 96, "Tommy"));
    students.push_front(StuRecord(10002, 92, "Carlos"));
    students.push_front(StuRecord(10003, 79, "Abby"));
    students.push_front(StuRecord(10004, 75, "Daisy"));

    auto iter = students.begin();
    // First record will remain unchanged
    iter++;

    // Second record will have a book title, year of enrollment, and audited status
    iter->addExtraField("Book Title", "The Theory of How to Live Your Best Life");
    iter->addExtraField("Year of Enrollment", "2018");
    iter->addExtraField("Audit Status", "Yes");
    iter++;

    // Third Record will have a Year of Enrollment as well and will attempt to retrieve
    // a non existent field
    iter->addExtraField("Year of Enrollment", "2017");
    cout << iter->retrieveField("Audit Status") << "\n";
    iter++;

    // Final record will add a category unlike the others and will change it to something else
    // then retrieve it
    iter->addExtraField("Favorite Professor", "Dr. Leiowitz");
    iter->addExtraField("Favorite Professor", "Dr. Daffodil");
    cout << iter->retrieveField("Favorite Professor") << "\n";

    iter = students.begin();
    while (iter != students.end())
    {
        iter->print();
        iter++;
    }
    return 0;
}