## EE450 Project
a. Full Name: **Shih-ju Hsu** <br>
b. Student ID: **9525305134** <br>
c. Both the basic and optional parts of my project have been completed. In the basic part, users should login first and the program allows users to check the availability of a book. If the book is available, the quantity will be deducted by one in the backend server. In the optional part, it allows an admin user to search for the remaining quantity of a book.<br>
d. 
* **serverM.cpp**: Server M is used to communicate with both the client and backend servers. It firstly authenticates the client. Then, it receives book queries from the client and sends them to a particular backend server. Finally, the backend server returns the status of the book and server M sends the status to the client.
* **serverS.cpp**: Server S is used to communicate with Server M for querying science books. After receiving a query, it returns the status (available/not available) to Server M. (remaining amount for admin user).
* **serverL.cpp**: Server L is similar to server S. The only difference is that server L is for querying literature-related books.
* **serverH.cpp**: Server H is similar to server S. The only difference is that server H is for querying history-related books.
* **client.cpp**: Client is used to provide an interface for users to enter their username and password to access the service. After authentication, users can enter book codes they want to query. It sends the request to server M and server M will return the status of the status of book to the client.

e. 
* client-serverM: 
    * client to serverM (authentication): ```[username] [password] [admin(0 or 1)]``` (separate with single space)
    * serverM to client (authentication): ```[status 0, 1, 2]``` (0 for authenticated, 1 for wrong password, 2 for unknown username)
    * client to serverM (query): ```[book-code]```
    * serverM to client (query): ```[messages asked in the instruction]``` (i.e. "Not able to find the book-code \<book-code\> in the system." etc.)
* serverM-server<S,H,L>:
    * serverM to server<S,H,L>: ```[book-code] [admin]```
    * server<S,H,L> to serverM: ```[status]``` (remaining amount for the book)

g. ```./client``` should be executed after ```./serverM``` is executed. Otherwise, the system will fail.

h.
    the similar patterns as following code for creating sockets and binding in serverM.cpp, server<S,L,H>.cpp are referred to Beej's Guide

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






