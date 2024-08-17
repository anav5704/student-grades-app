#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string ID;
    double coursework;
    double finalExam;
};

char CalGrade(double coursework, double finalExam) {
    double totalMark = coursework + finalExam;
    
    if (totalMark >= 85)
        return 'A';
    if (totalMark >= 78)
        return 'B';
    if (totalMark >= 50)
        return 'C';
    else
        return 'D';
}

void readData(const string& filename, Student students[], int& numStudents) {
    ifstream in_file(filename);

    if (in_file.fail()) {
        cout << "Error! Invalid File Found." << endl;
        exit(1);
    }

    numStudents = 0;
    while (in_file >> students[numStudents].ID >> students[numStudents].coursework >> students[numStudents].finalExam) {
        numStudents++;
    }

    in_file.close();
}

void printStudentData(const Student students[], int size) {
    cout << "The student data is displayed below:\n";
    cout << "Student ID\tCoursework\tFinal Exam\tGrade\n";

    for (int i = 0; i < size; ++i) {
        char grade = CalGrade(students[i].coursework, students[i].finalExam);
        cout << students[i].ID << "\t\t"
             << students[i].coursework << "\t\t"
             << students[i].finalExam << "\t\t"
             << grade << endl;
    }
}

int main() {
    const int SIZE = 20;
    Student students[SIZE];
    int numStudents = 0;
    
    readData("studentData.txt", students, numStudents);
    printStudentData(students, numStudents);

    return 0;
}
