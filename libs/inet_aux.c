#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include "inet_aux.h"
#include "memory.h"
#include "debug.h"

int ipv4_to_bits(const char *addr, void *ipv4_addr)
{
    return inet_pton(AF_INET, addr, ipv4_addr);
}

int check_endianess()
{
    unsigned short val = 0xAAFF;
    unsigned short re = htons(val);
    if (val != re)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void memory_dump(void *addr, size_t size)
{
    unsigned char *ptr = addr;
    printf("0x");
    for (size_t i = 0; i < size; i++)
    {
        printf("%02x", ptr[i]);
    }
    printf("\n");
}

int open_ipv4_udp_socket()
{
    int ipv4_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (ipv4_socket == -1)
    {
        ERROR(C_ERROR_CREATING_IPV4_SOCKET, "Error creating ipv4 socket.\n");
    }

    return ipv4_socket;
}

int open_ipv6_udp_socket()
{
    int ipv6_socket = socket(AF_INET6, SOCK_DGRAM, 0);
    if (ipv6_socket == -1)
    {
        ERROR(C_ERROR_CREATING_IPV6_SOCKET, "Error creating ipv6 socket.\n");
    }

    return ipv6_socket;
}

struct sockaddr_in *new_internet_socket_address_v4()
{
    size_t addr_size = sizeof(struct sockaddr_in);

    struct sockaddr_in *addr = (struct sockaddr_in *)MALLOC(addr_size);

    memset(addr, 0, addr_size);

    return addr;
}

struct sockaddr_in6 *new_internet_socket_address_v6()
{
    size_t addr_size = sizeof(struct sockaddr_in6);

    struct sockaddr_in6 *addr = (struct sockaddr_in6 *)MALLOC(addr_size);

    memset(addr, 0, addr_size);

    return addr;
}

void free_internet_socket_alloc(struct sockaddr *address)
{
    FREE(address);
}

int port_in_range(int port)
{
    return port >= 1 && port <= USHRT_MAX;
}
