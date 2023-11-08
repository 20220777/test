using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace wLiteConsole
{
  public partial class Form1 : Form
  {

    liblite.io.n.nSocket __socket = new liblite.io.n.nSocket();
    public Form1()
    {
      InitializeComponent();
      Init();
    }

    public void Init()
    {
      this.btnSocketOpen.Text = "OPEN";
      this.txtSocketIP.Text = "192.168.0.106";
      this.txtSocketPort.Text = "502";

      this.lstView.Columns.Add("no", 20);
      this.lstView.Columns.Add("log", 300);

      this.__socket._dlgtCallbackEx[(Int32)liblite.io.n.nLITE.__CALLBACK_READ] = new liblite.io.n.DlgtCallbackEx(__sockettRead);
      this.__socket._dlgtCallbackEx[(Int32)liblite.io.n.nLITE.__CALLBACK_CONNECTED] = new liblite.io.n.DlgtCallbackEx(__sockettConnected);
      this.__socket._dlgtCallbackEx[(Int32)liblite.io.n.nLITE.__CALLBACK_DISCONNECTED] = new liblite.io.n.DlgtCallbackEx(__sockettDisconnected);

      this.webBrowser1.Navigate("http://www.naver.com/");
    }
    public int __sockettConnected(int fd, byte[] b, int sz)
    {
      String[] log = { "1", String.Format("{0}", sz) };
      ListViewItem itm = new ListViewItem(log);

      if (lstView.InvokeRequired == true)
      {
        this.Invoke(new Action(delegate ()
        {
          lstView.Items.Add(itm);
        }));
      }
      return 0;
    }
    public int __sockettDisconnected(int fd, byte[] b, int sz)
    {
      String[] log = { "1", String.Format("{0}", sz) };
      ListViewItem itm = new ListViewItem(log);

      if (lstView.InvokeRequired == true)
      {
        this.Invoke(new Action(delegate ()
        {
          lstView.Items.Add(itm);
        }));
      }
      return 0;
    }
    public int __sockettRead(int fd, byte[] b, int sz)
    {
      String[] log = { "1", String.Format("{0}", sz) };
      ListViewItem itm = new ListViewItem(log);

      if (lstView.InvokeRequired == true)
      {
        this.Invoke(new Action(delegate ()
        {
          lstView.Items.Add(itm);
        }));
      }
      return 0;
    }

    private void btnSocketOpen_Click(object sender, EventArgs e)
    {
      if (this.btnSocketOpen.Text == "OPEN")
      {
        if (__socket.Open(this.txtSocketIP.Text, this.txtSocketPort.Text, "CLIENT", "TCP", "UNICAST") > 0)
        {
          this.btnSocketOpen.Text = "CLOSE";
        }
        else
        {
          this.btnSocketOpen.Text = "OPEN";
        }
      }
      else
      {
        __socket.Close();
        this.btnSocketOpen.Text = "OPEN";
      }
    }

    private void btnSerialWrite_Click(object sender, EventArgs e)
    {
      byte[] buf = new byte[32];
      Int32 sz = 0;

      buf[sz++] = 0x00;
      buf[sz++] = 0x01;

      buf[sz++] = 0x00;
      buf[sz++] = 0x00;

      buf[sz++] = 0x00;
      buf[sz++] = 0x06;

      buf[sz++] = 0x00;
      buf[sz++] = 0x03;

      buf[sz++] = 0x00;
      buf[sz++] = 0x00;

      buf[sz++] = 0x00;
      buf[sz++] = 0x08;

      __socket.Write(buf, sz);
    }
  }
}
