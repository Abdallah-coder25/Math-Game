#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;

enum eQuestionLevel{
    Easy = 1,
    Med,
    Hard,
    MixLevel
};
enum eQuestionType{
    Add = 1,
    Sub,
    Mul,
    Div,
    MixType
};
struct sQuestion{
    short QuestionNumber = 0;
    short Number1 = 0;
    short Number2 = 0;
    eQuestionType Type;
    eQuestionLevel Level;
    short UserAnswer = 0;
    short Result = 0;
    bool IsCorrect = false;
};
struct sFinalResult{
    short NumberOfQuestions = 0;
    eQuestionLevel Level;
    eQuestionType Type;
    short RightAnswers = 0;
    short WrongAnswers = 0;
};
short RandomNumber(short from, short to){
    return rand() % (to - from + 1) + from;
}
short ReadNumberOfQuestions(){
    short NumberOfQuestions;
    do {
        cout << "How many questions do you want to play (1 to 10)?: ";
        while (true) {
            cin >> NumberOfQuestions;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number!\n";
            } else
                break;
        }
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions;
}
eQuestionLevel ReadQuestionLevel(){
    short Level;
    do {
        cout << "\nPlease choose level of questions? [1]Easy, [2]Med, [3]Hard, [4]Mix: ";
        while (true) {
            cin >> Level;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number!\n";
            } else
                break;
        }
    } while (Level < 1 || Level > 4);
    return (eQuestionLevel)Level;
}
eQuestionType ReadQuestionType(){
    short Type;
    do {
        cout << "\nPlease choose the type of question: [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix: ";
        while (true) {
            cin >> Type;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number!\n";
            } else
                break;
        }
    } while (Type < 1 || Type > 5);
    return (eQuestionType)Type;
}
short Calculate(short Number1, short Number2, char Operation){
    switch (Operation) {
        case Add: return Number1 + Number2;
        case Sub: return Number1 - Number2;
        case Mul: return Number1 * Number2;
        case Div: return Number1 / Number2;
        default: return 0;
    }
}
char GetOperationSymbol(eQuestionType Type){
    switch (Type) {
        case Add: return '+';
        case Sub: return '-';
        case Mul: return '*';
        case Div: return '/';
        default: return '+';
    }
}
eQuestionType GenerateRandomType(){
    return (eQuestionType)RandomNumber(1, 4);
}
eQuestionLevel GenerateRandomLevel(){
    return (eQuestionLevel)RandomNumber(1, 3);
}
short GenerateNumberForLevel(eQuestionLevel Level){
    switch (Level) {
        case Easy: return RandomNumber(1, 20);
        case Med: return RandomNumber(21, 50);
        case Hard: return RandomNumber(51, 100);
        case MixLevel: return RandomNumber(1, 100);
        default: return RandomNumber(1, 20);
    }
}
void ShowAnswerResult(bool IsCorrect, short CorrectAnswer){
    if (IsCorrect) {
        cout << "\nRight answer :-)\n";
        system("color 02");
    } else {
        cout << "\nWrong answer (-:\n";
        cout << "The correct answer is: " << CorrectAnswer << endl;
        system("color 04");
    }
    cout << "\033[0m";
}
short ReadUserAnswer(short Number1, short Number2, eQuestionType Operation){
    short Answer;
    cout << "\nNumber1: " << Number1 << endl;
    cout << " Number2: " << Number2;
    cout << " " << GetOperationSymbol(Operation);
    cout << "\n------------------------";
    cin >> Answer;
    return Answer;
}
sQuestion GenerateQuestion(eQuestionLevel Level, eQuestionType Type){
    sQuestion Question;
    Question.Level = (Level == MixLevel) ? GenerateRandomLevel() : Level;
    Question.Type = (Type == MixType) ? GenerateRandomType() : Type;
    Question.Number1 = GenerateNumberForLevel(Level);
    Question.Number2 = GenerateNumberForLevel(Level);
    Question.Result = Calculate(Question.Number1, Question.Number2, Question.Type);
    Question.UserAnswer = ReadUserAnswer(Question.Number1, Question.Number2, Question.Type);
    Question.IsCorrect = (Question.Result == Question.UserAnswer);
    ShowAnswerResult(Question.IsCorrect, Question.Result);
    return Question;
}
sFinalResult PlayGame(short NumberOfRounds, eQuestionLevel Level, eQuestionType Type){
    sFinalResult Result;
    Result.NumberOfQuestions = NumberOfRounds;
    Result.Level = Level;
    Result.Type = Type;
    for (short i = 1; i <= NumberOfRounds; i++) {
        cout << "\nQuestion [" << i << "/" << NumberOfRounds << "]\n";
        sQuestion Question = GenerateQuestion(Level, Type);
        if (Question.IsCorrect)
            Result.RightAnswers++;
        else
            Result.WrongAnswers++;
    }
    return Result;
}
string GetPassOrFail(sFinalResult Result){
    if (Result.RightAnswers > Result.WrongAnswers){
        system("color 2");
        return "Pass";
    }
    else if (Result.WrongAnswers > Result.RightAnswers){
        system("color 4");
        return "Fail";
    }
    else{
        system("color 6");
        return "Draw";
    }
}
void PrintFinalResult(sFinalResult Result){
    cout << "\n\t\t----------------------------\n";
    cout << "\t\tFinal Result is: " << GetPassOrFail(Result) << endl;
    cout << "\n\t\t----------------------------\n";
    cout << "\t\tNumber of questions     : " << Result.NumberOfQuestions << endl;
    cout << "\t\tQuestion level          : " << Result.Level << endl;
    cout << "\t\tOperation type          : " << Result.Type << endl;
    cout << "\t\tNumber of right answers : " << Result.RightAnswers << endl;
    cout << "\t\tNumber of wrong answers : " << Result.WrongAnswers << endl;
    cout << "\t\t----------------------------\n";
}
void StartGame(){
    char Again = ' ';
    do {
        system("cls");
        system("color 0F");
        short Number = ReadNumberOfQuestions();
        eQuestionLevel Level = ReadQuestionLevel();
        eQuestionType Type = ReadQuestionType();
        sFinalResult Result = PlayGame(Number, Level, Type);
        PrintFinalResult(Result);
        cout << "Do you want to play again? ";
        cin >> Again;
    } while (Again == 'y' || Again == 'Y');
}
int main(){
    srand(time(0));
    StartGame();
    system("pause");
    return 0;
}
