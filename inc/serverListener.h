#ifndef SERVER_LISTENER_H
#define SERVER_LISTENER_H

char* readFromSocket(int connfd);

char* initServerListener(int portNum);


#endif