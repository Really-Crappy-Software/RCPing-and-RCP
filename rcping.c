#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <asm/types.h>
#include <linux/if_ether.h>
#include <libcap.h>
#include <string.h>
#define RCP             49152
#define ARPHRD_ETHER 	1
#define PACKET_RX       2
#define sizepkt         512
typedef unsigned short ushort_t;
struct sockaddr_ll {
    ushort_t sll_family;      /* address family (AF_LINK) */
    ushort_t sll_protocol;    /* link-layer protocol (e.g., Ethernet) */
    int32_t sll_ifindex;      /* interface index */
    uint16_t sll_hatype;     /* ARP hardware type */
    uint8_t  sll_pkttype;    /* packet type */
    uint8_t  sll_halen;      /* hardware address length */
    uint8_t  sll_addr[8];   /* hardware address (e.g., MAC address) */
};

uint16_t srcport;
uint16_t extport;
uint16_t srcport1;
uint16_t extport2;
char payload[256];

int main(int argc, char* argv[]) {
int intextport = atoi(argv[1]);
    cap_t caps = cap_init();
        cap_value_t *capvl = 0;
            cap_set_flag(caps, CAP_NET_RAW, 1, capvl, CAP_SET);
int sockfd = socket(AF_PACKET, SOCK_RAW, RCP);
if (sockfd < 0) {
    printf("Socket not created\n");
    printf("%d\n", sockfd);
    return -1;
    } else {
        printf("Socket Created successfully\n");
    }
    printf("test1\n");
    struct sockaddr_in *dst_addr = malloc((size_t)sizeof(struct sockaddr_in));
    printf("1\n");
    char buffer[sizepkt];
        printf("hi\n");
        dst_addr->sin_family = AF_INET;
        printf("test2\n");
        dst_addr->sin_port = htons(intextport);
        printf("test3\n");
        inet_pton(AF_INET, "127.0.0.1", &dst_addr->sin_addr);
        printf("test4\n");
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
            printf("package type couldn't be set\n");
            printf("%d\n", error5);
            return -1;
        }
        int error6 = src_addr->sll_hatype = ARPHRD_ETHER;
                        if (error6 < 0) {
            printf("package type couldn't be set\n");
            printf("%d\n", error6);
            return -1;
        }
        printf("test6\n");
        struct sockaddr *addr = (struct sockaddr *)&dst_addr;
        printf("1\n");
        struct sockaddr *interlcal = (struct sockaddr *)&src_addr;
     strcpy(payload, "This packet was sent using RCPing under the Really Crappy Protocol");
     extport = htons(intextport);
     srcport = htons(RCP);
     char chrsrcport[16];
     char chrextport[16];
     sprintf(chrsrcport, "%d", srcport);
     sprintf(chrextport, "%d", extport);
        memcpy(buffer, chrsrcport, sizeof(chrsrcport));
        printf("7\n");
            memcpy(buffer + sizeof(chrsrcport), chrextport, sizeof(chrextport));
            printf("8\n");
                memcpy(buffer + sizeof(chrsrcport) + sizeof(chrextport), payload, 8);
                printf("9\n");
        srcport1 = htons(RCP);
        extport2 = htons(intextport);
        int miku = bind(sockfd, interlcal, sizeof(interlcal));
        printf("10\n");
        if (miku < 0) {
            printf("client interface couldn't be set up\n");
            printf("%d\n", miku);
            return -1;
        }

        int jumanji = connect(sockfd, addr, sizeof(addr));
    if (jumanji < 0) {
        printf("Couldn't establish a connection using RCP, unsurprisingly\n");
        printf("%d", jumanji);
        return -1;
    } else {
        while (main) {
            ssize_t senresult = send(sockfd, buffer, sizeof(buffer), 0);
            if (senresult < 0) {
                printf("Package wasn't sent");
            }
        }
    }
}
