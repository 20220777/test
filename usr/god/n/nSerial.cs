using System;
using System.Runtime.InteropServices;

namespace liblite.io.n
{
  unsafe public partial class nSerial
  {
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    private delegate Int32 DlgtCallback(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __serial_fd(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __serial_read(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __serial_write(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __serial_open(out void* h, byte* argv, byte* b, Int32 sz, UInt32[] dlgt, void* o);

    [DllImport("lite.io.x86.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    private static extern Int32 __serial_close(out void* h);

    private void* hdl = null;
    Int32 fd = 0;
    byte[] buf = new byte[32];

    public DlgtCallbackEx _dlgtCallbackEx = null;
    private DlgtCallback[] _dlgtCallback = new DlgtCallback[(Int32)nLITE.__FUNCTIONS];
    UInt32[] fxps = new UInt32[(Int32)nLITE.__FUNCTIONS];

    public nSerial()
    {
      _dlgtCallback[(Int32)nLITE.__CALLBACK_READ] = new DlgtCallback(onCallbackRead);

      fxps[(Int32)nLITE.__CALLBACK_READ] = (UInt32)Marshal.GetFunctionPointerForDelegate(_dlgtCallback[(Int32)nLITE.__CALLBACK_READ]);
    }

    public Int32 Open(string argv1, string argv2, string argv3, string argv4, string argv5)
    {
      Int32 err = 0;
      string config = "{" +
                      "\"PORT\":\"" + argv1 + "\"," +
                      "\"BAUDRATE\":\"" + argv2 + "\"," +
                      "\"DATABIT\":\"8\"," +
                      "\"STOPBIT\":\"1\"," +
                      "\"PARITYBIT\":\"0\"," +
                      "\"BUF_SZ\":\"1\"," +
                      "\"SYNC\":\"DISABLE\"" +
                      "}";

      byte[] _config = new byte[config.Length];
      _config = System.Text.Encoding.UTF8.GetBytes(config);

      fixed (byte* _pconfig = _config)
      fixed (byte* _b = buf)
      {
        fd = err = __serial_open(out hdl, _pconfig, _b, 32, fxps, null);
      }
      return err;
    }

    public Int32 Close()
    {
      Int32 err = 0;
      err = __serial_close(out hdl);
      return err;
    }

    public Int32 Write(byte[] b, int sz)
    {
      Int32 err = 0;

      fixed (byte* _b = b)
      {
        err = __serial_write(hdl, fd, _b, sz, null, null);
      }

      return err;
    }


    Int32 onCallbackOpen(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o)
    {
      Int32 err = 0;
      //byte[] _b = new byte[sz];
      //Marshal.Copy((IntPtr)b, _b, 0, sz);

      //if (this._dlgtCallbackEx != null)
      //{
      //  this._dlgtCallbackEx.Invoke(fd, _b, sz);
      //}

      return err;
    }

    Int32 onCallbackClose(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o)
    {
      Int32 err = 0;
      //byte[] _b = new byte[sz];
      //Marshal.Copy((IntPtr)b, _b, 0, sz);

      //if (this._dlgtCallbackEx != null)
      //{
      //  this._dlgtCallbackEx.Invoke(fd, _b, sz);
      //}

      return err;
    }

    Int32 onCallbackRead(void* h, Int32 fd, byte* b, Int32 sz, void* extra, void* o)
    {
      Int32 err = 0;
      byte[] _b = new byte[sz];
      Marshal.Copy((IntPtr)b, _b, 0, sz);

      if (this._dlgtCallbackEx != null)
      {
        this._dlgtCallbackEx.Invoke(fd, _b, sz);
      }

      return err;
    }


  }
}
