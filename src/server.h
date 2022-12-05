#ifndef LIST
#define LIST
#include "proto.h"
typedef struct ClientNode {
    int data;
    struct ClientNode* prev;
    struct ClientNode* link;
    char ip[16];
    char name[31];
    int port;
    int num_correct_answers;
} ClientList;

ClientList *newNode(int sockfd, char* ip, int port) {
    ClientList *np = (ClientList *)malloc( sizeof(ClientList) );
    np->data = sockfd;
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->ip, ip, 16);
    strncpy(np->name, "NULL", 5);
    np->port = port;
    np->num_correct_answers = 0;
    return np;
}
/// @brief /////////////////////////
typedef struct QuestionNode {
    struct QuestionNode* prev;
    struct QuestionNode* link;
    int idx;
    char question[LENGTH_SEND];
    char option[LENGTH_SEND];
    char correct_answer[LENGTH_SEND];
} QuestionNode;


QuestionNode *newQuestionNode(int idx,char*question, char*option, char*correct_answer)
{
QuestionNode *np = (QuestionNode *)malloc( sizeof(QuestionNode) );
    np->idx = idx;
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->question, question, LENGTH_SEND);
    strncpy(np->option, option, LENGTH_SEND);
    strncpy(np->correct_answer, correct_answer, LENGTH_SEND);
    return np;
}

#endif // LIST