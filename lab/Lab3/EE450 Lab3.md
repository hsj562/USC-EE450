### EE 450

### Lab \#3

### Name: Shih-Ju Hsu

<p style="page-break-before: always">

1. They are **30 Munroe St** and **linksys_SES_24086**.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101111657017.png" alt="image-20231101111657017" style="zoom:30%;" />

2. They are both **0.1024 seconds**.

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101104300834.png" alt="image-20231101104300834" style="zoom:30%;" />

3. It is **00:16:b6:f7:1d:51**.

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101111757309.png" alt="image-20231101111757309" style="zoom:30%;" />

4. It is **ff:ff:ff:ff:ff:ff** (broadcast).

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101112042752.png" alt="image-20231101112042752" style="zoom:30%;" />

5. It is **00:16:b6:f7:1d:51**.

<img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101112254251.png" alt="image-20231101112254251" style="zoom:30%;" />

6. Supported Rates: **1, 2, 5.5, 11 (Mbps)**. Extended Supported Rates: **6, 9, 12, 18, 24, 36, 48, 54 (Mbps)**.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101115416679.png" alt="image-20231101115416679" style="zoom:40%;" /><img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101115433520.png" alt="image-20231101115433520" style="zoom:40%;" />

7. Three MAC address fields are **destination address**, **source address** and **BSS Id**. 

   MAC address corresponds to the wireless host: **00:13:02:d1:b6:4f** (source address)

   MAC address corresponds to the access point: **00:16:b6:f7:1d:51** (BSS Id)

   MAC address corresponds to the first-hop router: **00:16:b6:f4:eb:a8** (desination address)

   IP address of the wireless host: **192.168.1.109**

   Destination IP address: **128.119.245.12** 

   The destination IP address is the **IP address of gaia.cs.umass.edu** since it's the destination address of the IP packet.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101203754434.png" alt="image-20231101203754434" style="zoom:33%;" />

8. Three MAC address fields are **destination address**, **source address** and **BSS Id**. 

   MAC address corresponds to the host: **91:2a:b0:49:b6:4f** (destination address)

   MAC address corresponds to the access point: **00:16:b6:f7:1d:51** (BSS Id)

   MAC address corresponds to the first-hop router: **00:16:b6:f4:eb:a8** (source address)

   **No**. The IP address of the device that sent the TCP segment is **128.119.245.12**, which is the IP address of gaia.cs.umass.edu. The sender MAC address is **00:16:b6:f4:eb:a8**, which is the MAC address of the first-hop router.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231101203917617.png" alt="image-20231101203917617" style="zoom:33%;" />

   9. 

      (1) The host sent a DHCP release to the DHCP server. 

      (2) The host sent a deauthentication frame to the access point (30 Munroe St).

      <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231102004708605.png" alt="image-20231102004708605" style="zoom:33%;" />

      There should be a **disassociation** request to be sent but we don't see here.

   10. There are **17** frames. They are frame 1740, 1741, 1742, 1744, 1746, 1749, 1750, 1751, 1821, 1822, 1921, 1922, 1923, 1924, 2122, 2123 and 2124.

   11. **Yes.** The host wants the authentication to require a key or be open.

   12. **No.** We can't find a reply authentication from the ``linksys_ses_24086`` AP in the trace.

   13. At **63.168087**, the wireless host (00:13:02:d1:b6:4f) sent an authentication frame to the BSS (00:16:b6:f7:1d:51). At **63.169071**, the BSS sent an authentication frame back to the host.

   

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231102014748119.png" alt="image-20231102014748119" style="zoom:33%;" />

   14. At **63.169910**, the host sent an association request. At **63.192101**, the *30 Munroe St* AP sent an association response.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231102015501536.png" alt="image-20231102015501536" style="zoom:33%;" />

   15. The supported rates are **1, 2, 5.5, 11, 6, 9, 12, 18, 24, 36, 48, 54 (Mbps)** for the host. The supported rates are the same for the AP.

   <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231102020045685.png" alt="image-20231102020045685" style="zoom:30%;" /><img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231102020330819.png" alt="image-20231102020330819" style="zoom:30%;" />

   16. Probe Request: 

       * Receiver address: **ff:ff:ff:ff:ff:ff**
       * Transmitter(sender) address: **00:12:f0:1f:57:13**
       * BSS Id: **ff:ff:ff:ff:ff:ff**

       Probe Response:

       * Receiver address: **00:12:f0:1f:57:13**
       * Transmitter(sender) address: **00:16:b6:f7:1d:51**
       * BSS Id: **00:16:b6:f7:1d:51**

       <img src="/Users/jameshsu/Library/Application Support/typora-user-images/image-20231102021336275.png" alt="image-20231102021336275" style="zoom:50%;" />

       A probe request is used by hosts to **actively find an access point**. A probe response is sent by the AP to **respond the host**.

<p style="page-break-before: always">

### Conclusion

In this lab, we use Wireshark to examine 802.11 frames for exploring various aspects of 802.11, including the MAC addresses of senders, receivers, BSS and the role of beacons and probes. We also observe the process of authentication, association, and disassociation between wireless devices and access points. All in all, the lab helps us in understanding the mechanism of wireless communication by analyzing the frames.
