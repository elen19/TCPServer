#include <stdio.h>
#include <stdlib.h>
/* You will to add includes here */
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
// Included to get the support library
#include <calcLib.h>

#define PORT "9034"

using namespace std;

void* get_in_addr(struct sockaddr* sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
}

int main(int argc, char *argv[]){
  
  /* Do more magic */
  

}
