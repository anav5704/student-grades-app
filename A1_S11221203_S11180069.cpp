#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int COL_WIDTH = 15;
const int ROW_WIDTH = 55;
const int GRADE_A_PLUS_MIN = 85;
const int GRADE_A_MIN = 78;
const int GRADE_B_PLUS_MIN = 71;
const int GRADE_B_MIN = 64;
const int GRADE_C_PLUS_MIN = 57;
const int GRADE_C_MIN = 50;
const int ONE_HUNDRED = 100;

struct Student
{
    string Id;
    double coursework;
    double finalExam;
};

// ---------------------------- Prototypes ---------------------------- //

void readData(string filename, Student students[], int &studentCount, int capacity);

void updateStudentMarks(Student students[], int studentCount, int minMark, int maxMark);

void printAllStudents(Student students[], int studentCount);

void printTopStudents(Student students[], int studentCount);

void printGradeStats(Student students[], int studentCount);

string getGrade(double coursework, double finalExam);

double getAverageMark(Student students[], int studentCount);

double getPassRate(Student students[], int studentCount);

int validateInt(int lowerLimit, int upperLimit);

void printTableRow(Student students);

void printTableHeader();

string printLine(int length);

int main()
{
    const string FILENAME = "studentData.txt";
    const int DECIMAL_PRECISION = 2;
    const int MIN_MENU_OPTION = 1;
    const int MAX_MENU_OPTION = 5;
    const int MENU_OPTION_1 = 1;
    const int MENU_OPTION_2 = 2;
    const int MENU_OPTION_3 = 3;
    const int MENU_OPTION_4 = 4;
    const int MENU_OPTION_5 = 5;
    const int MIN_MARK = 0;
    const int MAX_MARK = 50;
    const int CAPACITY = 100;

    Student students[CAPACITY];

    bool continueRunning = true;
    int studentCount = 0;
    int menuChoice;

    // Format output with left alignment and fixed decimal place
    cout << left << fixed << setprecision(DECIMAL_PRECISION);

    // ------------------------- App Start ------------------------- //

    cout << "+-----------------------------------------------------+\n"
         << "|                 Student Grades App                  |\n"
         << "+-----------------------------------------------------+\n\n";

    readData(FILENAME, students, studentCount, CAPACITY);

    while (continueRunning)
    {
        cout << "\n1. View all students' details" << endl
             << "2. View top students' details" << endl
             << "3. View grade statistics" << endl
             << "4. Update student's marks" << endl
             << "5. Exit\n\n";

        cout << "Enter choice: ";
        menuChoice = validateInt(MIN_MENU_OPTION, MAX_MENU_OPTION);
        cout << endl;

        switch (menuChoice)
        {
        case MENU_OPTION_1:
            printAllStudents(students, studentCount);
            break;

        case MENU_OPTION_2:
            printTopStudents(students, studentCount);
            break;

        case MENU_OPTION_3:
            printGradeStats(students, studentCount);
            break;

        case MENU_OPTION_4:
            updateStudentMarks(students, studentCount, MIN_MARK, MAX_MARK);
            break;

        case MENU_OPTION_5:
            cout << "Exiting..." << endl;
            continueRunning = false;
            break;
        }
    }

    return 0;
}

// ---------------------------- Functions ---------------------------- //

void readData(string filename, Student students[], int &studentCount, int capacity)
{
    bool isFull = studentCount == capacity;
    ifstream readFile(filename.c_str());

    if (readFile.fail())
    {
        cout << "Oops, could not open file: " << filename << endl;
        exit(1);
    }

    string headerOmit;
    getline(readFile, headerOmit);

    // Fill array until capacity is not reached and data exists
    while (!isFull && readFile >> students[studentCount].Id >> students[studentCount].coursework >> students[studentCount].finalExam)
    {
        studentCount++;
    }

    readFile.close();
}

// Helper function to print the table header
void printTableHeader()
{
    cout << setw(COL_WIDTH) << "Student ID"
         << setw(COL_WIDTH) << "CW"
         << setw(COL_WIDTH) << "Final"
         << setw(COL_WIDTH) << "Grade" << endl
         << printLine(ROW_WIDTH) << endl;
}

