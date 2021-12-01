#ifndef _INET_AUX_H_
#define _INET_AUX_H_

#include <limits.h>

#define C_ERROR_CREATING_IPV4_SOCKET 100
#define C_ERROR_CREATING_IPV6_SOCKET 101

/**
 * @brief Point to Network (ok 1, else 0)
 * af = AF_INET | AF_INET6
 * src = string dotted
 * dst = struct in_addr | in6_addr
 */
// int inet_pton(int af, const char *src, void *dst);

/**
 * @brief Network to Point (ok 1, else 0)
 * af = AF_INET | AF_INET6
 * src = string dotted
 * dst = struct in_addr | in6_addr
 * size = sizeof(struct in_addr | in6_addr)
 */
// char inet_ntop(int af, const void *src, char *dst, socklen_t size);

// #include <sys/socket.h>
// struct sockaddr
// {
//     unsigned short sa_family; /* address family: AF_XXXX value */
//     char sa_data[14];         /* protocol-specific address */
// }

// ! IPV4
// #include <arpa/inet.h>
// struct sockaddr_in
// {
//     sa_family_t sin_family;  /* address family: AF_INET */
//     in_port_t sin_port;      /* port in network byte order (usar htons)*/
//     struct in_addr sin_addr; /* internet address */
// };
// /* Internet address. */
// struct in_addr
// {
//     uint32_t s_addr; /* address in network byte order (usar htonl)*/
// };

// ! IPV6
// #include <arpa/inet.h>
// struct sockaddr_in6
// {
//     sa_family_t sin6_family;   /* AF_INET6 */
//     in_port_t sin6_port;       /* port number, in network byte order */
//     uint32_tsin6_flowinfo;     /* IPv6 flow information */
//     struct in6_addr sin6_addr; /* IPv6 address */
//     uint32_t sin6_scope_id;    /* Scope ID */
// };
// struct in6_addr
// {
//     uint8_t s6_addr[16]; /* IPv6 address, in network byte order */
// };

// ! Byte order
// #include <arpa/inet.h>
// uint32_t htonl(uint32_t hostTOlong);
// uint32_t ntohl(uint32_t netTOlong);
// uint16_t htons(uint16_t hostTOshort);
// uint16_t ntohs(uint16_t netTOshort);

// ! Comunication lifecycle - Client
// socket() -> *sendto() -> *recvfrom() -> close()
//                      -> to_server -> recvfrom() -> process -> sendto() -> client
// ? OR
// socket() -> connect() -> send() -> recv() -> close()
//                      -> to_server -> recvfrom() -> process -> sendto() -> client

// ! Comunication lifecycle - Server
// socket() -> bind() -> *recvfrom() -> process -> *sendto()

// ! Socket
// #include <sys/types.h>
// #include <sys/socket.h>
// int socket( int domain, int type, int protocol);
// int socket( AF_INET | AF_INET6, SOCK_STREAM | SOCK_DGRAM | SOCK_RAW, 0 - default);
// success - fd
// failure - -1

// ! Binding - ! SERVER !
// #include <sys/types.h>
// #include <sys/socket.h>
// int bind( int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// int bind(
//     SOCKET_FILE_DESCRIPTOR,
//     (const struct sockaddr *)CASTING_VAR_sockaddr_in/6,
//     socklen_t addrlen - sizeof(CASTING_VAR_sockaddr_in/6 type)
// );
// success - 0
// failure - -1

// ! Check Available ports / used
// netstat -u -l

// ! Client-Server comunication (NOTE: recvfrom doesnt need to send \0 - the receiver will see the received data and process)
// #include <sys/types.h>
// #include <sys/socket.h>

// ssize_t received = recvfrom( int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
// recvfrom(socket_fd, payload, payload_size, MSG_DONTWAIT | 0, accept_from | NULL, expect_len | 0 | result); - SERVER
// recvfrom(socket_fd, payload, payload_size, MSG_DONTWAIT | 0, accept_from | NULL, expect_len | 0 | result); - CLIENT

// ssize_t sent = sendto( int sockfd, void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
// sendto(sock_fd, &payload, payload_size, 0, (const struct sockaddr *)&server_addr -> sockaddr_in casted, sizeof(server_addr));

// success > 0
// failure -1

// ! Client connect
// struct sockaddr_in server_addr;
// memset(&server_addr, 0, sizeof(struct sockaddr_in));
// server_addr.sin_family = AF_INET;
// server_addr.sin_port = htons(args_info.port_arg);
// server_addr.sin_addr.s_addr = inet_addr(args_info.ip_arg);
// socklen_t server_sock_len = sizeof(struct sockaddr_in);

// int conn_sock = connect(sock_fd, (const struct sockaddr *)&server_addr, server_sock_len);
// (void)conn_sock;

/**
 * @brief Dumps the given memory
 * 
 * @param addr 
 * @param size 
 */
void memory_dump(void *addr, size_t size);

/**
 * @brief Converts dotted ip to binary (0 bad format | -1 error)
 * 
 * @param addr 
 * @param ipv4_addr 
 * @return int 
 */
int ipv4_to_bits(const char *addr, void *ipv4_addr);

/**
 * @brief Checks the endianess of the machine (0 le | 1 be)
 * 
 * @return int 
 */
int check_endianess();

/**
 * @brief Creates a ipv4 socket and returns its file descriptor
 * 
 * @return int 
 */
int open_ipv4_udp_socket();

/**
 * @brief Creates a ipv6 socket and returns its file descriptor
 * 
 * @return int 
 */
int open_ipv6_udp_socket();

struct sockaddr_in *new_internet_socket_address_v4();

struct sockaddr_in6 *new_internet_socket_address_v6();

/**
 * @brief Frees an internet socket allocated space in memory
 * 
 * @param address 
 */
void free_internet_socket_alloc(struct sockaddr *address);

/**
 * @brief Verifies if a port is within range of allowed ports
 * (1 - ok | 0 - not in range)
 * 
 * @param port 
 * @return int
 */
int port_in_range(int port);

#endif