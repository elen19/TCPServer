#include <stdio.h>
#include <stdlib.h>
/* You will to add includes here */
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
// Included to get the support library
#include <calcLib.h>

#define PORT "9034"

using namespace std;

int initCalcLib(void);
int randomInt(void);
double randomFloat(void);
char* randomType(void);
const double ROUNDING = 0.001;

int main(int argc, char *argv[]){
  
    if (argc < 2)
    {
        printf("Too few arguments\nExpected: <port>");
        exit(0);
    }
    
    initCalcLib();
    struct addrinfo guide, * serverInfo, * p;
    uint16_t numBytes;
    uint16_t sockFD;
    uint16_t listenFD;
    uint8_t returnValue;

    double dval[2];
    double results;
    double clientResult;

    struct sockaddr_in clientAddr;
    socklen_t clientAddr_len = sizeof(clientResult);

    char finalMsg[80];
    char protocol[15] = "Text TCP 1.0\n";

    char clientMsg[100];  
    int clientMsgLen = sizeof(clientMsg);

    memset(&guide, 0, sizeof(guide));

    guide.ai_family = AI_INET;
    guide.ai_sockettype = SOCK_STREAM;
    guide.ai_flags = AI_PASSIVE;

    if ((returnValue = getaddrinfo(NULL, argv[1], &guide, &serverInfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(returnValue));
        exit(0);
    }

    for (p = serverInfo; p != NULL; p = p->ai_next)
    {
        if ((sockFD = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol)) == -1)
        {
            printf("listener: socket: %s\n", gai_strerror(errno));
            continue;
        }
        if (bind(sockFD, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockFD);
            printf("listener error: bind: %s\n", gai_strerror(errno));
            continue;
        }
        break;
    }
}
