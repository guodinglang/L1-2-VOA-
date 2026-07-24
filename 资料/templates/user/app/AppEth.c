#include "includes.h"

#include "wiz_interface.h"
#include "tcp_server_multi_socket.h"

/* network information */
uint8_t ethernet_buf[ETHERNET_BUF_MAX_SIZE] = {0};

void AppEth_Init(void)
{
  /* wizchip init */
  wizchip_initialize();

  network_init(ethernet_buf, (wiz_NetInfo *)&AppInfo.NetInfo);

  multi_tcps_socket_init();
}

void AppEth_Proc(void)
{
  multi_tcps_socket_proc(AppInfo.usLocalPort);
}
