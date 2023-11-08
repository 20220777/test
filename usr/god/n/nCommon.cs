using System;
using System.Runtime.InteropServices;

namespace liblite.io.n
{
  public delegate int DlgtCallbackEx(Int32 fd, byte[] b, Int32 sz);

  public enum nLITE
  {
    __CALLBACK_CONNECTED = 0,
    __CALLBACK_DISCONNECTED,
    __CALLBACK_OPEN,
    __CALLBACK_CLOSE,
    __CALLBACK_STATUS,
    __CALLBACK_READ,
    __CALLBACK_READFROM,
    __CALLBACK_URI,
    __CALLBACK_URI_NOT_FOUND,
    __CALLBACK_POST,
    __CALLBACK_GET,
    __CALLBACK_SSL_TLS,
    __CALLBACK_SSL_TLS_READ,
    __CALLBACK_SSL_TLS_WRITE,
    __CALLBACK_PRE_OPEN,
    __CALLBACK,
    __IO_I,
    __IO_O,
    __IO_CLOSE,
    __IO_ACCEPT,
    __WRITE,
    __FD,
    __FDSET,
    __FUNCTIONS,
  };
}
