#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "proto.h"
#include "server.h"

// Global variables
int server_sockfd = 0, client_sockfd = 0, client_number = 0, start_number = 0;
ClientList *root, *now;
QuestionNode* rootQuestion;

// Game function
void initialize_game()
{
//1
int idx1 = 1;
char question1[LENGTH_SEND] = "1. Declaring a pointer more than once may cause __";
char option1[LENGTH_SEND] = "1.Error ,2.Abort ,3.Trap ,4.Null ";
char correct_answer1[LENGTH_SEND] = "3.Trap ";
//1
int idx2 = 2;
char question2[LENGTH_SEND] = "2. An expression A.B in C++ means __";
char option2[LENGTH_SEND] = "1.A is member of object B ,2.B is member of Object A ,3.Product of A and B ,4.None of these ";
char correct_answer2[LENGTH_SEND] = "2.B is member of Object A ";
//1
int idx3 = 3;
char question3[LENGTH_SEND] = "3. __ function is used to allocate space for array in memory.";
char option3[LENGTH_SEND] = "1.malloc() ,2.realloc() ,3.alloc() ,4.calloc() ";
char correct_answer3[LENGTH_SEND] = "4.calloc() ";
//1
int idx4 = 4;
char question4[LENGTH_SEND] = "4. A pointer pointing to a variable that is not initialized is called __";
char option4[LENGTH_SEND] = "1.Void Pointer ,2.Null Pointer ,3.Empty Pointer ,4.Wild Pointer ";
char correct_answer4[LENGTH_SEND] = "2.Null Pointer ";



QuestionNode *np1 = newQuestionNode(idx1,question1,option1,correct_answer1);
QuestionNode *np2 = newQuestionNode(idx2,question2,option2,correct_answer2);
QuestionNode *np3 = newQuestionNode(idx3,question3,option3,correct_answer3);
QuestionNode *np4 = newQuestionNode(idx4,question4,option4,correct_answer4);
rootQuestion = np1;

np1->link = np2;
np2->link = np3;
np3->link = np4;

}

// 
void catch_ctrl_c_and_exit(int sig) {
    ClientList *tmp;
    while (root != NULL) {
        printf("\nClose socketfd: %d\n", root->data);
        close(root->data); // close all socket include server_sockfd
        tmp = root;
        root = root->link;
        free(tmp);
    }
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}

void send_to_all_clients(ClientList *np, char tmp_buffer[]) {
    ClientList *tmp = root->link;
    while (tmp != NULL) {
        if (np->data != tmp->data) { // all clients except itself.
            // printf("Send to sockfd (%d): \"%s\" \n", tmp->data, tmp_buffer); // debug
            send(tmp->data, tmp_buffer, LENGTH_SEND, 0);
        }
        tmp = tmp->link;
    }
}

//check nickname is exist or not 
int checkNicknameExist(char* nickname )
{
      ClientList *tmp = root->link;
    while (tmp != NULL) {
        if(strcmp(tmp->name,nickname)==0)
            return 1;
        tmp = tmp->link;
    }
    return 0;
}

// play game
void play_game( ClientList *player, QuestionNode * question)
{

 send(player->data, question->question, LENGTH_SEND, 0);

return;
}

//

void client_handler(void *p_client) {
    int leave_flag = 0;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientList *np = (ClientList *)p_client;
    ++client_number;

    // Check nickname is exist or not 
    if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || checkNicknameExist(nickname)) {
        send(np->data, "EXIT", LENGTH_SEND, 0);
        leave_flag = 1;
    } else {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("[%s][%s:%d](%d) join the chatroom.", np->name, np->ip,np->port, np->data);
        sprintf(send_buffer, "[%s][%s:%d](%d) join the chatroom.", np->name, np->ip,np->port, np->data);
        //send_to_all_clients(np, send_buffer);
        printf("Number Of Player: %d\n",client_number);
       
    }

    // Conversation
    while (1) {
        if (leave_flag) {
            break;
        }
        int receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
        if (receive > 0) {
            if (strlen(recv_buffer) == 0) {
                continue;
            }

            sprintf(send_buffer, "[%s]: %s [%s:%d]", np->name, recv_buffer, np->ip,np->port);
        } else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) {
            printf("[%s][%s:%d](%d) left the chatroom.\n", np->name, np->ip,np->port, np->data);
            sprintf(send_buffer, "[%s][%s:%d](%d) left the chatroom.\n", np->name, np->ip,np->port, np->data);
            leave_flag = 1;
        } else if(strcmp(recv_buffer, "game start") == 0)
        {
            ++start_number;
        }
        else {
            printf("Fatal Error: -1\n");
            leave_flag = 1;
        }
        //send_to_all_clients(np, send_buffer);
        printf("%s\n",send_buffer);

    }


    // Remove Node
    close(np->data);
    if (np == now) { // remove an edge node
        now = np->prev;
        now->link = NULL;
    } else { // remove a middle node
        np->prev->link = np->link;
        np->link->prev = np->prev;
    }
    free(np);
    --client_number;
}

int main()
{
    signal(SIGINT, catch_ctrl_c_and_exit);

    // Create socket
    server_sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sockfd == -1) {
        printf("Fail to create a socket.");
        exit(EXIT_FAILURE);
    }

    // Socket information
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(8888);

    // Bind and Listen
    bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
    listen(server_sockfd, 5);

    // Print Server IP
    getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Start Server on: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    // Initial linked list for clients
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr),ntohs(server_info.sin_port));
    now = root;
    
    initialize_game();
    while (1) {
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);

        // Print Client IP
        getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
        printf("Client %s:%d come in.\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        // Append linked list for clients
        ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr),ntohs(client_info.sin_port));
        c->prev = now;
        now->link = c;
        now = c;

        pthread_t id;
        if (pthread_create(&id, NULL, (void *)client_handler, (void *)c) != 0) {
            perror("Create pthread error!\n");
            exit(EXIT_FAILURE);
        }

    }

    return 0;
}