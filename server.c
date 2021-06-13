#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void write_file(int socketServer){
    int n;
    FILE *fp;
    char *filename = "received.txt";
    char buffer[1024];

    fp = fopen(filename, "w");
    while (1) {
        n = recv(socketServer, buffer, 1024, 0);
        if (n <= 0){
        break;
        return;
        }
    fprintf(fp, "%s", buffer);
    bzero(buffer, 1024);
    }

}

int main(){
    char *ip = "127.0.0.1";
    int port = 8080;
    int test;

    int socketServer, new_socket;
    struct sockaddr_in serverAddr, new_addr;
    socklen_t addr_size;
    char buffer[1024];
    
    //creation d'une socket ipv4, type, ip
    socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if(socketServer < 0) {
        perror("Erreur dans la socket");
        exit(1);
    }
    printf("Creation de la socket.\n");


    serverAddr.sin_family=AF_INET;
    //well-known ports and registered ports ne doivent pas etres utilisés
    serverAddr.sin_port=port;
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    //associer une adresse ip et numero de port à une socket ouverte, le client doit connaitre l'adresse du serveur pour initier la communication.
    test = bind(socketServer, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(test<0){
        printf("Error in binding\n");
        exit(1);
    }
    printf("binding success\n");

    test = listen(socketServer,1);
    if(test==0){
        printf("Pret pour se connecter...\n");
    }
    else{
        printf("error dans listen.");
        exit(1);
    }

    addr_size = sizeof(new_addr);
    new_socket = accept(socketServer, (struct sockaddr*)&new_addr, &addr_size);

    write_file(new_socket);
    printf("Data written in the file successfully.\n");

    return 0;

}