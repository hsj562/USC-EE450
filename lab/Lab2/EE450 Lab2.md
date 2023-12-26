### EE 450

### Lab 2

### Name: Shih-Ju Hsu

<p style="page-break-before: always">

1. The IP address of www.iitb.ac.in is **103.21.124.10**.

   <img src="/Users/jameshsu/Desktop/1-1.jpg" alt="1-1" style="zoom:80%;" />



2. The IP address of the DNS server that provided the answer above is **192.168.50.1**.

   <img src="/Users/jameshsu/Desktop/1-2.jpg" alt="1-2" style="zoom:80%;" />

3. The answer came from non-authoritative server.

   <img src="/Users/jameshsu/Desktop/1-3.jpg" alt="1-3" style="zoom:80%;" />

4. 

   (1) The name of the authoritative name server is **dns1.iitb.ac.in**.

   (2) I would use another ``nslookup`` command to find the IP address of the authoritative name server.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001012131379.png" alt="image-20231001012131379" style="zoom:33%;" />

   <p style="page-break-before: always">

5. 

   (1) The packet number is **15**.

   (2) It is sent over **UDP**.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930232810486.png" alt="image-20230930232810486" style="zoom:33%;" />

6. 

   (1) The packet number is **17**.

   (2) It is sent over **UDP**.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930232844803.png" alt="image-20230930232844803" style="zoom:33%;" />

7. 

   The destination port for the DNS query message is **53**.

   The source port of the DNS response message is also **53**.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930233036626.png" alt="image-20230930233036626" style="zoom:33%;" />

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930233019319.png" alt="image-20230930233019319" style="zoom:33%;" />

   

8. 

   DNS query message is sent to **75.75.75.75**.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930233147243.png" alt="image-20230930233147243" style="zoom:33%;" />

9. .

   (1) There is **one** "questions" in the DNS query message.

   (2) There are **no** "answers" in the DNS query message.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930233231017.png" alt="image-20230930233231017" style="zoom:33%;" />

10. .

    (1) There is **one** "questions" in the DNS response message.

    (2) There is **one** "answers" in the DNS response message.

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930233246827.png" alt="image-20230930233246827" style="zoom:33%;" />

11. .

    (1) The packet number of base file is **22**.

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930233537919.png" alt="image-20230930233537919" style="zoom:33%;" />

    (2) The packet number of DNS query is **15**. (the screenshot is in Q5)

    (3) The packet number of DNS response is **17**. (the screenshot is in Q6)

    <p style="page-break-before: always">

    (4) The packet number is **205**. 

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20230930233837135.png" alt="image-20230930233837135" style="zoom:33%;" />

    (5) The packet number of DNS query is **15**. (the screenshot is in Q5)

    (6) DNS caching allows the default local DNS server to store the mappings of domain name and its IP address. In this question, the IP address of http://gaia.cs.umass.edu has been stored in the cache of  after the initial query. 

12. 

    (1) The destination port of the DNS query message is **53**.

    (2) The source port of the DNS response message is also **53**.

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001000649469.png" alt="image-20231001000649469" style="zoom:33%;" />

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001000812828.png" alt="image-20231001000812828" style="zoom:33%;" />

13. .

    (1) DNS query message is sent to **75.75.75.75**.

    (2) Yes. It is the default local DNS sever.

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001001245380.png" alt="image-20231001001245380" style="zoom:33%;" />

    <p style="page-break-before: always">

14. 

    (1) It is **Type A**.

    (2) No. It does not contain any "answers"

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001001409436.png" alt="image-20231001001409436" style="zoom:33%;" />

15. .

    DNS response message contain **1** "questions" and **1** "answers".

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001001545663.png" alt="image-20231001001545663" style="zoom:33%;" />

16. 

    (1) The DNS query message is sent to **75.75.75.75**.

    (2) Yes. This is the IP address of the default local DNS server.

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001002143127.png" alt="image-20231001002143127" style="zoom:33%;" />

    <p style="page-break-before: always">

17. 

    The query has **one** "questions" and **does not** contain any "answers".

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001002255450.png" alt="image-20231001002255450" style="zoom:33%;" />

18. .

    (1) There are **3** answers.

    (2) The answers contain three authoritative name servers.

    (3) **Three** additional records are returned.

    (4) The additional records provide the **IP addresses** of the authoritative name servers.

    <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231001002555503.png" alt="image-20231001002555503" style="zoom:33%;" />
    
    <p style="page-break-before: always">



## Conclusion

This lab uses two tools including ``nslookup`` and ``Wireshark``. ``nslookup`` is used to find out the IP address (Type A) or authoritative name server (Type NS) of one domain name. ``Wireshark`` functions as a packet tracer, capturing and analyzing DNS queries and responses. The outcomes of this experiment indicate that the DNS packets are sent over UDP. The host sends queries to and receives responses from the default local DNS server. The DNS server is sent and received messages on port 53. With DNS caching, the DNS servers can store the mappings of domain names and their corresponding IP addresses, which prevents it from querying the same domain names repeatedly.
