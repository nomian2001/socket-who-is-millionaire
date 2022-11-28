#ifndef QUESTION_OBJECT
#define QUESTION_OBJECT

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Dataset
{
private:
    string basePath = "dataset/template";
    int randomPosition;
    vector<string> listQuestion;
    vector<string> listAnswerQuestion;

public:
    // Read file from random number
    void readQuestionFile(int pos);
    void readAnswerFile(int pos);
    // Getter
    vector<string> getListQuestion();
    vector<string> getListAnswer();
    // Setter
    void setListQuestion(string str);
    void setListAnswer(string str);
};

#endif