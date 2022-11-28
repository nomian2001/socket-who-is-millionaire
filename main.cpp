#include <iostream>
#include "entities/question.object.h"

using namespace std;

int main()
{
    cout << "Hello" << endl;
    Dataset data;
    data.readFile(1);
    vector<string> listQuestion = data.getListQuestion();

    for (int i = 0; i < listQuestion.size(); i++)
    {
        cout << listQuestion[i] << endl;
    }

    return 0;
}