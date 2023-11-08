using System;
using System.Runtime.InteropServices;

namespace liblite.io.n
{
  unsafe public partial class nSocket
  {
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    private delegate Int32 DlgtCallback(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __socket_fd(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __socket_read(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __socket_write(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __socket_open(out void* h, byte* argv, byte* b, Int32 sz, UInt32[] dlgt, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __socket_close(out void* h);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __socket_close_fd(void* h, Int32 fd);

    private void* hdl = null;
    Int32 fd = 0;
    byte[] buf = new byte[32];

    public DlgtCallbackEx[] _dlgtCallbackEx = new DlgtCallbackEx[(Int32)nLITE.__FUNCTIONS];
    private DlgtCallback[] _dlgtCallback = new DlgtCallback[(Int32)nLITE.__FUNCTIONS];
    UInt32[] fxps = new UInt32[(Int32)nLITE.__FUNCTIONS];

    public nSocket()
    {
      _dlgtCallback[(Int32)nLITE.__CALLBACK_READ] = new DlgtCallback(onCallbackRead);
      _dlgtCallback[(Int32)nLITE.__CALLBACK_STATUS] = new DlgtCallback(onCallbackStatus);

      fxps[(Int32)nLITE.__CALLBACK_READ] = (UInt32)Marshal.GetFunctionPointerForDelegate(_dlgtCallback[(Int32)nLITE.__CALLBACK_READ]);
      fxps[(Int32)nLITE.__CALLBACK_STATUS] = (UInt32)Marshal.GetFunctionPointerForDelegate(_dlgtCallback[(Int32)nLITE.__CALLBACK_STATUS]);

    }

    public Int32 Open(string argv1, string argv2, string argv3, string argv4, string argv5)
    {
      Int32 err = 0;
      string config = "{" +
                        "\"IP\":\"" + argv1 + "\"," +
                        "\"PORT\":\"" + argv2 + "\"," +
                        "\"CSTYPE\":\"" + argv3 + "\"," +
                        "\"PROTOCOL\":\"" + argv4 + "\"," +
                        "\"CASTTYPE\":\"" + argv5 + "\"," +
                        "\"SYNC\":\"DISABLE\"," +
                        "\"TIMEOUT\":\"4000000\"," +
                      "}";

      byte[] _config = new byte[config.Length];
      _config = System.Text.Encoding.UTF8.GetBytes(config);

      fixed (byte* _pconfig = _config)
      fixed (byte* _b = buf)
      {
        fd = err = __socket_open(out hdl, _pconfig, _b, 1024, fxps, null);
      }
      return err;
    }

    public Int32 Close(Int32 fd=-1)
    {
      Int32 err = 0;

      if (fd > 0) err = __socket_close_fd(hdl, fd);
      else err = __socket_close(out hdl);
      return err;
    }

    public Int32 Write(byte[] b, int sz)
    {
      Int32 err = 0;

      fixed (byte* _b = b)
      {
        err = __socket_write(hdl, fd, _b, sz, null, null);
      }

      return err;
    }

    Int32 onCallbackRead(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o)
    {
      Int32 err = 0;
      byte[] _b = new byte[sz];
      Marshal.Copy((IntPtr)b, _b, 0, sz);

      if (sz < 0) return 0;

      if (this._dlgtCallbackEx[(Int32)nLITE.__CALLBACK_READ] != null)
      {
        this._dlgtCallbackEx[(Int32)nLITE.__CALLBACK_READ].Invoke(fd, _b, sz);
      }

      return err;
    }
    Int32 onCallbackStatus(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o)
    {
      Int32 err = 0;
      byte[] _b = new byte[sz];
      Marshal.Copy((IntPtr)b, _b, 0, sz);


      switch ((UInt32)sz)
      {
        case 0xE000FD0B:
          break;

        case 0xE000FD0A:
          /////// Connected
          if (this._dlgtCallbackEx[(Int32)nLITE.__CALLBACK_CONNECTED] != null)
          {
            this._dlgtCallbackEx[(Int32)nLITE.__CALLBACK_CONNECTED].Invoke(fd, _b, sz);
          }
          break;

        case 0xE000FD0F:
          /////// DisConnected
          if (this._dlgtCallbackEx[(Int32)nLITE.__CALLBACK_DISCONNECTED] != null)
          {
            this._dlgtCallbackEx[(Int32)nLITE.__CALLBACK_DISCONNECTED].Invoke(fd, _b, sz);
          }
          break;
      }
      if (this._dlgtCallbackEx[(Int32)nLITE.__CALLBACK_STATUS] != null)
      {
        this._dlgtCallbackEx[(Int32)nLITE.__CALLBACK_STATUS].Invoke(fd, _b, sz);
      }

      return err;
    }


  }
}
