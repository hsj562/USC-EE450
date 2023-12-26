### EE 450 

### Lab #1

### Name: Shih-Ju Hsu

<div style="page-break-after: always; break-after: page;"></div>

* release IP address

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926023839372.png" alt="image-20230926023839372" style="zoom:33%;" />

* renew IP address

  <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926024636709.png" alt="image-20230926024636709" style="zoom:43%;" />

* second renew

(Renew DHCP Lease)

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/Screen Shot 2023-09-26 at 8.18.53 PM.png" alt="Screen Shot 2023-09-26 at 8.18.53 PM" style="zoom:20%;" />





<div style="page-break-after: always; break-after: page;"></div>

(1) 

DHCP messages are sent over UDP

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926091147382.png" alt="image-20230926091147382" style="zoom:50%;" />

<div style="page-break-after: always; break-after: page;"></div>

(2)

Yes. The port numbers (67 and 68) are the same as the given port numbers in this assignment. <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926091614870.png" alt="image-20230926091614870" style="zoom:50%;" />



(3) 

The link-layer address of my host is **Apple_c2:7b:1a (90:9c:4a:c2:7b:1a)**.

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926092123784.png" alt="image-20230926092123784" style="zoom:50%;" />

<div style="page-break-after: always; break-after: page;"></div>

(4) 

The **DHCP Message Type** are different. Also, the DHCP request message includes the information of **Requested IP Address** and **DHCP Server Identifier** while the DHCP discover message doesn't.

<img src="/Users/jameshsu/Desktop/Screen Shot 2023-09-26 at 9.27.50 AM.png" alt="Screen Shot 2023-09-26 at 9.27.50 AM" style="zoom:30%;" />



<img src="/Users/jameshsu/Desktop/Screen Shot 2023-09-26 at 9.27.15 AM.png" alt="Screen Shot 2023-09-26 at 9.27.15 AM" style="zoom:30%;" />

<div style="page-break-after: always; break-after: page;"></div>

(5)

- First DHCP Transaction ID: 0x16a47db4

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926101753957.png" alt="image-20230926101753957" style="zoom:40%;" />

- Second DHCP Transaction ID: 0x87fa7ef

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926101705691.png" alt="image-20230926101705691" style="zoom:40%;" />

- The purpose of Transaction ID is used by the client and server to identify the associated DHCP requests and responses.

<div style="page-break-after: always; break-after: page;"></div>

(6)

- Discover: 0.0.0.0 / 255.255.255.255

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926102800678.png" alt="image-20230926102800678" style="zoom:30%;" />



- Offer: 192.168.50.1 / 192.168.50.110

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926102930621.png" alt="image-20230926102930621" style="zoom:30%;" />



- Request: 0.0.0.0 / 255.255.255.255

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926103022652.png" alt="image-20230926103022652" style="zoom:30%;" />

<div style="page-break-after: always; break-after: page;"></div>

- ACK: 192.168.50.1 / 192.168.50.110

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926103043086.png" alt="image-20230926103043086" style="zoom:30%;" />

<div style="page-break-after: always; break-after: page;"></div>

(7)

The IP address of my DHCP server is **192.168.50.1**.

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926103548767.png" alt="image-20230926103548767" style="zoom:50%;" />

(8)

- DHCP server offers **192.168.50.110** to my host in DHCP Offer message.

  <img src="/Users/jameshsu/Library/Application Support/typora-user-images/Screen Shot 2023-09-26 at 5.37.31 PM.png" alt="Screen Shot 2023-09-26 at 5.37.31 PM" style="zoom:45%;" />

  (9)

  In the example screenshot, the IP address is **0.0.0.0**. In my experiment, the relay agent IP address is also **0.0.0.0**. Therefore, there is no relay agent in my experiment.

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/Screen Shot 2023-09-26 at 5.37.57 PM.png" alt="Screen Shot 2023-09-26 at 5.37.57 PM" style="zoom:45%;" />

<div style="page-break-after: always; break-after: page;"></div>

(10)

- The router line is to tell the client the IP address of the default gateway, which helps the client to transmit packets to the destination outside of the local network.
- The subnet mask line is to tell the client the subnet mask should be used. It helps the client to tell which part of the IP address belongs to the device and which part belongs to the network.

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/Screen Shot 2023-09-26 at 3.24.46 PM.png" alt="Screen Shot 2023-09-26 at 3.24.46 PM" style="zoom:70%;" />

(11)

Yes. The client accepted the offered IP address. The client's requested IP address (192.168.1.101) is in "Option: Requested IP Address" of the DHCP request message.



<img src="/Users/jameshsu/Library/Application Support/typora-user-images/Screen Shot 2023-09-26 at 6.12.49 PM.png" alt="Screen Shot 2023-09-26 at 6.12.49 PM" style="zoom:50%;" />

<div style="page-break-after: always; break-after: page;"></div>

(12)

- The purpose of the lease time is to tell the client how long will the assigned IP address be expired.

- In my experiment, the lease time is **1day**.

 <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230926155542954.png" alt="image-20230926155542954" style="zoom:30%;" />

(13)

- The DHCP release message is the request by the client to release the IP address and return to the server.
- No. The DHCP server does not issue any acknowledgement of receipt of the client’s DHCP request to the client. There is no verification of DHCP release message has been received.
- The server will not assign the IP address to others until the IP address expired. (ruuning out of the lease time)

(14)

Yes. There are broadcast ARP packets sent during the DHCP packet-exchange period. The purpose of the ARP packets is to make sure no other devices using the same IP address. If no devices have taken the IP address, the server will acknowledge the client's request.

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/Screen Shot 2023-09-26 at 4.44.27 PM.png" alt="Screen Shot 2023-09-26 at 4.44.27 PM" style="zoom:50%;" />