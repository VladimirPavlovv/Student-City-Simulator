#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int SESSION = 45;

struct Student
{
    int Z; // Знание
    int P; // Психика
    int E; // Енергия
    int K; // Пари(кеш) 
    int I; // Изпити(взети)
} student;

struct Game {
    int difficulty;
    int day;
    int examNumber;
    int passedExams;
    double success;
    //add student stats for easier save!!!
} game;

void showStats() {
    //fix ascii output!!!
    cout << "======================= " << endl;
    cout << "|| Day: " << game.day << endl;
    cout << "|| Money: " << student.K << endl;
    cout << "|| Energy: " << student.E << endl;
    cout << "|| Mentality: " << student.P << endl;
    cout << "|| Knowledge: " << student.Z << endl;
    cout << "======================= " << endl;
}

// Зареждане на игра от файл
void loadGameLoop() {

}

// Започване на нова игра
void newGameLoop() {
    int difficulty;

    cout << "Choose difficulty:" << endl;
    cout << "[1] Easy" << endl;
    cout << "[2] Medium" << endl;
    cout << "[3] Hard" << endl;
    cin >> difficulty;

    switch (difficulty) {
        case 1:
            student.Z = 70;
            student.P = 100;
            student.E = 100;
            student.K = 100;
            student.I = 0;
            break;
        case 2:
            student.Z = 50;
            student.P = 80;
            student.E = 80;
            student.K = 80;
            student.I = 0;
            break;
        case 3:
            student.Z = 35;
            student.P = 40;
            student.E = 60;
            student.K = 60;
            student.I = 0;
            break;
        default :
            cout << "Invalid input!";
            return;
    }

    int day = 1;

    while (day <= SESSION) {
        showStats();

        int option;
        cout << "What do you feel like doing today?" << endl;
        cout << "[1]Learn" << endl;
        cout << "[2]Eat(Duner mostly) " << endl;
        cout << "[3]Go out(chalgoteka preferably)" << endl;
        cout << "[4]Rest in peace" << endl;
        cout << "[5]Work" << endl;
        cout << "[6]Attend exam(when it is time)" << endl;
        cout << "[.]" << endl;
        cout << "[.]" << endl;
        cout << "[.]" << endl;
        cout << "[11]Exit game" << endl;
        cin >> option;

        switch (option) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 11:
                break;
            default:
                break;
        }

        day++;
    }

}

int main()
{
    int option;

    cout << "Welcome to Student City!" << endl;
    cout << "Choose your path:" << endl;
    cout << "[1] Start new game" << endl;
    cout << "[2] Load game from file" << endl;
    cin >> option;
    
    switch (option) {
        case 1:
            newGameLoop();
            break;
        case 2:
            loadGameLoop();
            break;
        default:
            cout << "Maybe if you failed entering simple number you are not ready for student city :(";
            break;
    }

    return 0;
}
