#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

void send_file(FILE *fp, int socketClient){
  int n;
  char data[1024] = {0};

  while(fgets(data, 1024, fp) != NULL) {
    if (send(socketClient, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, 1024);
  }
}

int main(){
    char *ip = "127.0.0.1";
    int port = 8080;
    int test;

    int socketClient, new_socket;
    struct sockaddr_in serverAddr, new_addr;
    FILE *fp;
    char *filename="send.txt";

    //creation d'une socket ipv4, type, ip
    socketClient = socket(AF_INET, SOCK_STREAM, 0);

    
    serverAddr.sin_family=AF_INET;
    //well-known ports and registered ports ne doivent pas etres utilisés
    serverAddr.sin_port=port;
    serverAddr.sin_addr.s_addr = inet_addr(ip);


    test = connect(socketClient, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(test == -1){
        printf("error in connecting\n");
        exit(1);
    }else{
        printf("connected to the server\n");
    }

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("error in reading file.\n");
        exit(1);
    }

    send_file(fp, socketClient);
    printf("File data sent successfully.\n");

    printf("Closing the connection.\n");
    close(socketClient);

    return 0;

}