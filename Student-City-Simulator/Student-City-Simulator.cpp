/**
*
* Solution to course project #11
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Vladimir Pavlov
* @idnumber 8MI0600624
* @compiler VCC
*
* Contains the full implementation of the Student Quest game.
*
*/

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

const int SESSION_DAYS = 45;
const int EXAMS = 5;
const int PASS_SCORE = 75;
const int MAX = 100;
const int MIN = 0;

//|================UTILITY + STRUCTURES=====================|

struct Student
{
    int Z = 100; // Knowledge
    int P = 100; // Psyche
    int E = 100; // Energy
    int K = 100; // Money(cash) 
    int I = 0; // Exams(passed)
} student;

struct Game {
    int difficulty = 0;
    int day = 1;
    int examDays[EXAMS];
    int examNumber = 1;
    bool isRunning = true; // Checking if the game has ended
} game;

int randomInt(int min, int max) {
    int random = rand() % (max - min + 1) + min;

    return random;
}

void intToChar(int value, char buffer[], int& pos)
{
    char temp[10];
    int count = 0;

    if (value == 0)
    {
        buffer[pos++] = '0';
        return;
    }

    while (value > 0)
    {
        temp[count++] = char(value % 10 + '0');
        value /= 10;
    }

    for (int i = count - 1; i >= 0; i--)
    {
        buffer[pos++] = temp[i];
    }
}


// Takes a string array and displays it inside an ASCII frame for better visualization
void printFrame(const char text[][MAX], int count)
{
    int width = 0;

    for (int i = 0; i < count; i++)
    {
        int len = 0;
        while (text[i][len] != '\0')
        {
            len++;
        }

        if (len > width)
        {
            width = len;
        }
    }

    cout << "+";
    for (int i = 0; i < width + 2; i++)
    {
        std::cout << "-";
    }
    cout << "+" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << "| " << text[i];

        int len = 0;
        while (text[i][len] != '\0')
        {
            len++;
        }

        for (int j = 0; j < width - len + 1; j++)
        {
            cout << " ";
        }

        cout << "|" << endl;
    }

    cout << "+";
    for (int i = 0; i < width + 2; i++)
    {
        cout << "-";
    }
    cout << "+" << endl;
}


// After finishing the game save.txt file becomes empty
void clearSave() {
    ofstream file("save.txt");
    file << "";
    file.close();
}

// Making the game store the data in save.txt after every day
void autoSave() {
    ofstream file("save.txt");

    // Student data
    file << student.Z << '\n';
    file << student.P << '\n';
    file << student.E << '\n';
    file << student.K << '\n';
    file << student.I << '\n';

    // Game data
    file << game.difficulty << '\n';
    file << game.day << '\n';
    for (int i = 0; i < EXAMS; i++)
    {
        file << game.examDays[i] << ' ';
    }
    file << '\n';
    file << game.examNumber;
}

//|===========================UI-GAME-STATE===================================|

// Showing student statistics for every day 
void showStats() {
    char stats[5][MAX];

    // Day
    int pos = 0;
    const char dayText[] = "Day: ";

    for (int i = 0; dayText[i] != '\0'; i++)
    {
        stats[0][pos++] = dayText[i];
    }
    intToChar(game.day, stats[0], pos);

    const char outOf[] = " out of ";

    for (int i = 0; outOf[i] != '\0'; i++)
    {
        stats[0][pos++] = outOf[i];
    }
    intToChar(SESSION_DAYS, stats[0], pos);

    stats[0][pos] = '\0';

    // Money
    pos = 0;
    const char moneyText[] = "Money: ";

    for (int i = 0; moneyText[i] != '\0'; i++)
    {
        stats[1][pos++] = moneyText[i];
    }
    intToChar(student.K, stats[1], pos);

    stats[1][pos] = '\0';

    // Energy
    pos = 0;
    const char energyText[] = "Energy: ";

    for (int i = 0; energyText[i] != '\0'; i++)
    {
        stats[2][pos++] = energyText[i];
    }
    intToChar(student.E, stats[2], pos);

    stats[2][pos] = '\0';

    // Mentality
    pos = 0;
    const char mentalityText[] = "Mentality: ";

    for (int i = 0; mentalityText[i] != '\0'; i++)
    {
        stats[3][pos++] = mentalityText[i];
    }
    intToChar(student.P, stats[3], pos);

    stats[3][pos] = '\0';

    // Knowledge
    pos = 0;
    const char knowledgeText[] = "Knowledge: ";

    for (int i = 0; knowledgeText[i] != '\0'; i++)
    {
        stats[4][pos++] = knowledgeText[i];
    }
    intToChar(student.Z, stats[4], pos);

    stats[4][pos] = '\0';

    printFrame(stats, 5);
}

