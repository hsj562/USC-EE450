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

#define UDP_PORT "44134"
#define TCP_PORT "45134"

#define MAX_BUF 1024
#define CODE_SZ 128
#define MAX_USR 1024
#define PATH "./member.txt"
using namespace std;


char localIP[] = "127.0.0.1";

char backend[] = "SLH";
char ports[][16] = {"41134", "42134", "43134"};

int main(int argc, char** argv) {
    cout << "Main Server is up and running.\n";

    /* setup UDP socket */
    /* refer to Beej's Guide */
    int udp_sock; 
    struct addrinfo *udp_addr;

    struct addrinfo udp_hints, *res;
    memset(&udp_hints, 0, sizeof(udp_hints));
    udp_hints.ai_family = AF_INET;
    udp_hints.ai_socktype = SOCK_DGRAM;

    if(getaddrinfo(localIP, UDP_PORT, &udp_hints, &res) == -1) {
        perror("serverM: getaddrinfo error");
    }

    for (udp_addr = res; udp_addr != NULL; udp_addr = udp_addr->ai_next) {
        if ( (udp_sock = socket(udp_addr->ai_family, udp_addr->ai_socktype, udp_addr->ai_protocol)) == -1 ) {
            perror("serverM: socket for backend server");
            continue;
        }
        if (bind(udp_sock, udp_addr->ai_addr, udp_addr->ai_addrlen) == -1) {
            close(udp_sock);
            perror("serverM: bind");
            continue;
        }
        break;
    }
    if (udp_addr == NULL) {
        perror("serverM: failed to create socket for backend server");
    }

    freeaddrinfo(res);
    /* end of reference */
    
    /* load member list */
    ifstream fs (PATH);
    unordered_map<string, string> valid_users;
    
    if (fs.is_open()) {
        string tmp, password, username;
        while(fs >> tmp >> password) {
            tmp = tmp.substr(0, tmp.length()-1);
            for(int i = 0; i < tmp.length(); ++i) {
                if(isupper(tmp[i])) username += tolower(tmp[i]);
                else username += tmp[i];
            }
            if(password[password.length()-1] == '\n') 
                password.substr(0, password.length()-1);
            valid_users.emplace(username, password);
            username.clear();
            password.clear();
            tmp.clear();

        }
        fs.close();
    } else {
        perror("serverM: failed to open member.txt");
    }
    cout << "Main Server loaded the member list.\n";

    /* build the connection with clients */
    /* refer to Beej's Guide */
    int sock_client;
    struct addrinfo hints, *servinfo, *p;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(NULL, TCP_PORT, &hints, &servinfo) != 0) {
        perror("serverM: getaddrinfo error");
    }
    
    int yes = 1;
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sock_client = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("serverM: socket for client");
            continue;
        }
        if (setsockopt(sock_client, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
            perror("serverM: setsockopt error");
        }
        if (bind(sock_client, p->ai_addr, p->ai_addrlen) == -1) {
            close(sock_client);
            perror("serverM: bind error");
            continue;
        }
        break;
    }
    freeaddrinfo(servinfo);

    if (p == NULL) {
        perror("serverM: failed to bind");
    }

    if (listen(sock_client, SOMAXCONN) == -1) {
        perror("serverM: listen error");
    }
    /* end of reference */

    /* listening from the client */
    while (1) { 
        /* refer to Beej's Guide */
        struct sockaddr_storage client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int child_fd = accept(sock_client, (struct sockaddr *)&client_addr, &addr_len);
        if (child_fd == -1) {
            perror("serverM: accept error");
            continue;
        }
        /* end of reference */

        /* authentication */
        bool auth = false;
        int admin = 0;

        while (1) {
            char buffer[MAX_BUF] = {};
            if(recv(child_fd, buffer, MAX_BUF, 0) == 0) break; // the client terminated the connection
            char user[MAX_BUF] = {}, pwd[MAX_BUF] = {};
            sscanf(buffer, "%s %s %d", user, pwd, &admin);
            string username = string(user), password = string(pwd);
            cout << "Main Server received the username and password from the client using TCP over port 45134.\n";

            if (valid_users.find(username) != valid_users.end()) { // valid username
                if (valid_users[username] == password) {
                    // successful
                    cout << "Password " << password << " matches the username. Send a reply to the client.\n";
                    send(child_fd, "0", 1, 0);
                    auth = true;
                    break;
                } else {
                    // wrong password
                    cout << "Password " << password << " does not match the username. Send a reply to the client.\n";
                    send(child_fd, "1", 1, 0);
                }
            } else {
                // wrong username
                cout << username << " is not registered. Send a reply to the client.\n";
                send(child_fd, "2", 1, 0);
            }
        }

        /* authentication succeed */
        /* get book code query from the client */
        char book_code[CODE_SZ], ret_msg[MAX_BUF];
        char recv_buf[MAX_BUF], send_buf[MAX_BUF];

        while (auth) {
            memset(send_buf, 0, sizeof(send_buf));
            memset(book_code, 0, sizeof(book_code));
            memset(ret_msg, 0, sizeof(ret_msg));
            memset(recv_buf, 0, sizeof(recv_buf));
            if(recv(child_fd, book_code, CODE_SZ, 0) == 0) return 0; // the client terminated the connection
            cout << "Main Server received the book request from client using TCP over port 45134.\n";
            // check the first character of book_code
            int categ = -1;
            
            if (book_code[0] == 'S') {
                categ = 0;
                cout << "Found " << book_code << " located at ServerS. Send to Server S.\n";
            } else if (book_code[0] == 'L') {
                categ = 1;
                cout << "Found " << book_code << " located at ServerL. Send to Server L.\n";

            } else if (book_code[0] == 'H') {
                categ = 2;
                cout << "Found " << book_code << " located at ServerH. Send to Server H.\n";
            } else {
                // wrong code
                sprintf(ret_msg, "Not able to find the book-code %s in the system.", book_code);
                send(child_fd, ret_msg, strlen(ret_msg), 0);
                cout << "Did not find " << book_code << " in the book code list.\n";
            }

            if (categ >= 0) {
                
                /* get destination address */
                struct addrinfo dest_hint, *dest_addr;
                memset(&dest_hint, 0, sizeof(dest_hint));
                dest_hint.ai_family = AF_INET;
                dest_hint.ai_socktype = SOCK_DGRAM;
                if(getaddrinfo(localIP, ports[categ], &dest_hint, &dest_addr) < 0) perror("serverM: getaddrinfo error");

                sprintf(send_buf, "%s %d", book_code, admin);
                sendto(udp_sock, send_buf, strlen(send_buf), 0, dest_addr->ai_addr, dest_addr->ai_addrlen);
                recvfrom(udp_sock, recv_buf, MAX_BUF, 0, dest_addr->ai_addr, &dest_addr->ai_addrlen);
                cout << "Main Server received the book code list from server " << backend[categ] << " using UDP over port 44134.\n";
                
                int remain = 0;
                sscanf(recv_buf, "%d", &remain);

                // return the result back to the client
                if(!admin) {
                    if(remain == -1) { // wrong code
                        sprintf(ret_msg, "Not able to find the book-code %s in the system.", book_code);
                        send(child_fd, ret_msg, strlen(ret_msg), 0);
                    } else if(remain == 0) { // not available
                        sprintf(ret_msg, "The requested book %s is NOT available in the library.", book_code);
                        send(child_fd, ret_msg, strlen(ret_msg), 0);
                    } else if(remain > 0) { // available
                        sprintf(ret_msg, "The requested book %s is available in the library.", book_code);
                        send(child_fd, ret_msg, strlen(ret_msg), 0);
                    }
                } else {
                    if(remain == -1) {
                        sprintf(ret_msg, "Not able to find the book-code %s in the system.\n", book_code);
                        send(child_fd, ret_msg, strlen(ret_msg), 0);
                    } else {
                        sprintf(ret_msg, "Total number of book %s available = %d\n", book_code, remain);
                        send(child_fd, ret_msg, strlen(ret_msg), 0);
                    }
                }
                cout << "Main Server sent the book status to the client.\n";
            }
            
        }
        
    }
    
    return 0;
}