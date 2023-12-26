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
#include <fstream>
#include <unordered_map>
#include <string>

#define PORT "43134"
#define PATH "./history.txt"

#define MAX_BUF 1024
using namespace std;

char localIP[] = "127.0.0.1";

int main(int argc, char** argv) {

    /* load data */
    ifstream fs (PATH); 

    unordered_map<string, int> book_list;

    if (fs.is_open()) {
        string book_code;
        int num;
        while (fs >> book_code >> num) {
            book_code = book_code.substr(0, book_code.length()-1);
            book_list.emplace(book_code, num);
            book_code.clear();
        }
        fs.close();
    } else {
        perror("serverH: failed to open history.txt");
    }
    /* setup socket for UDP with serverM */
    /* refer to Beej's Guide */
    struct addrinfo hints, *res, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    
    if(getaddrinfo(localIP, PORT, &hints, &res) == -1) {
        perror("serverH: getaddrinfo error");
    }
    int sockfd;

    for (p = res; p != NULL; p = p->ai_next) {
        if ( (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1 ) {
            perror("serverH: socket");
            continue;
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("serverH: bind");
            continue;
        }
        break;
    }
    if (p == NULL) {
        perror("serverH: failed to create socket");
    }
    freeaddrinfo(res);

    /* end of reference */

    cout << "serverH is up and running using UDP on port 43134.\n";

    /* refer to Beej's Guide */
    struct sockaddr_storage from;
    socklen_t addr_len = sizeof(from);
    /* end of reference */

    char recv_buf[MAX_BUF];
    char send_buf[MAX_BUF];
    int admin = 0;
    char code[MAX_BUF];
    while (1) {
        // listen to the serverM
        memset(code, 0, sizeof(code));
        memset(recv_buf, 0, sizeof(recv_buf));
        memset(send_buf, 0, sizeof(send_buf));
        recvfrom(sockfd, recv_buf, MAX_BUF, 0, (struct sockaddr *)&from, &addr_len);        
        
        sscanf(recv_buf, "%s %d", code, &admin);
        if(!admin) cout << "Server H received " << code <<  " code from the Main Server.\n";
        else cout << "Server H received an inventory status request for code " << code << ".\n";

        if (book_list.find(code) != book_list.end()) {
            sprintf(send_buf, "%d", book_list[code]);
            if (book_list[code] > 0 && !admin) --book_list[code];
            if(sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr *)&from, addr_len) < 0) {
                perror("serverH: error");
            }
        } else {
            sprintf(send_buf, "-1");
            if(sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr *)&from, addr_len) < 0) {
                perror("serverH: error");
            }
        }
        
        if(!admin) cout << "Server H finished sending the availability status of code " << code << " to the Main Server using UDP on port 43134.\n";
        else cout << "Server H finished sending the inventory status to the Main server using UDP on port 43134.\n";
    }

    return 0;       
}