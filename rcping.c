#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_arp.h>
#include <net/if.h>
#include <asm/types.h>
#include <libcap.h>
#include <string.h>
#define RCP 49152
#define sizepkt 512
struct RCP_packet {
uint16_t srcport;
uint16_t extport;
char* payload;
};
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
    struct sockaddr_in *dst_addr;
    char buffer[sizepkt];
        dst_addr->sin_family = AF_INET;
        dst_addr->sin_port = htons(intextport);
        inet_pton(AF_INET, "127.0.0.1", &dst_addr->sin_addr);
        struct sockaddr_ll *src_addr;
        src_addr->sll_family = AF_PACKET;
        src_addr->sll_protocol = htons(1560);
        src_addr->sll_ifindex = if_nametoindex("wlan0");
        struct sockaddr *addr = (struct sockaddr *)&dst_addr;
        struct sockaddr *interlcal = (struct sockaddr *)&src_addr;
     struct RCP_packet *packet;
     packet->srcport = htons(49152);
     packet->extport = htons(intextport);
     strcpy(packet->payload, "This packet was sent using RCPing under the Really Crappy Protocol");
        memcpy(buffer, &packet->srcport, sizeof(packet->srcport));
            memcpy(buffer + sizeof(packet->srcport), &packet->extport, sizeof(packet->extport));
                memcpy(buffer + sizeof(packet->srcport) + sizeof(packet->extport), packet->payload, 8);
                   struct RCP_packet *rcp;
        rcp->srcport = htons(1560);
        rcp->extport = htons(intextport);
        int miku = bind(sockfd, interlcal, sizeof(interlcal));
        if (miku < 0) {
            printf("Local interface couldn't be set up\n");
            printf("%d", miku);
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
