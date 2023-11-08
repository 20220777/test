
namespace wLiteConsole
{
  partial class Form1
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.btnSocketOpen = new System.Windows.Forms.Button();
      this.txtSocketIP = new System.Windows.Forms.TextBox();
      this.btnSerialWrite = new System.Windows.Forms.Button();
      this.txtSocketPort = new System.Windows.Forms.TextBox();
      this.lstView = new System.Windows.Forms.ListView();
      this.webBrowser1 = new System.Windows.Forms.WebBrowser();
      this.SuspendLayout();
      // 
      // btnSocketOpen
      // 
      this.btnSocketOpen.Location = new System.Drawing.Point(731, 12);
      this.btnSocketOpen.Name = "btnSocketOpen";
      this.btnSocketOpen.Size = new System.Drawing.Size(75, 23);
      this.btnSocketOpen.TabIndex = 0;
      this.btnSocketOpen.Text = "button1";
      this.btnSocketOpen.UseVisualStyleBackColor = true;
      this.btnSocketOpen.Click += new System.EventHandler(this.btnSocketOpen_Click);
      // 
      // txtSocketIP
      // 
      this.txtSocketIP.Location = new System.Drawing.Point(12, 15);
      this.txtSocketIP.Name = "txtSocketIP";
      this.txtSocketIP.Size = new System.Drawing.Size(100, 20);
      this.txtSocketIP.TabIndex = 1;
      // 
      // btnSerialWrite
      // 
      this.btnSerialWrite.Location = new System.Drawing.Point(731, 41);
      this.btnSerialWrite.Name = "btnSerialWrite";
      this.btnSerialWrite.Size = new System.Drawing.Size(75, 25);
      this.btnSerialWrite.TabIndex = 2;
      this.btnSerialWrite.Text = "button1";
      this.btnSerialWrite.UseVisualStyleBackColor = true;
      this.btnSerialWrite.Click += new System.EventHandler(this.btnSerialWrite_Click);
      // 
      // txtSocketPort
      // 
      this.txtSocketPort.Location = new System.Drawing.Point(117, 15);
      this.txtSocketPort.Name = "txtSocketPort";
      this.txtSocketPort.Size = new System.Drawing.Size(86, 20);
      this.txtSocketPort.TabIndex = 3;
      // 
      // lstView
      // 
      this.lstView.GridLines = true;
      this.lstView.HideSelection = false;
      this.lstView.Location = new System.Drawing.Point(12, 434);
      this.lstView.Name = "lstView";
      this.lstView.Size = new System.Drawing.Size(794, 125);
      this.lstView.TabIndex = 4;
      this.lstView.TabStop = false;
      this.lstView.UseCompatibleStateImageBehavior = false;
      this.lstView.View = System.Windows.Forms.View.Details;
      // 
      // webBrowser1
      // 
      this.webBrowser1.Location = new System.Drawing.Point(12, 72);
      this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
      this.webBrowser1.Name = "webBrowser1";
      this.webBrowser1.Size = new System.Drawing.Size(794, 356);
      this.webBrowser1.TabIndex = 5;
      this.webBrowser1.TabStop = false;
      this.webBrowser1.Url = new System.Uri("http://127.0.0.1/", System.UriKind.Absolute);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(818, 571);
      this.Controls.Add(this.webBrowser1);
      this.Controls.Add(this.lstView);
      this.Controls.Add(this.txtSocketPort);
      this.Controls.Add(this.btnSerialWrite);
      this.Controls.Add(this.txtSocketIP);
      this.Controls.Add(this.btnSocketOpen);
      this.Name = "Form1";
      this.Text = "Form1";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button btnSocketOpen;
    private System.Windows.Forms.TextBox txtSocketIP;
    private System.Windows.Forms.Button btnSerialWrite;
    private System.Windows.Forms.TextBox txtSocketPort;
    private System.Windows.Forms.ListView lstView;
    private System.Windows.Forms.WebBrowser webBrowser1;
  }
}

