#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <linux/if_xdp.h>
#include <asm/types.h>
#include <time.h>
#include <unistd.h>
#include <linux/if_ether.h>
#include <libcap.h>
#include <string.h>
#define RCP            49152
#define ARPHRD_ETHER 	1
#define PACKET_RX       2
#define sizepkt         1024
typedef unsigned short ushort_t;
struct sockaddr_ll {
    ushort_t sll_family;      /* address family (AF_LINK) */
    ushort_t sll_protocol;    /* link-layer protocol (e.g., Ethernet) */
    int32_t  sll_ifindex;      /* interface index */
    uint16_t sll_hatype;     /* ARP hardware type */
    uint8_t  sll_pkttype;    /* packet type */
    uint8_t  sll_halen;      /* hardware address length */
    uint8_t  sll_addr[8];   /* hardware address (e.g., MAC address) */
};

double   version;
uint16_t srcport;
uint16_t extport;
uint8_t  meinip;
uint8_t  destip;
char payload[256];

int main(int argc, char* argv[]) {
  clock_t start, end;
  struct hostent *host_entry;
int intextport = atoi(argv[1]);
    cap_t caps = cap_init();
        cap_value_t *capvl = 0;
            cap_set_flag(caps, CAP_NET_RAW, 1, capvl, CAP_SET);
int sockfd = socket(AF_PACKET, SOCK_RAW, RCP);
int sockfd2 = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
if (sockfd < 0) {
    printf("Socket not created\n");
    printf("%d\n", sockfd);
    return -1;
    } else {
        printf("Socket Created successfully\n");
    }
    if (sockfd2 < 0) {
    printf("Socket 2 not created\n");
    printf("%d\n", sockfd2);
    return -1;
    } else {
        printf("Socket 2 Created successfully\n");
    }
    struct sockaddr_in *dst_addr = malloc((size_t)sizeof(struct sockaddr_in));
    char buffer[sizepkt];
        dst_addr->sin_family = AF_INET; // IPv4 address family
        dst_addr->sin_port = htons(intextport); // port number
        dst_addr->sin_addr.s_addr = inet_addr(argv[2]); // IPv4 address
    struct sockaddr_ll *src_addr = malloc((size_t)sizeof(struct sockaddr_ll));
        int error1 = src_addr->sll_family = AF_PACKET;
                if (error1 < 0) {
            printf("socket family couldn't be set\n");
            printf("%d\n", error1);
            return -1;
        }
        int error2 = src_addr->sll_protocol = RCP;
                if (error2 < 0) {
            printf("The Internet protocol(IP) couldn't be set up\n");
            printf("%d\n", error2);
            return -1;
        }
        printf("test5\n");
        int error3 = src_addr->sll_ifindex = if_nametoindex("wlan0");
                if (error3 < 0) {
            printf("local interface couldn't be set up\n");
            printf("%d\n", error3);
            return -1;
        }
        int error4 = src_addr->sll_pkttype = PACKET_RX;
                if (error4 < 0) {
            printf("package type couldn't be set\n");
            printf("%d\n", error4);
            return -1;
        }
        int error5 = src_addr->sll_halen = 6;
                        if (error5 < 0) {
                printf("physical address length couldn't be set\n");
            printf("%d\n", error5);
            return -1;
        }
        int error6 = src_addr->sll_hatype = ARPHRD_ETHER;
                        if (error6 < 0) {
            printf("Hardware type couldn't be set\n");
            printf("%d\n", error6);
            return -1;
        }
      
        struct sockaddr *addr = (struct sockaddr *)dst_addr;
        
        struct sockaddr *interlcal = (struct sockaddr *)src_addr;
        strcpy(payload, "This packet was sent using RCPing under the Really Crappy Protocol");
        version = 1.0;
        char ipaddr[16];
        meinip = inet_addr("0.0.0.0");
        destip = inet_addr(argv[2]);
        extport = htons(intextport);
        srcport = htons(RCP);
     char chrsrcport[16];
     char chrextport[16];
     char chrmeinip[8];
     char chrdestip[8];
     char chrversion[8];
     char chrpayload[256];
     sprintf(chrsrcport, "client port:%d\n", srcport);
     sprintf(chrextport, "port sent to:%d\n", extport);
     sprintf(chrversion, "Version of RCP:%d\n", version);
     sprintf(chrdestip, "Destination IP:%d\n", destip);
     sprintf(chrmeinip, "Client IP:%d\n", meinip);
     sprintf(chrpayload, "Payload:%s\n", payload );
      strcat(buffer, chrsrcport);
        strcat(buffer, chrextport);
          strcat(buffer, chrversion);
            strcat(buffer, chrdestip);
              strcat(buffer, chrmeinip);
                strcat(buffer, chrpayload);
        int miku = bind(sockfd, interlcal, sizeof(*src_addr));
        if (miku < 0) {
            printf("client interface couldn't be set up\n");
            printf("%d\n", miku);
            return -1;
        }

        int jumanji = connect(sockfd2, addr, sizeof(*dst_addr));
    if (jumanji < 0) {
        printf("Couldn't establish a connection using RCP, unsurprisingly\n");
        printf("%d\n", jumanji);
        return -1;
    } else {
      printf("package sending:\n %s", buffer);
        while (main) {
      sleep(1);
      start = clock();
            ssize_t senresult = send(sockfd2, buffer, sizeof(buffer), 0);
      end = clock();
            if (senresult < 0) {
                printf("Package couldn't be sent\n");
                return -1;
            } else {
        double thyme = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("package sent to %s, in %f seconds\n", argv[2], thyme);
      }
        }
    }
}
