#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int SESSION_DAYS = 45;
const int MAX = 100;

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

int randomInt(int min, int max) {
    int random = rand() % (max - min + 1) + min;

    return random;
}

void learn() {
    int option;

    cout << "How would you like to learn?" << endl;
    cout << "[1]Go to lectures" << endl;
    cout << "[2]Learn at home" << endl;
    cout << "[3]Learn with friends" << endl;
    cin >> option;

    bool isDecided = false;

    while (!isDecided) {
        switch (option) {
        case 1:
            student.E -= 10;
            student.P -= 10;

            if (student.E >= 80) {
                student.Z += 20;

                if (student.Z > MAX) student.Z = MAX;
            }
            else if (student.E <= 40) {
                int random = randomInt(1, 2);

                if (random == 1) {
                    student.Z += 20;

                    if (student.Z > MAX) student.Z = MAX;
                }
                else {
                    student.Z += 10;

                    if (student.Z > MAX) student.Z = MAX;
                }
            }
            else {
                int random = randomInt(1, 4);

                if (random != 1) {
                    student.Z += 20;

                    if (student.Z > MAX) student.Z = MAX;
                }
                else {
                    student.Z += 10;

                    if (student.Z > MAX) student.Z = MAX;
                }
            }
            isDecided = true;
            break;
        case 2:
            student.E -= 15;
            student.P -= 20;

            if (student.E >= 80) {
                student.Z += 15;

                if (student.Z > MAX) student.Z = MAX;
            }
            else if (student.E <= 40) {
                int random = randomInt(1, 2);

                if (random == 1) {
                    student.Z += 15;

                    if (student.Z > MAX) student.Z = MAX;
                }
                else {
                    student.Z += 8;

                    if (student.Z > MAX) student.Z = MAX;
                }
            }
            else {
                int random = randomInt(1, 4);

                if (random != 1) {
                    student.Z += 15;

                    if (student.Z > MAX) student.Z = MAX;
                }
                else {
                    student.Z += 8;

                    if (student.Z > MAX) student.Z = MAX;
                }
            }
            isDecided = true;
            break;
        case 3:
            student.E -= 10;

            if (student.E >= 80) {
                student.Z += 5;
                student.P += 10;

                if (student.Z > MAX) student.Z = MAX;
                if (student.P > MAX) student.P = MAX;
            }
            else if (student.E <= 40) {
                int random = randomInt(1, 2);

                if (random == 1) {
                    student.Z += 5;
                    student.P += 10;

                    if (student.Z > MAX) student.Z = MAX;
                    if (student.P > MAX) student.P = MAX;
                }
                else {
                    student.P += 5;

                    if (student.P > MAX) student.P = MAX;
                }
            }
            else {
                int random = randomInt(1, 4);

                if (random != 1) {
                    student.Z += 5;
                    student.P += 10;

                    if (student.Z > MAX) student.Z = MAX;
                    if (student.P > MAX) student.P = MAX;
                }
                else {
                    student.P += 5;

                    if (student.P > MAX) student.P = MAX;
                }
            }
            isDecided = true;
            break;
        default:
            cout << "Invalid option!" << endl;
            break;
        }
    }

    //add chance for random effect
}

void eat() {
    student.K -= 10;

    if (student.E >= 80) {
        student.E += 20;
        student.P += 5;

        if (student.E > MAX) student.E = MAX;
        if (student.P > MAX) student.P = MAX;
    }
    else if (student.E <= 40) {
        int random = randomInt(1, 2);

        if (random == 1) {
            student.E += 20;
            student.P += 5;

            if (student.E > MAX) student.E = MAX;
            if (student.P > MAX) student.P = MAX;
        }
        else {
            student.E += 10;

            if (student.E > MAX) student.E = MAX;
        }
    }
    else {
        int random = randomInt(1, 4);

        if (random != 1) {
            student.E += 20;
            student.P += 5;

            if (student.E > MAX) student.E = MAX;
            if (student.P > MAX) student.P = MAX;
        }
        else {
            student.E += 10;

            if (student.E > MAX) student.E = MAX;
        }
    }

    //add chance for random effect
}

void sleep() {
    student.E += 50;
    student.P += 10;

    if (student.E > MAX) student.E = MAX;
    if (student.P > MAX) student.P = MAX;

    //add chance for random effect
}

void goOut() {
    student.E -= 15;
    student.K -= 25;

    if (student.E >= 80) {
        student.P += 40;

        if (student.P > MAX) student.P = MAX;
    }
    else if (student.E <= 40) {
        int random = randomInt(1, 2);

        if (random == 1) {
            student.P += 40;

            if (student.P > MAX) student.P = MAX;
        }
        else {
            student.P += 20;

            if (student.P > MAX) student.P = MAX;
        }
    }
    else {
        int random = randomInt(1, 4);

        if (random != 1) {
            student.P += 40;

            if (student.P > MAX) student.P = MAX;
        }
        else {
            student.P += 20;

            if (student.P > MAX) student.P = MAX;
        }
    }
}

void work() {
    student.E -= 20;
    student.P -= 10;

    if (student.E >= 80) {
        student.K += 40;

        if (student.K > MAX) student.K = MAX;
    }
    else if (student.E <= 40) {
        int random = randomInt(1, 2);

        if (random == 1) {
            student.K += 40;

            if (student.K > MAX) student.K = MAX;
        }
        else {
            student.K += 20;

            if (student.K > MAX) student.K = MAX;
        }
    }
    else {
        int random = randomInt(1, 4);

        if (random != 1) {
            student.K += 40;

            if (student.K > MAX) student.K = MAX;
        }
        else {
            student.K += 20;

            if (student.K > MAX) student.K = MAX;
        }
    }
}

void attendExam(int examNumber) {
    student.E -= 20;
    int penalty = (examNumber - 1) * 5;
    int luck = randomInt(1, 100);

    double success = (student.Z * 0.75) + (student.P * 0.1) + (student.E * 0.1) + (luck * 0.2) - penalty;

    if (success >= 75) {
        if (student.I == 4) {
            win();
        }
        else {
            student.I++;
            game.examNumber++;
            student.P += 20;
            student.E -= 20;

            if (student.P > MAX) student.P = MAX;
        }
    }
    else {
        student.P -= 30;
        student.E -= 20;
    }
}

void checkCondition() {

}

void exitGame() {

}

void autoSave() {

}

void win() {

}

void lose() {

}

void setDifficulty() {
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
    default:
        cout << "Invalid input!";
        return;
    }
}

// Зареждане на игра от файл
void loadGameLoop() {

}

// Започване на нова игра
void newGameLoop() {
    setDifficulty();

    game.day = 1;
    game.examNumber = 1;

    while (game.day <= SESSION_DAYS) {
        showStats();

        int isDecided = false;

        while (!isDecided)
        {
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
                learn();
                isDecided = true;
                break;
            case 2:
                eat();
                isDecided = true;
                break;
            case 3:
                goOut();
                isDecided = true;
                break;
            case 4:
                sleep();
                isDecided = true;
                break;
            case 5:
                work();
                isDecided = true;
                break;
            case 6:
                attendExam(game.examNumber);
                isDecided = true;
                break;
            case 11:
                exitGame();
                isDecided = true;
                break;
            default:
                break;
            }
        }

        checkCondition();

        game.day++;

        autoSave();
    }

}

int main()
{
    srand(time(NULL));

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