void win() {
    char win[][MAX] = {
        "CONGRATULATIONS!!!",
        "You successfully survived the",
        "exam session of your life!"
    };

    printFrame(win, 3);

    clearSave();

    game.isRunning = false; // Signalising the end of the game
}

void lose() {
    char lose[][MAX] = {
        "GAME OV3R!",
        "Due to your mental health and lack of knowledge",
        "you failed taking your exams,",
        "dropped out of university,",
        "became homeless and eventually died :-(",
        "Good luck next time!"
    };

    printFrame(lose, 6);

    clearSave();

    game.isRunning = false; // Signalising the end of the game
}

//|===========================GAME-CHECKS===================================|

bool isExamDay() {
    for (int i = 0; i < EXAMS; i++)
    {
        if (game.examDays[i] == game.day) {
            return true;
        }
    }

    return false;
}

// Checking whether the player's statistics are within valid limits
void checkCondition() {
    if (student.E <= MIN) {
        if (isExamDay()) {
            cout << "\nDue to lack of energy, you went unconscious!\n";

            student.E += 30;
            student.P -= 20;
            student.Z -= 20;
        }
        else {
            cout << "\nDue to lack of energy, you went unconscious and skipped a day!\n";

            game.day++;
            student.E += 40;
            student.P -= 10;
        }
    }
    if (student.K <= MIN) {
        cout << "\nYou spent all of your money and starved to death!\n";

        lose();
    }
    if (student.P <= MIN) {
        cout << "\nYou went insane and died!\n";

        lose();
    }
    if (student.Z < MIN) student.Z = MIN;
    if (student.E > MAX) student.E = MAX;
    if (student.K > MAX) student.K = MAX;
    if (student.P > MAX) student.P = MAX;
    if (student.Z > MAX) student.Z = MAX;
}

// Adding random events to introduce an element of luck
void randomEvent() {
    int random = randomInt(1, 100);

    if (random <= 30) {
        cout << "\nOh, a friend bought you a coffee!\n";
        student.P += 10;
    }
    else if (random <= 55) {
        cout << "\nMom and dad sent moneyyy$!\n";
        student.K += 20;
    }
    else if (random <= 75) {
        cout << "\nYou gambled your money playing belot with neighbors!\n";
        student.K -= 10;
        student.P -= 10;
    }
    else if (random <= 90) {
        cout << "\nYou are feeling sick!\n";
        student.E -= 20;
    }
    else {
        cout << "\nThe dorm just burned down, you are a bit homeless!\n";
        student.E -= 20;
        student.P -= 10;
        student.K -= 10;
    }
}

//|===========================PLAYER_ACTIONS===================================|

void learn() {
    int option;

    bool isDecided = false; // Looping till valid option
    
    while (!isDecided) {
        cout << "\nHow would you like to learn?\n" << endl;
        cout << "[1]Go to lectures" << endl;
        cout << "[2]Learn at home" << endl;
        cout << "[3]Learn with friends\n" << endl;
        cin >> option;

        // Checking input format
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Let's stick to entering a number.\n";
            continue;
        }

        switch (option) {
            case 1:
                cout << "\nYou went to lectures.\n";

                student.E -= 15;
                student.P -= 10;

                if (student.E >= 80) {
                    student.Z += 20;
                }
                else if (student.E <= 40) {
                    int random = randomInt(1, 100);

                    if (random <= 50) {
                        student.Z += 20;
                    }
                    else {
                        student.Z += 10;
                    }
                }
                else {
                    int random = randomInt(1, 100);

                    if (random <= 75) {
                        student.Z += 20;
                    }
                    else {
                        student.Z += 10;
                    }
                }
                isDecided = true;
                break;
            case 2:
                cout << "\nYou learned at home.\n";

                student.E -= 15;
                student.P -= 20;

                if (student.E >= 80) {
                    student.Z += 15;
                }
                else if (student.E <= 40) {
                    int random = randomInt(1, 100);

                    if (random <= 50) {
                        student.Z += 15;
                    }
                    else {
                        student.Z += 8;
                    }
                }
                else {
                    int random = randomInt(1, 100);

                    if (random <= 75) {
                        student.Z += 15;
                    }
                    else {
                        student.Z += 8;
                    }
                }
                isDecided = true;
                break;
            case 3:
                cout << "\nYou studied with friends.\n";

                student.E -= 15;

                if (student.E >= 80) {
                    student.Z += 5;
                    student.P += 10;
                }
                else if (student.E <= 40) {
                    int random = randomInt(1, 100);

                    if (random <= 50) {
                        student.Z += 5;
                        student.P += 10;
                    }
                    else {
                        student.P += 5;
                    }
                }
                else {
                    int random = randomInt(1, 100);

                    if (random <= 75) {
                        student.Z += 5;
                        student.P += 10;
                    }
                    else {
                        student.P += 5;
                    }
                }
                isDecided = true;
                break;
            default:
                cout << "\nInvalid option!\n" << endl;
                continue;
        }
    }
    
    // Adding chance for random event after player action
    int random = randomInt(1, 100);
    if (random <= 10) {
        cout << "\nYou overlearned and started hearing voices!\n";
        student.P -= 20;
    }
}

