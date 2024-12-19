
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.178.48"
#define SERVER_PORT 5111
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return -1;
    }

    printf("Connected to %s:%d\n", SERVER_IP, SERVER_PORT);

    // Loop for user input and sending messages
    while (1) {
        printf("-> ");
        if (fgets(message, sizeof(message), stdin) != NULL) {
            // Remove the newline character from the message
            message[strcspn(message, "\n")] = 0;

            // Send message to the server
            if (send(sock, message, strlen(message), 0) < 0) {
                perror("Send failed");
                break;
            }
        }
    }

    // Close the socket
    close(sock);
    return 0;
}
