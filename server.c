
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 5111
#define BUFFER_SIZE 1024

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Reuse address in case of address reuse error
    int opt = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Set socket option failed");
        close(server_sock);
        return -1;
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all available network interfaces

    // Bind the socket to the IP and port
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_sock, 5) < 0) {
        perror("Listen failed");
        close(server_sock);
        return -1;
    }

    printf("Server started. Waiting for connection...\n");

    // Accept an incoming connection
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock < 0) {
        perror("Accept failed");
        close(server_sock);
        return -1;
    }

    printf("Connection from: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Receive and print messages from client
    while (1) {
        ssize_t bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            break; // Connection closed or error
        }

        buffer[bytes_received] = '\0'; // Null-terminate the string
        printf("Received: %s\n", buffer);
    }

    printf("Disconnected. Exiting.\n");

    // Close the client and server sockets
    close(client_sock);
    close(server_sock);
    
    return 0;
}
