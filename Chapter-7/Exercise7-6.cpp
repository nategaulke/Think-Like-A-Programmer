#include <iostream>
#include <cstring>
#include <list>
using namespace std;

// Find a design pattern that can add to a Student Record:
// a term paper title, year of enrollment, and/or a bool indicating
// whether student is auditing a class; any combination is possible

// Will modify the strategy pattern idea, allowing user to choose to use the fields
// but will also already have them set up in case user decides to use them

// Simple Student Record w/ grade & ID Number
class StuRecord
{
public:
    StuRecord()
    {
        setStudentNumber(-1);
        setGrade(0);
        paperTitle = "";
        enrollYear = NULL;
        audited = NULL;
    }

    StuRecord(int stuNum, int gr, string name)
    {
        setStudentNumber(stuNum);
        setGrade(gr);
        setName(name);
        paperTitle = "";
        enrollYear = NULL;
        audited = NULL;
    }

    ~StuRecord()
    {
        if (audited != NULL)
            delete audited;
        if (enrollYear != NULL)
            delete enrollYear;
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

    // User MUST use add, to add the specified field
    void addTitle(string paperTitle)
    {
        this->paperTitle = paperTitle;
    }

    void addEnrollYear(int enrollYear)
    {
        if (this->enrollYear == NULL)
            this->enrollYear = new int;
        *this->enrollYear = enrollYear;
    }

    void addAudited(bool audited)
    {
        if (this->audited == NULL)
            this->audited = new bool;
        *this->audited = audited;
    }

    // Setters and Getters won't work until field is added
    // and initialized
    void setTitle(string paperTitle)
    {
        if (this->paperTitle != "")
            this->paperTitle = paperTitle;
        else
            cout << "This field has not been added\n";
    }

    void setEnrollYear(int enrollYear)
    {
        if (this->enrollYear != NULL)
            *this->enrollYear = enrollYear;
        else
            cout << "This field has not been added\n";
    }

    void setAudited(bool audited)
    {
        if (this->audited != NULL)
            *this->audited = audited;
        else
            cout << "This field has not been added\n";
    }

    string getTitle()
    {
        if (paperTitle != "")
            return paperTitle;
        else
        {
            return "This field has not been added\n";
        }
    }

    int getEnrollYear()
    {
        if (enrollYear != NULL)
            return *enrollYear;
        else
            return -1;
    }

    bool getAudited()
    {
        if (audited != NULL)
            return *audited;
        else
            return NULL;
    }

    // Puts the onus on creating a string for output on the class not the user
    // Also makes it less likely that user will know about/see fields they didn't add
    void print()
    {
        cout << "Name: " << getName();
        cout << "\tID: " << getStudentNumber();
        cout << "\tGrade: " << getGrade();
        if (paperTitle != "")
            cout << "\tPaper Title: " << getTitle();
        if (getEnrollYear() != -1)
            cout << "\tYear of Enrollment: " << getEnrollYear();
        if (audited != NULL)
        {
            cout << "\tAudit Status: ";
            if (getAudited() == true)
                cout << "Yes";
            else
                cout << "No";
        }
        cout << "\n";
    }

private:
    int grade;
    int studentNumber;
    string name;
    string paperTitle;
    int *enrollYear;
    bool *audited;
};

int main()
{
    list<StuRecord> students;
    students.push_front(StuRecord(10001, 96, "Tommy"));
    students.push_front(StuRecord(10002, 92, "Carlos"));
    students.push_front(StuRecord(10003, 79, "Abby"));
    students.push_front(StuRecord(10004, 75, "Daisy"));

    auto iter = students.begin();
    // First record will not contain no special categories
    iter++;

    // Second record will contain all special categories
    iter->addTitle("The Theory of Everything");
    iter->addEnrollYear(2019);
    iter->addAudited(true);
    iter++;

    // Third record will have enroll year and audited and will
    // attempt to set a title without first adding it
    // (thus printing "This field has not been added")
    iter->addEnrollYear(2018);
    iter->addAudited(false);
    iter->setTitle("How My Life Goes");
    iter++;

    // Final record will have a title & will change it
    iter->addTitle("My Life Story");
    iter->setTitle("How I Made a Ton of Money");
    iter = students.begin();
    while (iter != students.end())
    {
        iter->print();
        iter++;
    }
    return 0;
}