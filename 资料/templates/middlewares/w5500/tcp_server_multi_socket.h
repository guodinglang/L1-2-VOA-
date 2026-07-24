#ifndef _TCP_SERVER_MULTI_SOCKET_H_
#define _TCP_SERVER_MULTI_SOCKET_H_

#include "wizchip_conf.h"

#define TCP_SERVER_BUFF_SIZE_PER_SOCKET 128

extern const char *p_caSocketName[_WIZCHIP_SOCK_NUM_];

void multi_tcps_socket_init(void);

/**
 * @brief multi socket loopback function
 * @param destport: local port number
 *
 * @return Returns the operation result, 1 for success and error code for failure
 */
int32_t multi_tcps_socket_proc(uint16_t localport);

#endif
