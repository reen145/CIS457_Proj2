#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <wchar.h>
#include <locale.h>
#define PORT 8000
#define SIZE 4096
//Modified code from a tutorial on https://www.geeksforgeeks.org/socket-programming-cc/
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char msg[SIZE] = {0}; 
    char buffer[SIZE] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } else {
	printf("Connection Established, type 'QUIT' to terminate\n You message first!\n");
    } 
    while(strcmp(msg,"QUIT") != 0) {
	fgets(msg,SIZE,stdin);
	msg[strlen(msg)-1] = '\0';
    	send(sock , msg , strlen(msg) , 0 );

    	valread = read( sock , buffer, SIZE); 
    	printf("%s\n",buffer );
	bzero(buffer,SIZE);
    }
    return 0; 
}