void eat() {
    cout << "\nYou went for the duner.\n";

    student.K -= 15;

    if (student.E >= 80) {
        student.E += 20;
        student.P += 5;
    }
    else if (student.E <= 40) {
        int random = randomInt(1, 100);

        if (random <= 50) {
            student.E += 20;
            student.P += 5;
        }
        else {
            student.E += 10;
        }
    }
    else {
        int random = randomInt(1, 100);

        if (random <= 75) {
            student.E += 20;
            student.P += 5;
        }
        else {
            student.E += 10;
        }
    }

    int random = randomInt(1, 100);
    if (random <= 15) {
        cout << "\nYou got 1kg mayonnaise extra for lunch!\n";
        student.E += 10;
    }
}

void sleep() {
    cout << "\nTime to take a nap.\n";

    student.E += 50;
    student.P += 10;

    // Adding chance for random event after player action
    int random = randomInt(1, 100);
    if (random <= 20) {
        cout << "\nYou overslept and missed a lecture!\n";
        student.Z -= 10;
    }
}

void goOut() {
    cout << "\nLet's go to chalgoteka.\n";

    student.E -= 15;
    student.Z -= 10;
    student.K -= 25;

    if (student.E >= 80) {
        student.P += 40;
    }
    else if (student.E <= 40) {
        int random = randomInt(1, 100);

        if (random <= 50) {
            student.P += 40;
        }
        else {
            student.P += 20;
        }
    }
    else {
        int random = randomInt(1, 100);

        if (random <= 75) {
            student.P += 40;
        }
        else {
            student.P += 20;
        }
    }

    // Adding chance for random event after player action
    int random = randomInt(1, 100);
    if (random <= 10) {
        cout << "\nHomeless man attacked and robbed you!\n";
        student.P -= 15;
        student.K -= 20;
    }
}

void work() {
    cout << "\nNobody likes working, but we have to eat.\n";

    student.E -= 20;
    student.P -= 15;
    student.Z -= 10;

    if (student.E >= 80) {
        student.K += 40;
    }
    else if (student.E <= 40) {
        int random = randomInt(1, 100);

        if (random <= 50) {
            student.K += 40;
        }
        else {
            student.K += 20;
        }
    }
    else {
        int random = randomInt(1, 100);

        if (random <= 75) {
            student.K += 40;
        }
        else {
            student.K += 20;
        }
    }

    // Adding chance for random event after player action
    int random = randomInt(1, 100);
    if (random <= 20) {
        cout << "\nYou returned leva instead of euro and got fined by NAP!\n";
        student.K -= 10;
    }
}

void attendExam() {
    cout << "\nGuess who has exam!\n";

    student.E -= 20;
    int penalty = (game.examNumber - 1) * 5;
    int luck = randomInt(1, 100);

    double success = (student.Z * 0.75) + (student.P * 0.1) + (student.E * 0.1) + (luck * 0.2) - penalty;

    if (success >= PASS_SCORE) {
        if (student.I == 4) {
            win();
        }
        else {
            student.I++;
            game.examNumber++;
            student.P += 20;
            student.E -= 20;
            student.Z -= 20;

            char pass[2][MAX];

            int pos = 0;
            const char msg1[] = "Congratulations!";

            for (int i = 0; msg1[i] != '\0'; i++)
            {
                pass[0][pos++] = msg1[i];
            }

            pass[0][pos] = '\0';

            // "You passed exam number X"
            pos = 0;
            const char msg2[] = "You passed exam number ";
            for (int i = 0; msg2[i] != '\0'; i++)
            {
                pass[1][pos++] = msg2[i];
            }

            // Adding exam number
            intToChar(student.I, pass[1], pos);
            pass[1][pos] = '\0';

            printFrame(pass, 2);
        }
    }
    else {
        char fail[2][MAX];

        int pos = 0;
        const char msg1[] = "Sorry!";

        for (int i = 0; msg1[i] != '\0'; i++)
        {
            fail[0][pos++] = msg1[i];
        }

        fail[0][pos] = '\0';

        // "You failed exam number X"
        pos = 0;
        const char msg2[] = "You failed exam number ";

        for (int i = 0; msg2[i] != '\0'; i++)
        {
            fail[1][pos++] = msg2[i];
        }

        // Adding exam number
        intToChar(game.examNumber, fail[1], pos);
        fail[1][pos] = '\0';

        printFrame(fail, 2);


        lose();
    }
}

