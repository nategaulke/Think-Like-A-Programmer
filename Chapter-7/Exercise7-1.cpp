#include <iostream>
#include <cstring>
using namespace std;

// Modify policy function (176-180, fourth printing) used so that the
// different policies are stored inside the student collection class
// and are assigned with a code value

// Would have preferred to use the typedef firstStudentPolicy but had troubleshooting issues
// might revisit later but user no longer needs to be concerned with details of how program runs

// Simple Student Record w/ grade & ID Number
class StuRecord
{
public:
    StuRecord()
    {
        setStudentNumber(-1);
        setGrade(0);
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

private:
    int grade;
    int studentNumber;
    string name;
};

// Class that holds collection of StuRecord objects
class stuCollection
{
private:
    struct node
    {
        StuRecord data;
        node *next;
    };

    bool higherGrade(StuRecord r1, StuRecord r2)
    {
        return r1.getGrade() > r2.getGrade();
    }

    bool lowerStudentNumber(StuRecord r1, StuRecord r2)
    {
        return r1.getStudentNumber() < r2.getStudentNumber();
    }

    bool nameComesFirst(StuRecord r1, StuRecord r2)
    {
        return strcmp(r1.getName().c_str(), r2.getName().c_str()) < 0;
    }

public:
    // Four different constructors
    stuCollection()
    {
        stuHead = NULL;
        currentPolicy = '\0';
    }

    stuCollection(const stuCollection &rhs)
    {
        stuHead = copy(rhs.stuHead);
        currentPolicy = '\0';
    }

    stuCollection(StuRecord student)
    {
        stuHead = new node;
        stuHead->data = student;
        stuHead->next = NULL;
        currentPolicy = '\0';
    }

    stuCollection(int stuNum, int gr, string name)
    {
        StuRecord newStudent(stuNum, gr, name);
        stuHead = new node;
        stuHead->data = newStudent;
        stuHead->next = NULL;
        currentPolicy = '\0';
    }

    ~stuCollection()
    {
        delNodes(stuHead);
    }

    // Overloads '=' so that copys list not address
    stuCollection &operator=(const stuCollection &rhs)
    {
        if (this != &rhs)
        {
            delNodes(stuHead);
            stuHead = copy(rhs.stuHead);
        }
        currentPolicy = '\0';
        return *this;
    }

    // Add student either with class object or
    // by creating new instance with specified number & grade
    void addRecord(StuRecord newStudent)
    {
        node *newNode = new node;
        newNode->data = newStudent;
        newNode->next = stuHead;
        stuHead = newNode;
    }

    void addRecord(int stuNum, int gr, string name)
    {
        StuRecord newStudent(stuNum, gr, name);
        node *newNode = new node;
        newNode->data = newStudent;
        newNode->next = stuHead;
        stuHead = newNode;
    }

    // Mode of student grades
    double averageRecord()
    {
        int count = 0;
        double sum = 0, average;
        node *loopPtr = stuHead;
        while (loopPtr != NULL)
        {
            sum += loopPtr->data.getGrade();
            count++;
            loopPtr = loopPtr->next;
        }
        average = sum / count;
        return average;
    }

    void printRecords()
    {
        if (stuHead == NULL)
        {
            cout << "No records\n";
            return;
        }
        cout << "Student Records\n";

        printRecordsHelper(stuHead);

        cout << "\n";
    }

    stuCollection recordswithinRange(int min, int max)
    {
        // If no records, then no range to parse through
        if (stuHead == NULL)
            return stuCollection();
        stuCollection rangeCollection;
        int currStuGrade;
        node *loopPtr = stuHead;
        while (loopPtr != NULL)
        {
            currStuGrade = loopPtr->data.getGrade();

            // If current grade is in correct range, add to collection
            if (currStuGrade >= min && currStuGrade <= max)
            {
                rangeCollection.addRecord(loopPtr->data);
            }

            loopPtr = loopPtr->next;
        }
        return rangeCollection;
    }

    // User makes a choice on which policy to use, but does not know the details
    void setFirstStudentPolicy()
    {
        char option;
        cout << "Pick Student Policy:\n1) Student with highest grade\n2) Student who has been at the school the longest\n3) Student who's name comes first alphabetically\n";
        cin >> option;
        if (option == '1')
        {
            currentPolicy = '1';
        }
        else if (option == '2')
        {
            currentPolicy = '2';
        }
        else if (option == '3')
        {
            currentPolicy = '3';
        }
        else
        {
            cout << "This option does not exist at the moment\n";
        }
    }

    // Once policy is set and records are made, determine which policy was selected
    // and seek the "first" based on policy by iterating through list
    StuRecord firstStudent()
    {
        if (stuHead == NULL || currentPolicy == '\0')
        {
            StuRecord dummyRecord(-1, -1, "");
            return dummyRecord;
        }
        node *loopPtr = stuHead;
        StuRecord first = loopPtr->data;
        loopPtr = loopPtr->next;
        while (loopPtr != NULL)
        {
            if (currentPolicy == '1' && higherGrade(loopPtr->data, first))
            {
                first = loopPtr->data;
            }
            else if (currentPolicy == '2' && lowerStudentNumber(loopPtr->data, first))
            {
                first = loopPtr->data;
            }
            else if (currentPolicy == '3' && nameComesFirst(loopPtr->data, first))
            {
                first = loopPtr->data;
            }

            loopPtr = loopPtr->next;
        }
        return first;
    }

private:
    node *stuHead;
    char currentPolicy;

    // Deletes all nodes in collection
    void delNodes(node *ptr)
    {
        if (ptr == NULL)
            return;

        delNodes(ptr->next);
        delete ptr;
    }

    // Copys a collection over
    // (using a little recursion for simplicity)
    node *copy(const node *original)
    {
        if (original == NULL)
            return NULL;

        node *copyHead = new node;
        copyHead->data = original->data;

        copyHead->next = copy(original->next);

        return copyHead;
    }

    // Uses recursion to print student Records
    void printRecordsHelper(node *head)
    {
        if (head == NULL)
            return;
        printRecordsHelper(head->next);
        StuRecord currStudent = head->data;
        cout << "Name: " << currStudent.getName() << "\tID: " << currStudent.getStudentNumber() << "\tGrade: " << currStudent.getGrade() << "\n";
    }
};

int main()
{
    stuCollection school1;
    school1.addRecord(10001, 82, "Cynthia");
    school1.addRecord(10002, 96, "Tommy");
    school1.addRecord(10003, 92, "Carlos");
    school1.addRecord(10004, 79, "Abby");
    school1.printRecords();
    school1.setFirstStudentPolicy();
    // First Student by Grade: Tommy
    // First Student by First Added: Cynthia
    // First Student by Name Alphabetically: Abby
    StuRecord first = school1.firstStudent();
    cout << "\nFirst Student\n";
    cout << "Name: " << first.getName() << "\tID: " << first.getStudentNumber() << "\tGrade: " << first.getGrade() << "\n";
    return 0;
}
