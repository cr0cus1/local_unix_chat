#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/server_socket"

int init_listen_socket() {
    int server_fd;
    int client_fd;
    struct sockaddr_un server_addr;
    char buff[1024];

    unlink(SOCKET_PATH);

    if((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        perror("socket");
    
    puts("Socket created!");
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);
    if(bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        perror("bind");

    if(listen(server_fd, 5) < 0)
        perror("listen");

    puts("Listening...");

    socklen_t server_addr_size = sizeof(server_addr);
    while((client_fd = accept(server_fd, (struct sockaddr *) &server_addr, &server_addr_size)) > 0) {
        memset(buff, 0, sizeof(buff));
        puts("Client connected!");

        read(client_fd, buff, sizeof(buff));
        printf("%s \n", buff);
    }

    return 0;
}

int main(int argc, char **argv) {
    if(init_listen_socket() < 0)
        perror("init listen socket");
    return 0;
}
