#include <iostream>
using namespace std;

// Implement addRecord & averageRecord (from Chapter 4 & 5)
// for class of collection of student records
// (Similar to example used in Chapter 5, except able to
// pass grade/ID directly instead of only stuRecord class)

// Simple Student Record w/ grade & ID Number
class StuRecord
{
public:
    StuRecord()
    {
        setStudentNumber(-1);
        setGrade(0);
    }

    StuRecord(int stuNum, int gr)
    {
        setStudentNumber(stuNum);
        setGrade(gr);
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

private:
    int grade;
    int studentNumber;
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

public:
    // Four different constructors
    stuCollection()
    {
        stuHead = NULL;
    }

    stuCollection(const stuCollection &rhs)
    {
        stuHead = copy(rhs.stuHead);
    }

    stuCollection(StuRecord student)
    {
        stuHead = new node;
        stuHead->data = student;
        stuHead->next = NULL;
    }

    stuCollection(int stuNum, int gr)
    {
        StuRecord newStudent(stuNum, gr);
        stuHead = new node;
        stuHead->data = newStudent;
        stuHead->next = NULL;
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

    void addRecord(int stuNum, int gr)
    {
        StuRecord newStudent(stuNum, gr);
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

private:
    node *stuHead;

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
        cout << "ID: " << currStudent.getStudentNumber() << "\tGrade: " << currStudent.getGrade() << "\n";
    }
};

int main()
{
    // Construct (with ID & grade)
    stuCollection school1(1001, 84);

    // Create two student records & add to school
    StuRecord stu1(1002, 1000);
    school1.addRecord(stu1);
    school1.addRecord(StuRecord(1003, -20));

    // Print records
    school1.printRecords();

    // Print average grade
    cout << "The average grade of these students is: " << school1.averageRecord() << "\n";

    // Construct empty
    stuCollection school2;

    // Print empty records
    cout << "\nNew school built!\n";
    school2.printRecords();
    cout << "\nAdding new students\n";

    // Add student records directly with ID & grade
    school2.addRecord(2001, 34);
    school2.addRecord(2002, 95);

    // Print Records
    school2.printRecords();
    cout << "The average grade of these students is: " << school2.averageRecord() << "\n\n";

    // Copy the grades & print
    school1 = school2;
    cout << "School 1 & School 2 are now merged\n";
    cout << "School 1 ";
    school1.printRecords();
    cout << "School 2 ";
    school2.printRecords();
    return 0;
}
