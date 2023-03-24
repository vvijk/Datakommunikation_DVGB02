#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <time.h>
#include <stdlib.h>

#define SERVER_PORT 8080
#define BUF_SIZE 4096
int main(){
    int socket_desc;
    struct sockaddr_in server_addr, client_addr;
    int server_struct_len = sizeof(server_addr);
    char buffer[BUF_SIZE];
    
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(socket_desc < 0){
        printf("ERROR W CREATING SÖCKET\n");
    }else{
        printf("SOCKET CREATION SUCCESS\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    /*Send empty datagram*/
    sendto(socket_desc, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    uint32_t data;
	int bytes_read = recvfrom(socket_desc, &data, 4, 0, (struct sockaddr*)&server_addr, &server_struct_len);
    if(bytes_read < 0){
        perror("bytes_read\n");
        exit(1);
    }

    data = ntohl(data); // to little endian
	printf("Data received: dec: %d hex: %X\n", data, data);
    data -= 2208988800L; // since 1970
    time_t current_time = data;
	printf("Current server time is: %s\n", ctime(&current_time));

    close(socket_desc);
}