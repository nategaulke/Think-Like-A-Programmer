#include <iostream>
#include <cstring>
#include <list>
using namespace std;

// Take a problem you've already solved, and solve it using a different component

// I modified my solution for exercise 7-3 by sorting the array of records using
// merge sort (more efficient than insertion sort) and by using binary search instead
// of interpolation search

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
        StuRecord *stuArray = new StuRecord[students.size()];
        auto iter = students.begin();
        int i = 0;

        while (iter != students.end())
        {
            stuArray[i++] = *iter;
            iter++;
        }
        sort(stuArray, 0, students.size() - 1);

        StuRecord retval = binarySearch(stuArray, StudentID, 0, students.size() - 1);
        delete[] stuArray;
        return retval;
    }

private:
    list<StuRecord> students;
    char currentPolicy;

    // Simple swap of two elements in array
    void swap(StuRecord array[], int a, int b)
    {
        StuRecord temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    // Merge sort has a runtime of O(n log n) where n is the size of the array
    void sort(StuRecord array[], int lo, int hi)
    {
        // Base case, only one element to be sorted
        if (lo >= hi)
            return;
        int i, j, k, mid = lo + (hi - lo) / 2;
        StuRecord *copy = NULL;

        // Recursive calls to sort both halves of array
        sort(array, lo, mid);
        sort(array, mid + 1, hi);

        copy = new StuRecord[hi - lo + 1];
        // Start of first halve of array
        i = lo;
        // Start of second halve of array
        j = mid + 1;
        // Start of the new array
        k = 0;

        // Copy the elements into the array
        while (i <= mid || j <= hi)
        {
            // If haven't traverse through both halves yet
            // then check which is the smaller value
            if (i <= mid && j <= hi)
            {
                if (array[i].getStudentNumber() < array[j].getStudentNumber())
                    copy[k++] = array[i++];
                else
                    copy[k++] = array[j++];
            }
            // If second half of array is done, copy the first half over
            else if (j > hi)
            {
                copy[k++] = array[i++];
            }
            // If first half of array is done, copy the second half over
            else if (i > mid)
            {
                copy[k++] = array[j++];
            }
        }

        // Copy the sorted contents and discard the allocated array
        for (i = lo; i <= hi; i++)
            array[i] = copy[i - lo];

        delete[] copy;
    }

    // Using binary search algorithm (must be sorted values)
    // O (log n)
    StuRecord binarySearch(StuRecord array[], int value, int lo, int hi)
    {
        if (lo <= hi && value >= array[lo].getStudentNumber() && value <= array[hi].getStudentNumber())
        {
            int mid = lo + (hi - lo) / 2;

            if (array[mid].getStudentNumber() == value)
                return array[mid];

            if (array[mid].getStudentNumber() < value)
                return binarySearch(array, value, mid + 1, hi);

            if (array[mid].getStudentNumber() > value)
                return binarySearch(array, value, lo, mid - 1);
        }
        return StuRecord(0, 0, "");
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

    school1.addRecord(StuRecord(10004, 79, "Abby"));
    school1.addRecord(10001, 82, "Cynthia");
    // Print records
    school1.printRecords();

    int id = 10003;
    cout << "Finding the record for " << id << "\n";
    StuRecord found = school1.findRecord(id);
    cout << "Name: " << found.getName() << "\tID: " << found.getStudentNumber() << "\tGrade: " << found.getGrade() << "\n";
    return 0;
}