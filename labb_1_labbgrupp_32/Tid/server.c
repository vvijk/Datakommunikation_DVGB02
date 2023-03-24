#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <time.h>

#define SERVER_PORT 8080
#define BUF_SIZE 4096
int main(){
    int socket_desc;
    struct sockaddr_in server_addr, client_addr;
    int client_struct_len = sizeof(client_addr);
    char buffer[BUF_SIZE];

    while(1){
        socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(socket_desc < 0){
            printf("ERROR W CREATING SÖCKET\n");
        }
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
        printf("**********************************\n"
        "Listening for incoming messages...\n");
        /*Recive client message (empty datagram)*/
        if (recvfrom(socket_desc, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_struct_len) < 0){
            printf("Couldn't receive message\n");
            return -1;
        }else{
            printf("Empty datagram recived...\n");
        }
        time_t current_time = time(NULL);
        printf("Sending current time: %s", ctime(&current_time));
        uint32_t data = current_time; // since 1970 (unix epoch)
        data += 2208988800L; // since 1900 
        data = htonl(data); // Convert to Network order
        sendto(socket_desc, &data, 4, 0, (struct sockaddr*)&client_addr, client_struct_len);
        printf("Closing socket..\n");
        close(socket_desc);
    }
}