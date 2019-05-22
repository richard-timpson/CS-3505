using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AdminClient
{
    public partial class ServerControllerView : Form
    {
        //Variables
        ServerControllerControl Controler;
        public static int loggedIn = 0;
        public static string host = "127.0.0.1";
        public bool issuesLogingIn = false;
        private LoginPage ourLogin;
        private bool newSpreadsheetOpen = false, newUserOpen = false;

        /// <summary>
        /// Main starter for program. Calls LoginPage to start first. 
        /// Once LogingPage is finished, 
        /// </summary>
        public ServerControllerView()
        {

            LoginPage();


            if (loggedIn == 1)
            {
                Controler = new ServerControllerControl(this);
                Controler.closeEvent += unableToConnect;
                if (!issuesLogingIn)
                    InitializeComponent();
                else
                {

                    unableToConnect();
                    return;

                }

                spreadsheetListView.View = View.List;
                userListView.View = View.List;
                Thread.Sleep(1000);
                Controler.startGetData();

                // Set the view to show details.
                activeSpreadsheetsAndUsers.View = View.Details;
                // Allow the user to edit item text.
                activeSpreadsheetsAndUsers.LabelEdit = true;
                // Allow the user to rearrange columns.
                activeSpreadsheetsAndUsers.AllowColumnReorder = true;
                // Display check boxes.
                activeSpreadsheetsAndUsers.CheckBoxes = true;
                // Select the item and subitems when selection is made.
                activeSpreadsheetsAndUsers.FullRowSelect = true;
                // Display grid lines.
                activeSpreadsheetsAndUsers.GridLines = true;
                // Sort the items in the list in ascending order.
                activeSpreadsheetsAndUsers.Sorting = SortOrder.Ascending;
                activeSpreadsheetsAndUsers.CheckBoxes = false;

                // Create columns for the items and subitems.
                // Width of -2 indicates auto-size.
                activeSpreadsheetsAndUsers.Columns.Add("Spreadsheets", -2, HorizontalAlignment.Left);
                activeSpreadsheetsAndUsers.Columns.Add("Users", -2, HorizontalAlignment.Left);

            }
            else
                Close();

        }

        public void recieveListData(string[] listItem, int listNumber)
        {
            if (listNumber == 0)
            {


                MethodInvoker invalidater = new MethodInvoker(() => userListView.Clear());

                this.Invoke(invalidater);
                foreach (string now in listItem)
                {
                    MethodInvoker invalidater2 = new MethodInvoker(() => userListView.Items.Add(new ListViewItem(now)));

                    this.Invoke(invalidater2);
                }
            }
            else
            {

                MethodInvoker invalidater = new MethodInvoker(() => spreadsheetListView.Clear());

                this.Invoke(invalidater);
                foreach (string now in listItem)
                {
                    MethodInvoker invalidater2 = new MethodInvoker(() => spreadsheetListView.Items.Add(new ListViewItem(now)));

                    this.Invoke(invalidater2);
                }



            }
        }

        Dictionary<string, ListViewItem> activeSpreadsheetUserPair = new Dictionary<string, ListViewItem>();
        public void addActiveItems(string spreadsheetName, string[] users)
        {
            // Create three items and three sets of subitems for each item.
            Console.WriteLine("Trying to add to active Spreadsheet/users");
            ListViewItem item1 = new ListViewItem(spreadsheetName);
            // Place a check mark next to the item.
            StringBuilder listOfUsers = new StringBuilder();
            foreach (string now in users)
            {
                listOfUsers.Append(now + ", ");
            }
            Console.WriteLine(listOfUsers.ToString());
            MethodInvoker invalidater;
            item1.SubItems.Add(listOfUsers.ToString());
            if (activeSpreadsheetUserPair.ContainsKey(spreadsheetName))
            {
                MethodInvoker invalidater1;
                Console.WriteLine("Removing");
                ListViewItem toRemove = activeSpreadsheetUserPair[spreadsheetName];
                invalidater1 = new MethodInvoker(() => activeSpreadsheetsAndUsers.Items.Remove(toRemove));
                this.Invoke(invalidater1);
                activeSpreadsheetUserPair.Remove(spreadsheetName);
            }
            Console.WriteLine("Going to add");
            activeSpreadsheetUserPair.Add(spreadsheetName, item1);
            invalidater = new MethodInvoker(() => activeSpreadsheetsAndUsers.Items.Add(item1));

            this.Invoke(invalidater);
        }


        /// <summary>
        /// Shows a dialog box with issues then closes the program
        /// </summary>
        public void unableToConnect()
        {
            MessageBox.Show("Cannot Connect To Server. Please Check Connection. Program will now close");
            issuesLogingIn = true;

            Close();
            return;
        }
        /// <summary>
        /// shows dialog box with issues then closes the program
        /// </summary>
        public void unableToLoginin()
        {
            MessageBox.Show("Cannot Login. Please try again later");

            Close();
            return;
        }

        /// <summary>
        /// Runs login page 
        /// </summary>
        public void LoginPage()
        {
            ourLogin = new LoginPage();
            Application.Run(ourLogin);

        }
        /// <summary>
        /// cuts contact with the server and closes the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void logoutButton_Click(object sender, EventArgs e)
        {
            DialogResult turnOff = MessageBox.Show("Are you sure you want to log out?", "Log out Confirmation", MessageBoxButtons.OKCancel);

            if (turnOff == DialogResult.OK)
            {
                logTextBox.AppendText("Ending Connection and logging out");
                Controler.endContact();
                this.Close();
            }
        }
        /// <summary>
        /// turns the server off or on
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void offButton_Click(object sender, EventArgs e)
        {

            DialogResult turnOff = MessageBox.Show("Are you sure you want to turn off the server?", "Turn off server Confrimation", MessageBoxButtons.OKCancel);

            if (turnOff == DialogResult.OK)
            {
                logTextBox.AppendText("Sending Turn off Message");
                Controler.SendCommand(new OperationAdmin("OFF", "", ""));
                Controler.endContact();
                this.addUserButton.Visible = false;
                this.addUserButton.Enabled = false;

                userListView.Clear();
                spreadsheetListView.Clear();
                spreadsheetListView.Enabled = false;
                userListView.Enabled = false;
                logTextBox.AppendText("Preparing to close");
                MessageBox.Show("Server Off message sent. Program will now close");
                Close();
            }

        }
        /// <summary>
        /// Allows use of adding a user and confirmation button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void addUserButton_Click(object sender, EventArgs e)
        {
            newUserOpen = true;
            if (newSpreadsheetOpen)
                closeNewSpreadsheetItems();

            cancelButton.Enabled = true;
            cancelButton.Visible = true;

            newUserTextBox.Enabled = true;
            newUserLabel.Enabled = true;
            newPasswordLabel.Enabled = true;
            newPasswordTextBox.Enabled = true;
            confirmAddUserButton.Enabled = true;

            newUserTextBox.Visible = true;
            newUserLabel.Visible = true;
            newPasswordLabel.Visible = true;
            newPasswordTextBox.Visible = true;
            confirmAddUserButton.Visible = true;
        }

        /// <summary>
        /// Sends request to add a user 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void confirmAddUserButton_Click(object sender, EventArgs e)
        {
            if (newUserTextBox.Text == "" || newPasswordTextBox.Text == "")
            {
                MessageBox.Show("Please enter a new name and password");
                return;
            }
            Controler.SendCommand(new OperationAdmin("AU", newUserTextBox.Text.ToString(), newPasswordTextBox.Text.ToString()));
            logTextBox.AppendText("Add User Command sent for " + newUserTextBox.Text + "\n");
            closeNewUserItems();

        }

        /// <summary>
        /// Closes the new user items after clearing them
        /// </summary>
        private void closeNewUserItems()
        {
            newUserTextBox.Clear();
            newPasswordTextBox.Clear();

            newUserTextBox.Enabled = false;
            newUserLabel.Enabled = false;
            newPasswordLabel.Enabled = false;
            newPasswordTextBox.Enabled = false;
            confirmAddUserButton.Enabled = false;

            newUserTextBox.Visible = false;
            newUserLabel.Visible = false;
            newPasswordLabel.Visible = false;
            newPasswordTextBox.Visible = false;
            confirmAddUserButton.Visible = false;

            cancelButton.Enabled = false;
            cancelButton.Visible = false;
        }

        /// <summary>
        /// opens the new spreadsheed options and closes the new user options if needs be
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void addSpreadsheetButton_Click(object sender, EventArgs e)
        {
            newSpreadsheetOpen = true;
            if (newUserOpen)
                closeNewUserItems();

            cancelButton.Enabled = true;
            cancelButton.Visible = true;

            newSpreadhseetTextBox.Enabled = true;
            confirmNewSpreadsheetButton.Enabled = true;
            newSpreadsheetNameLabel.Enabled = true;

            newSpreadhseetTextBox.Visible = true;
            confirmNewSpreadsheetButton.Visible = true;
            newSpreadsheetNameLabel.Visible = true;
        }

        private void confirmNewSpreadsheetButton_Click(object sender, EventArgs e)
        {
            if (newSpreadhseetTextBox.Text == "")
            {
                MessageBox.Show("Please enter a the new Spreadsheet Name");
                return;
            }
            Controler.SendCommand(new OperationAdmin("AS", newSpreadhseetTextBox.Text.ToString(), ""));
            logTextBox.AppendText("Add Spreadsheet Command sent for " + newSpreadhseetTextBox.Text + "\n");
            closeNewSpreadsheetItems();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            closeNewSpreadsheetItems();
            closeNewUserItems();
        }

        private void closeNewSpreadsheetItems()
        {
            newSpreadhseetTextBox.Clear();

            newSpreadhseetTextBox.Enabled = false;
            confirmNewSpreadsheetButton.Enabled = false;
            newSpreadsheetNameLabel.Enabled = false;

            newSpreadhseetTextBox.Visible = false;
            confirmNewSpreadsheetButton.Visible = false;
            newSpreadsheetNameLabel.Visible = false;

            cancelButton.Enabled = false;
            cancelButton.Visible = false;
        }

        private void userListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            deleteUserButton.Enabled = true;
            deleteUserButton.Visible = true;


        }

        private void spreadsheetListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            deleteSpreadsheetButton.Visible = true;
            deleteSpreadsheetButton.Enabled = true;
        }

        private void deleteUserButton_Click(object sender, EventArgs e)
        {
            ListView.SelectedListViewItemCollection toDelete = userListView.SelectedItems;
            StringBuilder hold = new StringBuilder();
            foreach (ListViewItem now in toDelete)
            {
                string[] touse = now.Text.Split();
                hold.Append(touse[0]);
                hold.Append("\n");
            }
            DialogResult dialogResult = MessageBox.Show("Do you want to delete the following users:\n" + hold + "?", "Delete Users confirmation", MessageBoxButtons.OKCancel);
            if (dialogResult == DialogResult.OK)
            {
                foreach (ListViewItem now in toDelete)
                {

                    string[] touse = now.Text.Split();

                    string item = touse[0];
                    Controler.SendCommand(new OperationAdmin("DU", item, ""));

                }

                deleteUserButton.Enabled = false;
                deleteUserButton.Visible = false;
                logTextBox.AppendText("Delete user(s) message sent");
            }
        }

        public void clearActiveItems()
        {
            MethodInvoker invalidater2 = new MethodInvoker(() => activeSpreadsheetsAndUsers.Items.Clear());

            this.Invoke(invalidater2);
        }

        private void deleteSpreadsheetButton_Click(object sender, EventArgs e)
        {
            ListView.SelectedListViewItemCollection toDelete = spreadsheetListView.SelectedItems;

            StringBuilder hold = new StringBuilder();
            foreach (ListViewItem now in toDelete)
            {
                hold.Append(now.Text);
                hold.Append("\n");
            }
            DialogResult dialogResult = MessageBox.Show("Do you want to delete the following spreadsheets: \n" + hold + "?", "Delete Users confirmation", MessageBoxButtons.OKCancel);
            if (dialogResult == DialogResult.OK)
            {
                foreach (ListViewItem now in toDelete)
                {
                    string item = now.Text;
                    Controler.SendCommand(new OperationAdmin("DS", item, ""));
                }

                deleteSpreadsheetButton.Visible = false;
                deleteSpreadsheetButton.Enabled = false;
                logTextBox.AppendText("Delete spreadsheet(s) command sent\n");
            }
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            Controler.SendCommand(new OperationAdmin("R", "", ""));
        }

        private void newUserTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        public void errorMessageShow(string error)
        {
            MessageBox.Show("Error Recieved: " + error);
        }

    }
}
