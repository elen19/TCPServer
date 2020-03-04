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
    socklen_t clientAddr_len = sizeOf(clientResult);
}
