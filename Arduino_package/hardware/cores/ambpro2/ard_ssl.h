#ifndef ARD_SSL_H
#define ARD_SSL_H

#include <mbedtls/ctr_drbg.h>
#include <mbedtls/ssl.h>
#include <mbedtls/entropy.h>
#include <mbedtls/net_sockets.h>

typedef struct {
    int socket;
    int recvTimeout;
    mbedtls_ssl_context *ssl;
    mbedtls_ssl_config *conf;
    mbedtls_ctr_drbg_context *ctr_drbg;
    mbedtls_entropy_context *entropy;
} sslclient_context;

int start_ssl_client(sslclient_context *ssl_client, uint32_t ipAddress, uint32_t port, unsigned char *rootCABuff, unsigned char *cli_cert, unsigned char *cli_key, unsigned char *pskIdent, unsigned char *psKey, char *SNI_hostname);

void stop_ssl_socket(sslclient_context *ssl_client);

int send_ssl_data(sslclient_context *ssl_client, const uint8_t *data, uint16_t len);

int get_ssl_receive(sslclient_context *ssl_client, uint8_t *data, int length, int flag);

int get_ssl_sock_errno(sslclient_context *ssl_client);

int get_ssl_bytes_avail(sslclient_context *ssl_client);

#endif
