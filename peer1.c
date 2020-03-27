#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <wchar.h>
#include <locale.h>
#define PORT 8000
#define SIZE 4096
//Code modified from a tutorial on https://www.geeksforgeeks.org/socket-programming-cc/
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[SIZE] = {0}; 
    char msg[SIZE] = {0}; 
       
    // Creating socket file descriptor with IPv4 and TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8000
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } else {
	printf("Connection Established, type 'QUIT' to terminate\n");
    }
    while(strcmp(msg,"QUIT") != 0) {
    	valread = read( new_socket , buffer, SIZE); 
    	printf("%s\n",buffer );
	bzero(buffer,SIZE);

	fgets(msg,SIZE,stdin);
	msg[strlen(msg)-1] = '\0';
    	send(new_socket , msg , sizeof(msg) , 0 );  
    }
    return 0; 
}
