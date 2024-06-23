#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int network_socket;
    struct sockaddr_in server_address;
    char server_response[255];

    // 0 means a usage of the default protocol (TCP)
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    if (connection_status < 0)
    {
        printf("Error connecting to websocket");
        return 1;
    };

    recv(network_socket, server_response, sizeof(server_response), 0);
    printf("Received data from the client: %s\n", server_response);

    close(network_socket);
    return 0;
}