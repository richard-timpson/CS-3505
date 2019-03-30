using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientGUI
{
    public partial class ClientLogIn : Form
    {
        public ClientLogIn()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// Verifies if the username/password combination from UsernameTextBox
        /// and PasswordTextBox is valid. If it is, open a new window listing
        /// available spreadsheets. Otherwise, print an error.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LogInButton_Click(object sender, EventArgs e)
        {
            //Pack up the two strings into a string builder to be sent
            //To the server. The server will then either verify or deny
            //And sends according information back.

            //If it was a successful login attempt, open a new window
            //listing the list of available spreadsheets to edit.

            //If it is unsuccessful, pop up a dialog box explaining that
            //the username/password combination cannot be found.
            MessageBox.Show("Invalid Username/Password Combination.\n\nPlease try again.", 
                            "Invalid Username/Password", 
                            MessageBoxButtons.OK, 
                            MessageBoxIcon.Error);
        }

        /// <summary>
        /// Opens a new window allowing a user to register with a username
        /// and password.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NewUserButton_Click(object sender, EventArgs e)
        {

        }
    }
}
