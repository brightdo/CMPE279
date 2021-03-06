// Server side C/C++ program to demonstrate Socket programming

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 80
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[102] = {0};
    char *hello = "Hello from server";
    
    printf("process running\n");
    
    if (argc == 1) { //if no params, run as parent
        printf("PARENT PROCESS STARTED\n");
        printf("execve=0x%p\n", execve);

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Attaching socket to port 80
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                    &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        if (fork() == 0) {
            // Child
            dup2(server_fd,2); // duplicate file handle so it can be accessed later

            char *const new_argv[] = {(char *) argv[0], "c"}; // new program argv
            char *const envp[] = {NULL}; // new program envp
            if(execve(argv[0], new_argv, envp) < 0 ){ // exec another copy of myself with added param
            	perror("execve failed\n" ); // notify upon failure
            }
        }
        else {
            printf("PARENT WAITING\n");
            wait(NULL); // wait for child process to finish
            printf("PARENT PROCESS TERMINATING\n");
        }
    }
    else if ((argc > 1)){ // if params passed, run as child
        printf("CHILD PROCESS STARTED AND LISTENING\n");
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( PORT );
        
        server_fd = 2; // previously made duplicate
	    
        // Forcefully attaching socket to the port 80
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
        }
        
        setuid(65534); // set to nobody uid @ 65534
        valread = read( new_socket , buffer, 1024);
        printf("%s\n",buffer );
        send(new_socket, hello , strlen(hello) , 0 );
        printf("Hello message sent\n");
        printf("CHILD PROCESS TERMINATING\n");
        exit(0);
    }
    return 0;
}