// Helper function to print a table row (student details)
void printTableRow(Student students)
{
    string grade = getGrade(students.coursework, students.finalExam);

    cout << setw(COL_WIDTH) << students.Id
         << setw(COL_WIDTH) << students.coursework
         << setw(COL_WIDTH) << students.finalExam
         << setw(COL_WIDTH) << grade << endl
         << printLine(ROW_WIDTH) << endl;
}

void printAllStudents(Student students[], int studentCount)
{
    printTableHeader();

    for (int i = 0; i < studentCount; i++)
    {
        printTableRow(students[i]);
    }
}

void printTopStudents(Student students[], int studentCount)
{
    double highestMark = students[0].coursework + students[0].finalExam;

    //  Loop through all students and get highest mark
    for (int i = 0; i < studentCount; i++)
    {
        double totalMark = students[i].coursework + students[i].finalExam;

        if (totalMark >= highestMark)
        {
            highestMark = totalMark;
        }
    }

    printTableHeader();

    // Loop through all students and print those with the highest mark
    for (int i = 0; i < studentCount; i++)
    {
        double totalMark = students[i].coursework + students[i].finalExam;

        if (totalMark == highestMark)
        {
            printTableRow(students[i]);
        }
    }
}

void printGradeStats(Student students[], int studentCount)
{
    cout << "Average Mark: " << getAverageMark(students, studentCount) << endl;
    cout << "Pass Rate: " << getPassRate(students, studentCount) << "%" << endl;
}

double getAverageMark(Student students[], int studentCount)
{
    double totalMarks = 0.0;

    for (int i = 0; i < studentCount; i++)
    {
        totalMarks += students[i].coursework + students[i].finalExam;
    }

    return totalMarks / studentCount;
}

double getPassRate(Student students[], int studentCount)
{
    double passCount = 0.0;

    for (int i = 0; i < studentCount; i++)
    {
        string grade = getGrade(students[i].coursework, students[i].finalExam);

        if (grade != "D")
        {
            passCount++;
        }
    }

    return (passCount / studentCount) * ONE_HUNDRED;
}

string getGrade(double coursework, double finalExam)
{
    double totalMark = coursework + finalExam;

    if (totalMark >= GRADE_A_PLUS_MIN)
    {
        return "A+";
    }
    else if (totalMark >= GRADE_A_MIN)
    {
        return "A";
    }
    else if (totalMark >= GRADE_B_PLUS_MIN)
    {
        return "B+";
    }
    else if (totalMark >= GRADE_B_MIN)
    {
        return "B";
    }
    else if (totalMark >= GRADE_C_PLUS_MIN)
    {
        return "C+";
    }
    else if (totalMark >= GRADE_C_MIN)
    {
        return "C";
    }
    else
    {
        return "D";
    }
}

void updateStudentMarks(Student students[], int studentCount, int minMark, int maxMark)
{
    bool studentExists = false;
    int studentIndex;
    string studentId;
    double coursework;
    double finalExam;

    cout << "Enter student Id: ";
    cin >> studentId;

    //  Check if student exists and get their index
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].Id == studentId)
        {
            studentExists = true;
            studentIndex = i;
        }
    }

    if (studentExists)
    {
        cout << "Enter new coursework: ";
        coursework = validateInt(minMark, maxMark);

        cout << "Enter new final exam: ";
        finalExam = validateInt(minMark, maxMark);

        students[studentIndex].coursework = coursework;
        students[studentIndex].finalExam = finalExam;

        cout << "\nStudent details updated successfully!\n\n";

        printTableHeader();
        printTableRow(students[studentIndex]);
    }
    else
    {
        cout << "\nOops, student Id: " << studentId << " was not found" << endl;
    }
}

int validateInt(int lowerLimit, int upperLimit)
{
    int input;
    cin >> input;

    while (cin.fail() || (input < lowerLimit || input > upperLimit))
    {
        cin.clear();
        string dummy;
        getline(cin, dummy);

        cout << "\nOops! Something went wrong." << endl;

        // Input is not a number
        if (cin.fail())
        {
            cout << "Please enter a number: ";
        }

        // Input is out of range
        else if (input < lowerLimit || input > upperLimit)
        {
            cout << "Try entering something between " << lowerLimit << " and " << upperLimit << ": ";
        }

        cin >> input;
    }

    return input;
}

// Helper function to print a horizontal line
string printLine(int length)
{
    string line = "";

    for (int i = 0; i < length; i++)
    {
        line += "-";
    }

    return line;
}
