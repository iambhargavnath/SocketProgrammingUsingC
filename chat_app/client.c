// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
  
int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char hello[1024];
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))< 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    while(1)
    {
    valread = read(client_fd, buffer, 1024);
    printf("Server msg%s\n", buffer);
    int val=strcmp(buffer,"BYE");
    printf("\nstrcmp: %d\n",val);
    if(val==0)
    break;
    printf("\nEnter the msg to send");
    gets(hello);
    write(client_fd, hello, strlen(hello));
    }
    // closing the connected socket
    close(client_fd);
    return 0;
}