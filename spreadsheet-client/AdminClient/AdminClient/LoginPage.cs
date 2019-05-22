using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AdminClient
{
    public partial class LoginPage : Form
    {

        private Dictionary<string, int> namePasswordPair = new Dictionary<string, int>();
        public LoginPage()
        {
            InitializeComponent();
            namePasswordPair.Add("admin", "password".GetHashCode());
        }



        private void loginButton_Click(object sender, EventArgs e)
        {
            if (userNameTextBox.Text == "")
            {
                MessageBox.Show("Please enter a user name");
                return;
            }
            if (passwordTextBox.Text == "")
            {
                MessageBox.Show("Please enter a password");
                return;
            }
            if (!namePasswordPair.ContainsKey(userNameTextBox.Text))
            {
                MessageBox.Show("Unable to login. Please try again");
                userNameTextBox.Clear();
                passwordTextBox.Clear();
                return;
            }
            if (namePasswordPair[userNameTextBox.Text] == passwordTextBox.Text.GetHashCode())
            {
                if (!serverAddressTextBox.ToString().Equals(""))
                {
                    ServerControllerView.host = serverAddressTextBox.Text.ToString();
                }

                ServerControllerView.loggedIn = 1;
                this.Close();

            }
        }


    }
}
