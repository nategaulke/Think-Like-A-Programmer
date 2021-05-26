#include <iostream>
using namespace std;

// Building from the previous exercise
// New method that returns collection of students
// within certain range of grades

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
    stuCollection class1;
    class1.addRecord(1001, 40);
    class1.addRecord(1002, 80);
    class1.addRecord(1003, 99);
    class1.addRecord(1004, 85);
    class1.addRecord(1005, 100);
    class1.addRecord(1006, 66);
    class1.addRecord(1007, 84);
    class1.addRecord(1008, 80);
    class1.addRecord(1009, 76);
    class1.addRecord(10010, 90);
    cout << "Class 1 ";
    class1.printRecords();

    // Copying the records for specified range
    stuCollection class2;
    cout << "Adding high achieving students (85 - 100) to an additional class\n";
    class2 = class1.recordswithinRange(85, 100);

    cout << "Class 1 ";
    class1.printRecords();
    cout << "Class 2 ";
    class2.printRecords();
    return 0;
}
