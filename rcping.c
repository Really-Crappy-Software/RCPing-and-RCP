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
#define sizepkt         512
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
    printf("test1\n");
    struct sockaddr_in *dst_addr = malloc((size_t)sizeof(struct sockaddr_in));
    printf("1\n");
    char buffer[sizepkt];
        printf("hi\n");
        dst_addr->sin_family = AF_INET; // IPv4 address family
        dst_addr->sin_port = htons(intextport); // port number
        dst_addr->sin_addr.s_addr = inet_addr("8.8.8.8"); // IPv4 address
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
        printf("test6\n");
        struct sockaddr *addr = (struct sockaddr *)dst_addr;
        printf("1\n");
        struct sockaddr *interlcal = (struct sockaddr *)src_addr;
        printf("here\n");
     printf("here\n");
        strcpy(payload, "This packet was sent using RCPing under the Really Crappy Protocol");
        printf("here\n");
        version = 1.0;
        printf("here\n");
        meinip = inet_addr("220.233.193.89");
        printf("here\n");
        destip = inet_addr("8.8.8.8");
        printf("here\n");
        extport = htons(intextport);
        printf("here\n");
        srcport = htons(RCP);
        printf("here\n");
     char chrsrcport[16];
     char chrextport[16];
     char chrmeinip[8];
     char chrdestip[8];
     char chrversion[8];
     printf("here\n");
     sprintf(chrsrcport, "%d", srcport);
     sprintf(chrextport, "%d", extport);
     sprintf(chrversion, "%d", version);
     sprintf(chrdestip, "%d", destip);
     sprintf(chrmeinip, "%d", meinip);
     printf("here\n");
        memcpy(buffer, chrsrcport, sizeof(chrsrcport));
        printf("7\n");
            memcpy(buffer + sizeof(chrsrcport), chrextport, sizeof(chrextport));
            printf("8\n");
                memcpy(buffer + sizeof(chrsrcport) + sizeof(chrextport), payload, sizeof(payload));
                printf("9\n");
                    memcpy(buffer + sizeof(chrsrcport) + sizeof(chrextport) + sizeof(payload), chrversion, sizeof(chrversion));
                    printf("10\n");
                        memcpy(buffer + sizeof(chrsrcport) + sizeof(chrextport) + sizeof(payload) + sizeof(chrversion),  chrmeinip, sizeof(chrmeinip));
                        printf("11\n");
                            memcpy(buffer + sizeof(chrsrcport) + sizeof(chrextport) + sizeof(payload) + sizeof(chrversion) + sizeof(chrmeinip), chrdestip, sizeof(chrdestip));
                            printf("12\n");


        int miku = bind(sockfd, interlcal, sizeof(*src_addr));
        printf("10\n");
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
        while (main) {
            ssize_t senresult = send(sockfd2, buffer, sizeof(buffer), 0);
            if (senresult < 0) {
                printf("Package couldn't be sent");
                return -1;
            }
        }
    }
}
