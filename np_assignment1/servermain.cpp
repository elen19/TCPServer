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
    if (sockFD == -1)
    {
        printf("Failed to creat socket\n");
    }

    freeaddrinfo(serverInfo); //Rensar serverInfo, bra safety

    while (true)
    {
        memset(clientMsg, 0, sizeof(clientMsg));
        memset(finalMsg, 0, sizeof(finalMsg));

        if (listen(sockFD, 1) == -1)
        {
            printf("No one is listening \nError: %s", strerror(errno));
            close(sockFD);
            exit(0);
        }
        else
        {
            printf("Listening on 127.0.0.1:%s\n", argv[1]);
        }

        if ((listenFD = accept(sockFD, (struct sockaddr*) & clientAddr, &clientAddr_len))== -1)
        {
            printf("Error accepting: %s \n", strerror(errno));
            continue;
        }
        printf("CLIENT CONNECTED!!\n Checking protocol\n");

        send(listenFD, protocol, strlen(protocol), 0);

        numBytes = recv(listenFD, clientMsg, clientMsgLen, 0);
        printf("Recieved %d bytes\n", numBytes);
        //Se till att clienten säger att det är "OK"
        if (strcmp(clientMsg, "OK\n") == 0)
        {
            printf("OK from client");
            
            char* oper = randomType();

            if (strchr(oper, 'f') != null)
            {
                //Här genereras floats
                for (int i = 0; i < 2; i++)
                {
                    fval[i] = randomFloat();
                    printf("[x]Value %d: %8.8g\n", i + 1, fval[i]);

                }

                sprintf(calcMsgFinal, "%s %8.8g %8.8g\n", oper, fval[0], fval[1]);
                //Här kollar vi vilken operand vi jobbar med, skriver ut den
                //och beräknar resultatet				
                if (strcmp(oper, "fadd") == 0)
                {
                    printf("Operation: Addition\n");
                    result = fval[0] + fval[1];
                }
                else if (strcmp(oper, "fsub") == 0)
                {
                    printf("Operation: Subraction\n");
                    result = fval[0] - fval[1];
                }
                else if (strcmp(oper, "fmul") == 0)
                {
                    printf("Operation: Multiplication\n");
                    result = fval[0] * fval[1];
                }
                else if (strcmp(oper, "fdiv") == 0)
                {
                    printf("Operation: Division\n");
                    result = fval[0] / fval[1];
                }
            }

        }

    }

}
