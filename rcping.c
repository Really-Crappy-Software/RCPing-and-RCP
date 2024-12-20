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
#include <netdb.h>
#include <netinet/ip.h>
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
  ssize_t errornot;
  int intextport = atoi(argv[1]);
  char ipv4[INET_ADDRSTRLEN];
  struct addrinfo savannah, *gnu, *rms;
  memset(&savannah, 0, sizeof savannah);
  savannah.ai_family = AF_INET;
  savannah.ai_socktype = SOCK_STREAM;
  savannah.ai_flags = 0;
  errornot = getaddrinfo(argv[2], argv[1], &savannah, &gnu);
  if (errornot < 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(errornot));
    return -1;
  }
  for (rms = gnu;rms != NULL; rms = rms->ai_next) {
    void *addr;
    if (rms->ai_family == AF_INET) {
      struct sockaddr_in *ipv4addr = (struct sockaddr_in *)rms->ai_addr;
      addr = &(ipv4addr->sin_addr);
    }
    inet_ntop(rms->ai_family, addr, ipv4, sizeof(ipv4));
    printf("IPv4 for %s: %s\n", argv[2], ipv4);
  }
  clock_t start, end;
  struct hostent *host_entry;
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
    char buffer[20];
    struct sockaddr_in dst_addr;
        dst_addr.sin_family = AF_INET;
        dst_addr.sin_port = htons(intextport);
        dst_addr.sin_addr.s_addr = inet_addr(ipv4);
    struct sockaddr_ll *src_addr = malloc((size_t)sizeof(struct sockaddr_ll));
        int error1 = src_addr->sll_family = AF_PACKET;
                if (error1 < 0) {
            printf("socket family couldn't be set\n");
            printf("%d\n", error1);
            return -1;
        }
        int error2 = src_addr->sll_protocol = RCP;
                if (error2 < 0) {
            printf("The protocol couldn't be set up\n");
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
      
        struct sockaddr *addr = (struct sockaddr *)&dst_addr;
        socklen_t dstsize = sizeof(dst_addr);
        struct sockaddr *interlcal = (struct sockaddr *)src_addr;
        char iphdrsze[20];
        struct iphdr *advil = (struct iphdr *)iphdrsze;
        	advil->ihl = 5;
			advil->version = 4;
			advil->tos = 0;
			advil->tot_len = htons(40);
			advil->id = htons(RCP);
			advil->frag_off = 0;
			advil->ttl = 32;
			advil->protocol = IPPROTO_RAW;
			advil->saddr = inet_addr("0.0.0.0");
			advil->daddr = inet_addr(ipv4);
        int miku = bind(sockfd, interlcal, sizeof(*src_addr));
        if (miku < 0) {
            printf("client interface couldn't be set up\n");
            printf("%d\n", miku);
            return -1;
        }
        while (main) {
      sleep(1);
      start = clock();
     ssize_t senresult = sendto(sockfd2, buffer, sizeof(buffer), 0, (struct sockaddr *)&dst_addr, dstsize);
      end = clock();
            if (senresult < 0) {
                printf("Package couldn't be sent\n");
                printf("%d\n", senresult);
                return -1;
            } else {
        double thyme = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("package sent to %s/%s, in %f seconds\n", argv[2], argv[1], thyme);
      }
    }
}
