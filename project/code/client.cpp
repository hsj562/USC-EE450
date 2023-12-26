#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#define PORT "45134"
#define MAX_BUF 1024
using namespace std;

char localIP[] = "127.0.0.1";

void encrpt(char original_text[], char encrpted_text[]) {
    for(int i = 0; i < strlen(original_text); ++i) {
        if (isdigit(original_text[i])) {
            sprintf(encrpted_text+i, "%c", '0' + (original_text[i] - '0' + 5) % 10);
        } else if (isupper(original_text[i])) {
            sprintf(encrpted_text+i, "%c", 'A' + (original_text[i] - 'A' + 5) % 26);
        } else if (islower(original_text[i])) {
            sprintf(encrpted_text+i, "%c", 'a' + (original_text[i] - 'a' + 5) % 26);
        } else {
            sprintf(encrpted_text+i, "%c", original_text[i]);
        }
    }
}

int main(int argc, char** argv) {

    cout << "Client is up and running.\n";
    /* create socket and connect with main server */
    struct addrinfo hints, *remote_addr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(localIP, PORT, &hints, &remote_addr);   // get the server addr info

    int sockfd = socket(hints.ai_family, hints.ai_socktype, 0);
    connect(sockfd, remote_addr->ai_addr, remote_addr->ai_addrlen);

    struct sockaddr_in my_addr;
    socklen_t addrlen = sizeof(my_addr);
    getsockname(sockfd, (struct sockaddr *)&my_addr, &addrlen);
    int port = ntohs(my_addr.sin_port);

    freeaddrinfo(remote_addr);

    /* interact with users */
    char username[MAX_BUF] = {}, password[MAX_BUF] = {};
    char en_username[MAX_BUF] = {}, en_password[MAX_BUF] = {};
    bool admin = false;
    while (1) {
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        memset(en_username, 0, sizeof(en_username));
        memset(en_password, 0, sizeof(en_password));
        cout << "Please enter the username: ";
        cin >> username;
        cout << "Please enter the password: ";
        cin >> password;
        admin = string(username) == "admin";
        encrpt(username, en_username);
        encrpt(password, en_password);

        char send_buf[MAX_BUF] = {};
        strncat(send_buf, en_username, strlen(en_username));
        strncat(send_buf, " ", 1);
        strncat(send_buf, en_password, strlen(en_password));
        strncat(send_buf, admin?" 1": " 0", 2);

        // send msg to main server
        if (send(sockfd, send_buf, strlen(send_buf), 0) == -1) {
            perror("client: sending error");
        }
        cout << username << " sent an authentication request to the Main Server.\n";
        char recv_buf[MAX_BUF] = {};
        if (recv(sockfd, recv_buf, MAX_BUF-1, 0) == -1) {
            perror("client: receiving error");
        }
        int status;
        sscanf(recv_buf, "%d", &status);
        if (status == 0) {
            cout << username << " received the result of authentication from Main Server using TCP over port " << port << ".\nAuthentication is successful.\n";
            char query[MAX_BUF] = {};
            memset(recv_buf, 0, sizeof(recv_buf));
            while (1) {
                memset(recv_buf, 0, sizeof(recv_buf));
                cout << "Please enter book code to query: ";
                cin >> query;
                send(sockfd, query, strlen(query), 0);
                if(admin) {
                    cout << "Request sent to the Main Server with Admin rights.\n";
                } else {
                    cout << username << " sent the request to the Main Server.\n";
                }
                recv(sockfd, recv_buf, MAX_BUF-1, 0);
                cout << "Response received from the Main Server on TCP port: " << port << ".\n";
                cout << recv_buf << endl;
                cout << "—- Start a new query —-\n";
            }
        } else if (status == 1) {
            cout << username << " received the result of authentication from Main Server using TCP over port " << port << ".\nAuthentication failed: Password does not match.\n";
        } else if (status == 2) {
            cout << username << " received the result of authentication from Main Server using TCP over port " << port << ".\nAuthentication failed: Username not found.\n";
        }
        
    }
    
    close(sockfd);
    
    return 0;
}