#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Student
{
    string ID;
    double coursework;
    double finalExam;
};

// ---------------------------- Prototypes ---------------------------- //

void printTableHeader();

string printLine(int length);

void printTableRow(Student students);

void printGradeStats(Student students[], int size);

string getGrade(double coursework, double finalExam);

void UpdateStudentMarks(Student students[], int size);

double getPassRate(const Student students[], int size);

double getAverageMark(const Student students[], int size);

void printHighestScorer(const Student students[], int size);

void printStudentTables(const Student students[], int size);

void readData(const string &filename, Student students[], int &studentCount, int maxSize);

int main()
{
    const string FILENAME = "studentData.txt";
    const int SIZE = 100;

    Student students[SIZE];
    int studentCount = 0;
    int choice;
    bool continueRunning = true;
    string studentID;
    double newCoursework;
    double newFinalExam;

    cout << left << fixed << setprecision(2);

    // ------------------------- App Start ------------------------- //

    cout << "+-----------------------------------------------------+\n"
         << "|                 Student Grades App                  |\n"
         << "+-----------------------------------------------------+\n\n";

    readData(FILENAME, students, studentCount, SIZE);

    while (continueRunning)
    {
        cout << "\n1. View all students' details" << endl
             << "2. View top student's details" << endl
             << "3. View grade statistics" << endl
             << "4. Update student's marks\n"
             << "5. Exit\n\n";

        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            printStudentTables(students, studentCount);
            break;

        case 2:
            printHighestScorer(students, studentCount);
            break;

        case 3:
            printGradeStats(students, studentCount);
            break;

        case 4:
            UpdateStudentMarks(students, studentCount);
            break;
        case 5:
            cout << "Exiting..." << endl;
            continueRunning = false;
            break;
        }
    }

    return 0;
}

// ---------------------------- Functions ---------------------------- //

string printLine(int length)
{
    string line = "";

    for (int i = 0; i < length; i++)
    {
        line += "-";
    }

    return line;
}

string getGrade(double coursework, double finalExam)
{
    double totalMark = coursework + finalExam;

    if (totalMark >= 85 && totalMark <= 100)
        return "A+";
    else if (totalMark >= 78 && totalMark < 85)
        return "A";
    else if (totalMark >= 71 && totalMark < 78)
        return "B+";
    else if (totalMark >= 64 && totalMark < 71)
        return "B";
    else if (totalMark >= 57 && totalMark < 64)
        return "C+";
    else if (totalMark >= 50 && totalMark < 57)
        return "C";
    else
        return "D";
}

void readData(const string &filename, Student students[], int &studentCount, int maxSize)
{
    ifstream readFile(filename);

    if (readFile.fail())
    {
        cout << "Error! Could not open file: " << filename << endl;
        exit(1);
    }

    string headerOmit;
    getline(readFile, headerOmit);

    while (readFile >> students[studentCount].ID >> students[studentCount].coursework >> students[studentCount].finalExam)
    {
        studentCount++;
    }

    readFile.close();
}

double getAverageMark(const Student students[], int size)
{
    double totalMarks = 0.0;

    for (int i = 0; i < size; i++)
    {
        totalMarks += students[i].coursework + students[i].finalExam;
    }

    return totalMarks / size;
}

double getPassRate(const Student students[], int size)
{
    int passCount = 0;

    for (int i = 0; i < size; i++)
    {
        string grade = getGrade(students[i].coursework, students[i].finalExam);

        if (grade != "D")
        {
            passCount++;
        }
    }

    return (1.0 * passCount) / size;
}

void printHighestScorer(const Student students[], int size)
{
    int highestIndex = 0;

    double highestMark = students[0].coursework + students[0].finalExam;

    for (int i = 0; i < size; i++)
    {
        double totalMark = students[i].coursework + students[i].finalExam;

        if (totalMark > highestMark)
        {
            highestMark = totalMark;
            highestIndex = i;
        }
    }

    printTableHeader();
    printTableRow(students[highestIndex]);
}

void printTableHeader()
{
    cout << setw(15) << "Student ID"
         << setw(15) << "CW"
         << setw(15) << "Final"
         << setw(15) << "Grade" << endl
         << printLine(55) << endl;
}

void printTableRow(Student students)
{
    string grade = getGrade(students.coursework, students.finalExam);

    cout << setw(15) << students.ID
         << setw(15) << students.coursework
         << setw(15) << students.finalExam
         << setw(15) << grade << endl
         << printLine(55) << endl;
}

void printStudentTables(const Student students[], int size)
{
    printTableHeader();

    for (int i = 0; i < size; ++i)
    {
        printTableRow(students[i]);
    }
}

void printGradeStats(Student students[], int size)
{
    double averageMark = getAverageMark(students, size);
    double passRate = getPassRate(students, size);

    cout << "Average Mark: " << averageMark << endl;
    cout << "Pass Rate: " << passRate * 100 << "%" << endl;
}

void UpdateStudentMarks(Student students[], int size)
{

    string studentID;
    double newCoursework;
    double newFinalExam;

    cout << "Enter student ID: ";
    cin >> studentID;

    cout << "Enter new coursework: ";
    cin >> newCoursework;

    cout << "Enter new final exam: ";
    cin >> newFinalExam;

    for (int i = 0; i < size; i++)
    {
        if (students[i].ID == studentID)
        {
            students[i].coursework = newCoursework;
            students[i].finalExam = newFinalExam;

            cout << "Student details updated successfully!" << endl;
            return;
        }
    }

    cout << "Student ID not found!" << endl;
}