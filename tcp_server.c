#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int server_socket;
    struct sockaddr_in server_address;

    char server_message[255] = "The server received your request.";

    // 0 means a usage of the default protocol (TCP)
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_socket, 1);

    // 2nd and 3rd arguments are a sockaddr  struct and its size respectively to get info about client
    // in the current example I know it's a localhost (my machine), so passing NULL for both arguments
    int client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, &server_message, sizeof(server_message), 0);

    close(server_socket);
    return 0;
}