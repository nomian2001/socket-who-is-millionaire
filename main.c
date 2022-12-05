// this just for testing 

// #include <stdio.h>

// int main() {
//     char c;
//     printf("Enter a character: ");
//     scanf("%c", &c);

//     if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
//         printf("%c is an alphabet.", c);
//     else
//         printf("%c is not an alphabet.", c);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEND_LENGTH 1000
typedef struct QuestionNode {
    struct QuestionNode* prev;
    struct QuestionNode* link;
    int idx;
    char question[SEND_LENGTH];
    char option[SEND_LENGTH];
    char correct_answer[SEND_LENGTH];
} QuestionNode;


QuestionNode *newQuestionNode(int idx,char*question, char*option, char*correct_answer)
{
QuestionNode *np = (QuestionNode *)malloc( sizeof(QuestionNode) );
    np->idx = idx;
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->question, question, SEND_LENGTH);
    strncpy(np->option, option, SEND_LENGTH);
    strncpy(np->correct_answer, correct_answer, SEND_LENGTH);
    return np;
}

void play_game()
{
    
}


int main()
{
int idx = 1;
char question[SEND_LENGTH] = "1. Declaring a pointer more than once may cause __";
char option[SEND_LENGTH] = "1.Error ,2.Abort ,3.Trap ,4.Null ";
char correct_answer[SEND_LENGTH] = "3.Trap ";
QuestionNode *root;
QuestionNode *np = newQuestionNode(idx,question,option,correct_answer);

printf("idx: %d\n\n",np->idx);
printf("question: %s\n\n",np->question);
printf("option: %s\n\n",np->option);
printf("correct_answer: %s\n\n",np->correct_answer);


    return 0;
}