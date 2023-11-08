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
  }
}
