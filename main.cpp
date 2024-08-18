#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Student {
    string ID;
    double coursework;
    double finalExam;
};

string CalGrade(double coursework, double finalExam) {
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

void printFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "Contents of " << filename << ":\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Error! Unable to open file: " << filename << endl;
    }
}

void readData(const string& filename, Student students[], int& numStudents, int maxSize) {
    ifstream in_file(filename);

    if (in_file.fail()) {
        cout << "Error! Could not open file: " << filename << endl;
        return;
    }

    string line;
    getline(in_file, line);

    numStudents = 0;
    while (numStudents < maxSize && getline(in_file, line)) {
        istringstream iss(line);
        if (iss >> students[numStudents].ID >> students[numStudents].coursework >> students[numStudents].finalExam) {
            numStudents++;
        }
    }

    if (numStudents == 0) {
        cout << "Warning: No data was read from the file." << endl;
    } else if (numStudents == maxSize && !in_file.eof()) {
        cout << "Warning: Maximum number of students reached. Some data may not have been read." << endl;
    }

    in_file.close();
}

double calAvgMark(const Student students[], int size) {
    if (size == 0)
        return 0.0;

    double totalMarks = 0.0;

    for (int i = 0; i < size; i++) {
        totalMarks += students[i].coursework + students[i].finalExam;
    }

    return totalMarks / size;
}

double calPassRate(const Student students[], int size) {
    if (size == 0)
        return 0.0;

    int passCount = 0;

    for (int i = 0; i < size; i++) {
        string grade = CalGrade(students[i].coursework, students[i].finalExam);
        if (grade == "A+" || grade == "A" || grade == "B+" || grade == "B" || grade == "C+" || grade == "C") {
            passCount++;
        }
    }

    return (1.0 * passCount) / size;
}

void findHighestScorer(const Student students[], int size) {
    if (size == 0) {
        cout << "No students to review." << endl;
        return;
    }

    int highestIndex = 0;
    double highestMark = students[0].coursework + students[0].finalExam;

    for (int i = 1; i < size; i++) {
        double totalMark = students[i].coursework + students[i].finalExam;
        if (totalMark > highestMark) {
            highestMark = totalMark;
            highestIndex = i;
        }
    }

    cout << "Highest Scorer Details:\n";
    cout << "Student ID: " << students[highestIndex].ID << endl;
    cout << "Coursework Mark: " << students[highestIndex].coursework << endl;
    cout << "Final Exam Mark: " << students[highestIndex].finalExam << endl;
    cout << "Total Mark: " << highestMark << endl;
    cout << "Grade: " << CalGrade(students[highestIndex].coursework, students[highestIndex].finalExam) << endl;
}

void printStudentData(const Student students[], int size) {
    cout << "The student data is displayed below:\n";
    cout << "Student ID\tCoursework\tFinal Exam\tGrade\n";

    for (int i = 0; i < size; ++i) {
        string grade = CalGrade(students[i].coursework, students[i].finalExam);
        cout << students[i].ID << "\t\t"
             << students[i].coursework << "\t\t"
             << students[i].finalExam << "\t\t"
             << grade << endl;
    }

    double avgMark = calAvgMark(students, size);
    double passRate = calPassRate(students, size);
    
    cout << fixed << setprecision(2);
    cout << "\nAverage Mark: " << avgMark << endl;
    cout << "Pass Rate: " << passRate * 100 << "%" << endl;
    
    findHighestScorer(students, size);
}

void UpdateStudentMarks(Student students[], const string& studentID, double newCoursework, double newFinalExam, int size) {
    for (int i = 0; i < size; i++) {
        if (students[i].ID == studentID) {
            students[i].coursework = newCoursework;
            students[i].finalExam = newFinalExam;
            cout << "Marks updated successfully for student ID: " << studentID << endl;
            cout << "Updated Coursework: " << students[i].coursework << endl;
            cout << "Updated Final Exam: " << students[i].finalExam << endl;
            return;
        }
    }
    cout << "Student ID not found!" << endl;
}

int main() {
    const int SIZE = 100;
    Student students[SIZE];
    int numStudents = 0;
    string studentID;
    double newCoursework;
    double newFinalExam;

    string filename = "studentData.txt";
    
    cout << "Attempting to read file: " << filename << endl;
    printFile(filename);

    readData(filename, students, numStudents, SIZE);
    
    if (numStudents == 0) {
        cout << "No student data was rea." << endl;
        return 1;
    }

    cout << "Number of students read: " << numStudents << endl;
    printStudentData(students, numStudents);

    cout << "Enter student ID if you want to update: " << endl;
    cin >> studentID;
    cout << "Enter New Coursework Mark: " << endl;
    while (true) {
        cin >> newCoursework;
        if (cin.fail()) {
            cout << "Invalid Coursework Mark. Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            break;
        }
    }
    cout << "Enter New Final Exam Marks: " << endl;
    while (true) {
        cin >> newFinalExam;
        if (cin.fail()) {
            cout << "Invalid Final Exam mark. Try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            break;
        }
    }

    UpdateStudentMarks(students, studentID, newCoursework, newFinalExam, numStudents);

    return 0;
}
