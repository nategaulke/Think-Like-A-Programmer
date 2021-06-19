#include <iostream>
#include <cstring>
#include <list>
using namespace std;

// Building from the previous exercise find a record by student ID
// using a symbol table (ie binary search tree/hash table)

// Going to implement a hash table which I used in Computer Science I

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
        currentPolicy = '\0';
    }

    stuCollection(const stuCollection &rhs)
    {
        students = rhs.students;
        currentPolicy = '\0';
    }

    stuCollection(StuRecord student)
    {
        students.push_front(student);
        currentPolicy = '\0';
    }

    stuCollection(int stuNum, int gr, string name)
    {
        StuRecord newStudent(stuNum, gr, name);
        students.push_front(newStudent);
        currentPolicy = '\0';
    }

    // Overloads '=' so that copys list not address
    stuCollection &operator=(const stuCollection &rhs)
    {
        if (this != &rhs)
        {
            students = rhs.students;
        }
        currentPolicy = '\0';
        return *this;
    }

    // Add student either with class object or
    // by creating new instance with specified number & grade
    void addRecord(StuRecord newStudent)
    {
        students.push_front(newStudent);
    }

    void addRecord(int stuNum, int gr, string name)
    {
        StuRecord newStudent(stuNum, gr, name);
        students.push_front(newStudent);
    }

    // Mode of student grades
    double averageRecord()
    {
        int count = 0;
        double sum = 0, average;
        auto iter = students.begin();
        while (iter != students.end())
        {
            sum += iter->getGrade();
            count++;
            iter++;
        }
        if (count == 0)
        {
            return 0;
        }
        average = sum / count;
        return average;
    }

    void printRecords()
    {
        if (students.size() == 0)
        {
            cout << "No records\n";
            return;
        }
        cout << "Student Records\n";
        auto iter = students.begin();
        while (iter != students.end())
        {
            cout << "Name: " << iter->getName() << "\tID: " << iter->getStudentNumber() << "\tGrade: " << iter->getGrade() << "\n";
            iter++;
        }
        cout << "\n";
    }

    stuCollection recordswithinRange(int min, int max)
    {
        // If no records, then no range to parse through
        if (students.size() == 0)
            return *this;
        stuCollection rangeCollection;
        int currStuGrade;
        auto iter = students.begin();
        while (iter != students.end())
        {
            currStuGrade = iter->getGrade();

            // If current grade is in correct range, add to collection
            if (currStuGrade >= min && currStuGrade <= max)
            {
                rangeCollection.addRecord(*iter);
            }
            iter++;
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
        if (students.size() == 0 || currentPolicy == '\0')
        {
            StuRecord dummyRecord(-1, -1, "");
            return dummyRecord;
        }
        auto iter = students.begin();
        StuRecord first = *iter;
        iter++;
        while (iter != students.end())
        {
            if (currentPolicy == '1' && higherGrade(*iter, first))
            {
                first = *iter;
            }
            else if (currentPolicy == '2' && lowerStudentNumber(*iter, first))
            {
                first = *iter;
            }
            else if (currentPolicy == '3' && nameComesFirst(*iter, first))
            {
                first = *iter;
            }

            iter++;
        }
        return first;
    }

    StuRecord findRecord(int StudentID)
    {
        // Create hash table for StuRecords w/ size same as size of student body
        int size = students.size() * 2;
        StuRecord *hashTable = new StuRecord[size];
        for (int i = 0; i < size; i++)
        {
            // Empty Space (never been used)
            hashTable[i] = StuRecord(-1, 0, "");
        }
        auto iter = students.begin();
        while (iter != students.end())
        {
            // Insert elements into hash table
            // (Separate insert function that creates hash value)
            insert(*iter, hashTable, size);
            iter++;
        }
        StuRecord retval = retrieve(StudentID, hashTable, size);
        delete[] hashTable;
        return retval;
    }

private:
    list<StuRecord> students;
    char currentPolicy;

    // Using technique similar to Horner's Rule
    // linear runtime based on how many digits are in num
    int hash(int num)
    {
        int hash = 0;
        while (num != 0)
        {
            hash = (hash + num % 10) * 37;
            num /= 10;
        }
        return hash;
    }

    void insert(StuRecord student, StuRecord hashTable[], int size)
    {
        int studentNum = student.getStudentNumber();
        int index, hashval, i = 0;
        hashval = index = hash(studentNum) % size;

        // ID -1 indicates array value is empty
        while (hashTable[index].getStudentNumber() != -1)
        {
            i++;
            // ensures that index will loop back through if necessary
            // linear probing to find next available empty spot
            // Average runtime O(1); Worst runtime O(n)
            index = (hashval + i) % size;
        }

        hashTable[index] = student;
    }

    StuRecord retrieve(int studentID, StuRecord hashTable[], int size)
    {
        int index, hashval, i = 0;
        hashval = index = hash(studentID) % size;

        while (hashTable[index].getStudentNumber() != studentID && hashTable[index].getStudentNumber() != -1)
        {
            i++;
            index = (hashval + i) % size;
            if (i == size)
                return StuRecord(-1, 0, "");
        }
        // Either returns the record with the student ID
        // Or a dummy record if an empty space was found, indicating the record does not exist
        return hashTable[index];
    }
};

int main()
{
    // Construct (with ID & grade)
    stuCollection school1(10000, 65, "Timmy");
    StuRecord stu1(10003, 92, "Carlos");
    school1.addRecord(stu1);
    // Add Records (various methods)

    school1.addRecord(10002, 96, "Tommy");
    school1.addRecord(10005, 82, "Mary");
    school1.addRecord(10007, 43, "Michelle");

    school1.addRecord(StuRecord(10004, 79, "Abby"));
    school1.addRecord(10001, 82, "Cynthia");
    school1.addRecord(10006, 79, "Sammy");
    // Print records
    school1.printRecords();

    int id = 10004;
    cout << "Finding the record for " << id << "\n";
    StuRecord found = school1.findRecord(id);
    cout << "Name: " << found.getName() << "\tID: " << found.getStudentNumber() << "\tGrade: " << found.getGrade() << "\n";
    return 0;
}