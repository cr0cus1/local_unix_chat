#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFF 1024
#define SOCK_PATH "/tmp/server_socket" 

int init_client_socket() {
    int client_fd;
    struct sockaddr_un client_addr;

    if((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        perror("socket");

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strcpy(client_addr.sun_path, SOCK_PATH);

    if(connect(client_fd, (struct sockaddr *) &client_addr, sizeof(struct sockaddr_un)) < 0)
        perror("connect");
    
    return 0;
}
