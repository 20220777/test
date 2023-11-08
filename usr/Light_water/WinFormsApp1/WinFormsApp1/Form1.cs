namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        

        public Form1()
        {
            InitializeComponent();
            string[] strImageFile = { @"C:\opt\team_c\usr\Light_water\WinFormsApp1\WinFormsApp1\Img\blurred-soft-people-meeting-table-260nw-714357475.jpg", @"C:\opt\team_c\usr\Light_water\WinFormsApp1\WinFormsApp1\Img\brighton-england-august-03-2019-260nw-1630338670.jpg", @"C:\opt\team_c\usr\Light_water\WinFormsApp1\WinFormsApp1\Img\contemporary-loft-office-interior-3d-260nw-1662227212.jpg" };
            int i = 0;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.pbView.Image = Image.FromFile(strImageFile[i].ToString());
            label2.Text = strImageFile[i].ToString();
        }
    }
}