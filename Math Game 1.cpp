// Math Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

enum enLevel { Hard = 1, Med = 2, easy = 3, Mixlevel = 4 };
enum enOperationType { Add = 1, Subtract = 2, Devide = 3, MultiPly = 4, Mix = 5 };
enum enIsCorrect{correct=1,wrong=0};
enum enIsPass{Pass=1,NotPass=0};


struct strQuestion {
    enLevel level;
    enOperationType OperationTyp;
    enIsCorrect IsCorrect;
    int N1;
    int N2;
    int UserAnswer;
    int CorrectAnswer;
};

struct strQuize {
    strQuestion Questions[100];
    int NumberOfCorrectAnswers;
    int NumberOfWrongAnswers;
    enIsPass IsPass;
};

enIsPass IsPass(strQuize &Quize) {
    if (Quize.NumberOfCorrectAnswers > Quize.NumberOfWrongAnswers) {
        return Quize.IsPass = enIsPass::Pass;
    }
    else {
        return Quize.IsPass = enIsPass::NotPass;
    }
}
int RandomNumber(int from, int to) {
    return rand() % (to - from + 1) + from;
}
enOperationType ReadOperationType() {
    int operationType;
    cout << "Please enter the operation Type: Add[1] Subtract[2] Devide[3] Multiply[4] Mix[5]\n";
    cin >> operationType;
    if (enOperationType(operationType) == enOperationType::Mix) 
    {
        return enOperationType(RandomNumber(1, 4));
    }
    else {
        return enOperationType(operationType);
    }
}
enLevel ReadLevel() {
    int Level;
    cout << "Please enter the levle: Hard[1] Med[2] easy[3] Mix[4]\n";
    cin >> Level;
    if (enLevel(Level) == enLevel::Mixlevel) {
        return enLevel(RandomNumber(1, 3));
    }
    else {
        return enLevel(Level);
    }
}



int generateRandomNumber(enLevel level) {
    if (level == enLevel::easy) {
        return RandomNumber(1, 15);
    }
    else if (level == enLevel::Med) {
        return RandomNumber(15, 30);
    }
    else if (level == enLevel::Hard) {
        return RandomNumber(30, 100);
    }
}


int ReadUserAnswer() {
    int UserAnswer;
    cin >> UserAnswer;
    return UserAnswer;
}
void GenerateOperation(enOperationType OperationType, int N1, int N2) {
    if (OperationType == enOperationType::Add) {
        cout << N1
            << endl<<" + \n"
            << N2
            << "\n----\n\n";
    }
    else if (OperationType == enOperationType::Subtract) {
        cout << N1
            << endl<<"-\n"
            << N2
            << "\n----\n";

    }
    else if (OperationType == enOperationType::MultiPly) {
        cout << N1
            << endl<<"*\n"
            << N2
            << "\n----\n";

    }
    else if (OperationType == enOperationType::Devide) {
        cout << N1
            << endl<<"/\n"
            << N2
            << "\n----\n";
    }
}
int GetCorrectAnswer(enOperationType OperationType, int N1, int N2) {
    int correctAnswer;
    if (OperationType == enOperationType::Add) {
        correctAnswer = N1 + N2;
    }
    else if (OperationType == enOperationType::Subtract) {
        correctAnswer = N1 - N2;
    }
    else if (OperationType == enOperationType::MultiPly) {
        correctAnswer = N1 * N2;
    }
    else if (OperationType == enOperationType::Devide) {
        correctAnswer = N1 / N2;
    }
    return correctAnswer;
}
void IsCorrect(int UserAnswer, int correctAnswer,int& correctTimes,int &wrongTimes) {
    if (UserAnswer == correctAnswer) {
        system("color 2F");
        cout << "\n your answer is correct :-) \n";
        correctTimes++;
    }
    else if (UserAnswer != correctAnswer) {
        system("color 4F");
        cout << "\nYour answer is not correct :-( \n";
        cout << "\nThe correct Answer is : " << correctAnswer << "\n";
        wrongTimes++;
    }
}
int HowManyQuestions() {
    int NumberOfQuestions;
    cout << "please enter the number of Questions: \n";
    cin >> NumberOfQuestions;
    return NumberOfQuestions;
}

void PrintFinalResults(strQuize &Quize) {
    cout << "\n\n---------------Game Over-------------------\n\n";
    cout << "\nNumber Of correct answers: " << Quize.NumberOfCorrectAnswers<<"\n";
    cout << "\nNumber Of wrong answers: " << Quize.NumberOfWrongAnswers << "\n";
    if (IsPass(Quize)== enIsPass::Pass) {
        cout << "\nCongrats, You have Passed !!\n";
    }
    else if (IsPass(Quize) == enIsPass::NotPass) {
        cout << "\n You have failed !!\n";
    }
}

void PlayGame(int NumberOfQuestion,strQuize &Quize) {
    
    enLevel level = ReadLevel();
    enOperationType OperationType = ReadOperationType();

    Quize.NumberOfCorrectAnswers=0;
    Quize.NumberOfWrongAnswers=0;


    for (int i = 1; i <= NumberOfQuestion; i++) {
        int N1 = generateRandomNumber(level);
        int N2 = generateRandomNumber(level);
        GenerateOperation(OperationType, N1, N2);
        Quize.Questions->UserAnswer = ReadUserAnswer();
        Quize.Questions->CorrectAnswer = GetCorrectAnswer(OperationType, N1, N2);
        IsCorrect(Quize.Questions->UserAnswer, Quize.Questions->CorrectAnswer, Quize.NumberOfCorrectAnswers, Quize.NumberOfWrongAnswers);
    }
    PrintFinalResults(Quize);
}
void ResetScreen() {
    system("cls");
    system("color 0F");
}
void StartGame() {
    char PlayAgain;
    strQuize Quize;
    do {
        ResetScreen();
        PlayGame(HowManyQuestions(), Quize);

        cout << "\n Do you want to Play Again: Yes[Y] No[N]\n";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
    //Seed Random called only once
    srand(time(NULL));

    StartGame();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
