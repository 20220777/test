
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
      this.button1 = new System.Windows.Forms.Button();
      this.txtSocketPort = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // btnSocketOpen
      // 
      this.btnSocketOpen.Location = new System.Drawing.Point(832, 11);
      this.btnSocketOpen.Name = "btnSocketOpen";
      this.btnSocketOpen.Size = new System.Drawing.Size(87, 21);
      this.btnSocketOpen.TabIndex = 0;
      this.btnSocketOpen.Text = "button1";
      this.btnSocketOpen.UseVisualStyleBackColor = true;
      this.btnSocketOpen.Click += new System.EventHandler(this.btnSocketOpen_Click);
      // 
      // txtSocketIP
      // 
      this.txtSocketIP.Location = new System.Drawing.Point(14, 14);
      this.txtSocketIP.Name = "txtSocketIP";
      this.txtSocketIP.Size = new System.Drawing.Size(116, 21);
      this.txtSocketIP.TabIndex = 1;
      // 
      // button1
      // 
      this.button1.Location = new System.Drawing.Point(832, 64);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(75, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "button1";
      this.button1.UseVisualStyleBackColor = true;
      // 
      // txtSocketPort
      // 
      this.txtSocketPort.Location = new System.Drawing.Point(136, 14);
      this.txtSocketPort.Name = "txtSocketPort";
      this.txtSocketPort.Size = new System.Drawing.Size(100, 21);
      this.txtSocketPort.TabIndex = 3;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(933, 415);
      this.Controls.Add(this.txtSocketPort);
      this.Controls.Add(this.button1);
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
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.TextBox txtSocketPort;
  }
}

