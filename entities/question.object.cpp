#include "question.object.h"

void Dataset::readQuestionFile(int pos)
{
    fstream file;
    string line;
    file.open(basePath + to_string(pos) + "/questions.txt");
    cout << basePath + to_string(pos) + "/questions.txt" << endl;
    while (getline(file, line))
    {
        Dataset::setListQuestion(line);
    }
}

void Dataset::readAnswerFile(int pos)
{
    fstream file;
    string line;
    file.open(basePath + to_string(pos) + "/answers.txt");
    cout << basePath + to_string(pos) + "/answers.txt" << endl;
    while (getline(file, line))
    {
        Dataset::setListAnswer(line);
    }
}

// Setter
void Dataset::setListQuestion(string str)
{
    Dataset::listQuestion.push_back(str);
};

void Dataset::Dataset::setListAnswer(string str)
{
    Dataset::listAnswerQuestion.push_back(str);
};

// Getter
vector<string> Dataset::getListQuestion()
{
    return Dataset::listQuestion;
};
vector<string> Dataset::getListAnswer()
{
    return Dataset::listAnswerQuestion;
};
