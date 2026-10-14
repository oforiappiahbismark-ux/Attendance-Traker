#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 30;
const int NUM_DAYS = 5;

string students[MAX_STUDENTS];
int attendance[MAX_STUDENTS][NUM_DAYS] = {};  // 1 = present, 0 = absent
int studentCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Class is full.\n";
        return;
    }
    cout << "Student name: ";
    cin >> ws;
    getline(cin, students[studentCount]);
    cout << "Added with ID " << studentCount << "\n";
    studentCount++;
}

void markAttendance() {
    int id, day, status;
    cout << "Student ID: ";
    cin >> id;
    cout << "Day (1-" << NUM_DAYS << "): ";
    cin >> day;
    cout << "Present? (1 = yes, 0 = no): ";
    cin >> status;

    if (id < 0 || id >= studentCount || day < 1 || day > NUM_DAYS ||
        (status != 0 && status != 1)) {
        cout << "Invalid input.\n";
        return;
    }
    attendance[id][day - 1] = status;
    cout << "Recorded.\n";
}

double percentage(int id) {
    int present = 0;
    for (int d = 0; d < NUM_DAYS; d++) present += attendance[id][d];
    return (double)present / NUM_DAYS * 100;
}

void showReport() {
    cout << "\n" << left << setw(5) << "ID" << setw(15) << "Name";
    for (int d = 1; d <= NUM_DAYS; d++) cout << "D" << d << " ";
    cout << "  %\n";
    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(5) << i << setw(15) << students[i];
        for (int d = 0; d < NUM_DAYS; d++) cout << attendance[i][d] << "  ";
        cout << fixed << setprecision(1) << "  " << percentage(i) << "\n";
    }
}

void belowThreshold() {
    double limit = 75;
    bool found = false;
    cout << "\nStudents below " << limit << "%:\n";
    for (int i = 0; i < studentCount; i++) {
        if (percentage(i) < limit) {
            cout << " - " << students[i] << " (" << percentage(i) << "%)\n";
            found = true;
        }
    }
    if (!found) cout << " None\n";
}

void worstDay() {
    if (studentCount == 0) { cout << "No students yet.\n"; return; }
    int worst = 0, lowest = studentCount + 1;
    for (int d = 0; d < NUM_DAYS; d++) {
        int total = 0;
        for (int s = 0; s < studentCount; s++) total += attendance[s][d];
        if (total < lowest) { lowest = total; worst = d; }
    }
    cout << "Lowest turnout: Day " << worst + 1
         << " (" << lowest << " present)\n";
}

int main() {
    int choice;
    do {
        cout << "\n=== Attendance Tracker ===\n"
             << "1. Add student\n2. Mark attendance\n3. Show report\n"
             << "4. Students below 75%\n5. Day with lowest turnout\n0. Exit\n"
             << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: markAttendance(); break;
            case 3: showReport(); break;
            case 4: belowThreshold(); break;
            case 5: worstDay(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
