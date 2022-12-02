#ifndef LIST
#define LIST

typedef struct ClientNode {
    int data;
    struct ClientNode* prev;
    struct ClientNode* link;
    char ip[16];
    char name[31];
    int port;
} ClientList;

ClientList *newNode(int sockfd, char* ip, int port) {
    ClientList *np = (ClientList *)malloc( sizeof(ClientList) );
    np->data = sockfd;
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->ip, ip, 16);
    strncpy(np->name, "NULL", 5);
    np->port = port;
    return np;
}

#endif // LIST