#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>
#include <time.h>


int main(int argc, char* argv[]) {

    /* 
        Note: 
            This will be taking place in localhost of the network that the computer is connected to!
            The format of the starting the server should be:
            secret-squirrel$./server <port_number>
    */

   if (argc != 2) {
    perror("Invalid format. Please try './server <port_number>' \n");
    return 1;
   }

    FILE* log = fopen("distance_log.txt", "w");
    if (!log) {
        perror("Failed to open or create the distance log");
        return 6;
    }

    // Take in the port number
    const int PORT = atoi(argv[1]);

    // Create a socket 
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Unable to create socket. Closing the socket");
        return 2;
    }

    // Set the sockaddr
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(""); // Put your ip address here. Example: "192.168.1.1" <-- do not actually use this! LOL

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind socket");
        return 4;
    }

    // Only arduino
    if (listen(server_socket, 1) < 0) {
        perror("Failed to listen on socket");
        return 5;
    }

    printf("Server listening on port %d\n", PORT);


    int client_socket;
    while(1) {

        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Failed to accept client connection\n");
            continue;
        }

        char buffer[13];
        // Receive Data
        while(1){
            ssize_t message = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
            if (message > 0) {
                buffer[message] = '\0';

                // Get current time
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                char timestamp[100];
                strftime(timestamp, sizeof(timestamp)-1, "[%Y-%m-%d %H:%M:%S]", t);

                // Log the timestamp and received data
                fprintf(log, "%s %s\n", timestamp, buffer);
                fflush(log);
            } else if (message == 0) {
                printf("Client disconnected.\n");
                break;
            }
        }
        close(client_socket);
    }

    // Close the log file once done
    fclose(log);
    return 0;
}