//|===========================GAME-FLOW===================================|

void setDifficulty() {
    bool isDecided = false; // Looping till valid option

    int difficulty;

    do
    {
        cout << "\nChoose difficulty:\n" << endl;
        cout << "[1] Easy" << endl;
        cout << "[2] Medium" << endl;
        cout << "[3] Hard\n" << endl;
        cin >> difficulty;

        // Checking input format
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Let's stick to entering a number.\n";
            continue;
        }

        game.difficulty = difficulty;

        switch (game.difficulty) {
            case 1:
                isDecided = true;
                student.Z = 70;
                student.P = 100;
                student.E = 100;
                student.K = 100;
                student.I = 0;
                break;
            case 2:
                isDecided = true;
                student.Z = 50;
                student.P = 80;
                student.E = 80;
                student.K = 80;
                student.I = 0;
                break;
            case 3:
                isDecided = true;
                student.Z = 35;
                student.P = 40;
                student.E = 60;
                student.K = 60;
                student.I = 0;
                break;
            default:
                cout << "\nInvalid input!\n";
                break;
        }
    } while (!isDecided);  
}

// Starting new game - directly to main loop
void gameLoop() {
    // Checking whether this is a new game or a loaded save
    if (game.difficulty == 0) {
        setDifficulty();

        // Generating exam days
        game.examDays[0] = 8;
        game.examDays[1] = 17;
        game.examDays[2] = 26;
        game.examDays[3] = randomInt(27, 45);
        game.examDays[4] = 45;
    }

    while (game.day <= SESSION_DAYS) {
        checkCondition();

        if (!game.isRunning) {
            return;
        }

        showStats();

        bool isDecided = false; // Looping till valid option

        while (!isDecided)
        {
            int option;
            cout << "\nWhat do you feel like doing today?\n" << endl;
            cout << "[1]Learn" << endl;
            cout << "[2]Eat(Duner mostly) " << endl;
            cout << "[3]Go out(chalgoteka preferably)" << endl;
            cout << "[4]Rest in peace" << endl;
            cout << "[5]Work" << endl;
            cout << "[6]Attend exam(when it is time)" << endl;
            cout << "[.]" << endl;
            cout << "[.]" << endl;
            cout << "[.]" << endl;
            cout << "[11]Exit game\n" << endl;
            cin >> option;

            // Checking input format
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Let's stick to entering a number.\n";
                continue;
            }
   
            if (isExamDay() && option == 6) {
                attendExam();
                isDecided = true;
            }
            else if (!isExamDay() && option == 6) {
                cout << "\nNot so fast, its not your time yet!" << endl;
            } 
            else if (isExamDay() && option != 6) {
                cout << "\nSorry, but you have an exam!" << endl;
            }
            else {
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
                    case 11:
                        autoSave();
                        return;
                    default:
                        break;
                }
            }
        }

        // Second check condition to update the stats, so the random effect cause maximum changes 
        checkCondition();

        // Second check if the game has ended
        if (!game.isRunning) {
            return;
        }

        if (!isExamDay()) {
            randomEvent();
        }

        game.day++;

        autoSave();
    }

}

// Loading save.txt to continue previous attempt
void loadGame() {
    ifstream file("save.txt");

    if (!file) {
        cout << "File not found!\n" << endl;
        return;
    }

    // Student data
    file >> student.Z;
    file >> student.P;
    file >> student.E;
    file >> student.K;
    file >> student.I;

    // Game data
    file >> game.difficulty;
    file >> game.day;
    for (int i = 0; i < EXAMS; i++)
    {
        file >> game.examDays[i];
    }
    file >> game.examNumber;

    gameLoop();
}

int main()
{
    // Making random numbers as random as possible
    srand(time(NULL));

    int option;
    bool isDecided = false; // Looping till valid option

    cout << "Welcome to Student City Simulator!\n" << endl;

    do
    {
        cout << "Choose your path:\n" << endl;
        cout << "[1] Start new game" << endl;
        cout << "[2] Load game from file\n" << endl;
        cin >> option;

        // Checking input format
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Let's stick to entering a number.\n";
            continue;
        }

        switch (option) {
            case 1:
                isDecided = true;
                gameLoop();
                break;
            case 2:
                isDecided = true;
                loadGame();
                break;
            default:
                cout << "Maybe if you failed entering simple number you are not ready for student city :(\n";
                break;
        }
    } while (!isDecided);

    return 0;
}
