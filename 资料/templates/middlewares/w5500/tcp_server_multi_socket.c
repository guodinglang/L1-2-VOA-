#include "tcp_server_multi_socket.h"
#include "socket.h"
#include "stdio.h"
#include "wizchip_conf.h"
#include "BspConfig.h"

const char *p_caSocketName[_WIZCHIP_SOCK_NUM_] =
    {
        "socket_0",
        "socket_1",
        "socket_2",
        "socket_3",
        "socket_4",
        "socket_5",
        "socket_6",
        "socket_7",
};

static uint8_t ucaSocketBuff[_WIZCHIP_SOCK_NUM_][TCP_SERVER_BUFF_SIZE_PER_SOCKET] = {0};
static uint8_t ucaSocketHandle[_WIZCHIP_SOCK_NUM_] = {0};

static uint16_t socket_send_idx_0(uint8_t *p_ucaBuff, uint16_t usLen)
{
  send(0, p_ucaBuff, usLen);
  return usLen;
}

static uint16_t socket_send_idx_1(uint8_t *p_ucaBuff, uint16_t usLen)
{
  send(1, p_ucaBuff, usLen);
  return usLen;
}

static uint16_t socket_send_idx_2(uint8_t *p_ucaBuff, uint16_t usLen)
{
  send(2, p_ucaBuff, usLen);
  return usLen;
}

static uint16_t socket_send_idx_3(uint8_t *p_ucaBuff, uint16_t usLen)
{
  send(3, p_ucaBuff, usLen);
  return usLen;
}

static uint16_t socket_send_idx_4(uint8_t *p_ucaBuff, uint16_t usLen)
{
  send(4, p_ucaBuff, usLen);
  return usLen;
}

static uint16_t socket_send_idx_5(uint8_t *p_ucaBuff, uint16_t usLen)
{
  send(5, p_ucaBuff, usLen);
  return usLen;
}

static uint16_t socket_send_idx_6(uint8_t *p_ucaBuff, uint16_t usLen)
{
  send(6, p_ucaBuff, usLen);
  return usLen;
}

static uint16_t socket_send_idx_7(uint8_t *p_ucaBuff, uint16_t usLen)
{
  send(7, p_ucaBuff, usLen);
  return usLen;
}

const BspComPort_Param_S BspComPort_Param_Socket[_WIZCHIP_SOCK_NUM_] =
    {
        {
            .p_caName = "socket_0",
            .p_ucaBuff = &ucaSocketBuff[0][0],
            .usSize = TCP_SERVER_BUFF_SIZE_PER_SOCKET,
            .usTimeOut = 50,
            .p_Send = socket_send_idx_0,
        },
        {
            .p_caName = "socket_1",
            .p_ucaBuff = &ucaSocketBuff[1][0],
            .usSize = TCP_SERVER_BUFF_SIZE_PER_SOCKET,
            .usTimeOut = 50,
            .p_Send = socket_send_idx_1,
        },
        {
            .p_caName = "socket_2",
            .p_ucaBuff = &ucaSocketBuff[2][0],
            .usSize = TCP_SERVER_BUFF_SIZE_PER_SOCKET,
            .usTimeOut = 50,
            .p_Send = socket_send_idx_2,
        },
        {
            .p_caName = "socket_3",
            .p_ucaBuff = &ucaSocketBuff[3][0],
            .usSize = TCP_SERVER_BUFF_SIZE_PER_SOCKET,
            .usTimeOut = 50,
            .p_Send = socket_send_idx_3,
        },
        {
            .p_caName = "socket_4",
            .p_ucaBuff = &ucaSocketBuff[4][0],
            .usSize = TCP_SERVER_BUFF_SIZE_PER_SOCKET,
            .usTimeOut = 50,
            .p_Send = socket_send_idx_4,
        },
        {
            .p_caName = "socket_5",
            .p_ucaBuff = &ucaSocketBuff[5][0],
            .usSize = TCP_SERVER_BUFF_SIZE_PER_SOCKET,
            .usTimeOut = 50,
            .p_Send = socket_send_idx_5,
        },
        {
            .p_caName = "socket_6",
            .p_ucaBuff = &ucaSocketBuff[6][0],
            .usSize = TCP_SERVER_BUFF_SIZE_PER_SOCKET,
            .usTimeOut = 50,
            .p_Send = socket_send_idx_6,
        },
        {
            .p_caName = "socket_7",
            .p_ucaBuff = &ucaSocketBuff[7][0],
            .usSize = TCP_SERVER_BUFF_SIZE_PER_SOCKET,
            .usTimeOut = 50,
            .p_Send = socket_send_idx_7,
        },
};

void multi_tcps_socket_init(void)
{
  for (uint8_t i = 0; i < _WIZCHIP_SOCK_NUM_; i++)
  {
    ucaSocketHandle[i] = BspComPort_Create((BspComPort_Param_S *)&BspComPort_Param_Socket[i]);
  }
}

/**
 * @brief multi socket loopback function
 * @param destport: local port number
 *
 * @return Returns the operation result, 1 for success and error code for failure
 */
int32_t multi_tcps_socket_proc(uint16_t localport)
{
  int32_t ret;
  uint16_t usRxLen;
  static uint8_t socket_sn = 0;

  switch (getSn_SR(socket_sn))
  {
  case SOCK_ESTABLISHED:
    if (getSn_IR(socket_sn) & Sn_IR_CON)
    {
      // We need to send a packet of data to activate keepalive
      ret = send(socket_sn, (uint8_t *)"", 1); // Data send process
      if (ret < 0)                             // Send Error occurred (sent data length < 0)
      {
        close(socket_sn); // socket close
        return ret;
      }
      setSn_IR(socket_sn, Sn_IR_CON);
    }
    if ((usRxLen = getSn_RX_RSR(socket_sn)) > 0) // Don't need to check SOCKERR_BUSY because it doesn't not occur.
    {
      uint16_t usLinearBuffSize;
      uint8_t *p_ucaLinearBuff = BspComPort_RxBuffGetLinear(ucaSocketHandle[socket_sn], &usLinearBuffSize);
      if (p_ucaLinearBuff)
      {
        if (usRxLen > usLinearBuffSize)
        {
          usRxLen = usLinearBuffSize;
        }

        ret = recv(socket_sn, p_ucaLinearBuff, usRxLen);

        if (ret > 0)
        {
          BspComPort_RxBuffLinearWriteDone(ucaSocketHandle[socket_sn], usRxLen);

          BspComPort_RxStart(ucaSocketHandle[socket_sn]);
        }
        else
        {
          return ret; // check SOCKERR_BUSY & SOCKERR_XXX. For showing the occurrence of SOCKERR_BUSY.
        }
      }
    }
    break;
  case SOCK_CLOSE_WAIT:
    if ((ret = disconnect(socket_sn)) != SOCK_OK)
      return ret;
    break;
  case SOCK_INIT:
    if ((ret = listen(socket_sn)) != SOCK_OK)
      return ret;
    break;
  case SOCK_CLOSED:
    if ((ret = socket(socket_sn, Sn_MR_TCP, localport, 0x00)) != socket_sn)
      return ret;
    break;
  default:
    break;
  }

  if (++socket_sn >= _WIZCHIP_SOCK_NUM_)
  {
    socket_sn = 0;
  }

  return 1;
}
