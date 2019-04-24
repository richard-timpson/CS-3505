using CS3505;
using SpreadsheetGUI;
using SS;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace ClientGUI
{
    public partial class ClientLogIn : Form
    {
        private SpreadsheetView ssView;

        private string name = "";
        /// <summary>
        /// Holds onto the spreadsheet and server connection
        /// </summary>
        private SpreadsheetController ssController;

        public SpreadsheetView SSView
        {
            get
            {
                return ssView;
            }

        }
       
        public ClientLogIn()
        {
            InitializeComponent();

            //--------------------ssController Initialization-------------------------------
            //On start up, set the Spreadsheet in the controller to null, since there
            //is no Spreadsheet associated with the client yet.
            ssController = new SpreadsheetController(new Spreadsheet(x => true, x => x.ToUpper(), "cs3505"));
            ssController.SpreadsheetsReceived += UpdateListOfSpreadsheets;
            ssController.SpreadsheetUpdated += UpdateSpreadsheet;
            ssController.InvalidUsername += UsernameInvalid;
            ssController.InvalidPassword += PasswordInvalid;
            ssController.SpreadsheetError += ProcessError;
            ssController.ConnectionLostEvent += ConnectionLostNotification;
            ssController.DeniedConnection += ConnectionDenied;
            //------------------------------------------------------------------------------

            //----------ListOfSpreadsheets Initialization-------------------------------
            //There is no connection to the server yet, disable the ListOfSpreadsheets
            ListOfSpreadsheets.Enabled = false;
            //Only allow one Spreadsheet selection at a time
            ListOfSpreadsheets.SelectionMode = SelectionMode.One;
            //--------------------------------------------------------------------------

            //--------------------------Button Initialization---------------------------
            EditSpreadsheetButton.Enabled = false;
            NewSpreadsheetButton.Enabled = false;
            //--------------------------------------------------------------------------
  
            ssView = new SpreadsheetView(ssController);

        }

        /// <summary>
        /// Lets the user know that an invalid password was entered.
        /// Passwords cannot have commas.
        /// </summary>
        private void PasswordInvalid()
        {
            MessageBox.Show("The specified password is invalid.\n\nPasswords cannot have commas.",
                            "Invalid Password",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Stop);
        }

        /// <summary>
        /// When the connection is denied, notify the user
        /// and reenable the controls accordingly
        /// </summary>
        private void ConnectionDenied()
        {
            MessageBox.Show("The connection to " + AddressTextBox.Text + " has been denied.\n\nPlease verify the address and try again.",
                            "Connection Denied",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Warning);

            MethodInvoker mi = new MethodInvoker(() => EnableEverything(false));
            this.Invoke(mi);
        }

        /// <summary>
        /// notifies the user that the Connection was lost with the server
        /// </summary>
        private void ConnectionLostNotification()
        {
            if (!this.IsDisposed)
            {
                MessageBox.Show("Connection to the Server Was Lost Please Reconnect", "Connection Lost",
                                       MessageBoxButtons.OK,
                                       MessageBoxIcon.Warning);

                MethodInvoker m = new MethodInvoker(() => ListOfSpreadsheets.Items.Clear());
                this.Invoke(m);
            }
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// Method is called when the List of Spreadsheets from the server has been updated.
        /// Update the ListOfSpreadsheets to reflect as such.
        /// </summary>
        private void UpdateListOfSpreadsheets()
        {
            MethodInvoker m = new MethodInvoker(() => this.PopulateListOfSpreadsheets());
            this.Invoke(m);
        }

        /// <summary>
        /// Sends the selected spreadsheet from the ListOfSpreadsheets to the server
        /// along with username, password, and IP address.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void EditSpreadsheetButton_Click(object sender, EventArgs e)
        {
            //If a spreadsheet isn't selected, don't do anything
            if (ListOfSpreadsheets.SelectedItem == null)
            {
                return;
            }

            //Otherwise, send the message to open the spreadsheet
            System.Diagnostics.Debug.WriteLine(ListOfSpreadsheets.SelectedItem.ToString());
            name = ListOfSpreadsheets.SelectedItem.ToString();
            ssController.ChooseSpreadsheet(ListOfSpreadsheets.SelectedItem.ToString(), UsernameTextBox.Text, PasswordTextBox.Text);
          
        }

        /// <summary>
        /// Connect to the server with the specified address in the Address Text Box.
        /// If there is no value in the Address text box, it connects to The Generics
        /// server by default.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ConnectButton_Click(object sender, EventArgs e)
        {
            bool success = false;
            //If AddressTextBox is null, empty, or whitespace, connect to Generics Server.
            if (String.IsNullOrWhiteSpace(AddressTextBox.Text))
            {
                //use the controller to connect to the Generics Server
            }
            else //Otherwise, connect with the given address
            {
                
                try //To connect to server with given address
                {
                    //Disable controls while the client connects
                    DisableEverything();

                    //Connect
                    ssController.Connect(AddressTextBox.Text);
                    NewSpreadsheetButton.Enabled = true;
                    success = true;

                }
                catch //Fails to connect because of invalid address.
                {
                    //Handle invalid server error gracefully.
                    MessageBox.Show("Invalid Server Address.\n\nPlease enter a different address.",
                                    "Failed To Connect",
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Error);
                    success = false;
                }
            }

            //After the connection attempt is complete, reenable the controls accordingly
            EnableEverything(success);
        }

        /// <summary>
        /// Enables the EditSpreadsheetButton if something in ListOfSpreadsheets 
        /// is selected. If nothing is selected, the EditSpreadsheetButton will 
        /// remain disabled.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ListOfSpreadsheets_SelectedIndexChanged(object sender, EventArgs e)
        {
            EditSpreadsheetButton.Enabled = true;
        }


        /// <summary>
        /// Draws the list of available spreadsheets
        /// </summary>
        private void PopulateListOfSpreadsheets()
        {
            ListOfSpreadsheets.Enabled = true;


            // Shutdown the ListOfSpreadsheets as items are added.
            ListOfSpreadsheets.BeginUpdate();

            //If there are no Spreadsheets, don't update
            if (ssController.Sheets != null)
            {
                ListOfSpreadsheets.Items.Clear();
                //Go through the list of spreadsheets in the controller, and add them to the ListOfSpreadsheets
                for (int i = 0; i < ssController.Sheets.Length; i++)
                {
                    ListOfSpreadsheets.Items.Add(ssController.Sheets[i]);
                }
            }

            //After the painting has been finished, (Spreadsheets have been added)
            //Unlock the ListOfSpreadsheets
            ListOfSpreadsheets.EndUpdate();
        }

        /// <summary>
        /// Subscribes and updates a spreadsheet
        /// </summary>
        private void UpdateSpreadsheet(Dictionary<string, IEnumerable<string>> cellDependencies)
        {
            // Launch the SpreadsheetView
            if (!this.IsDisposed)
            {
                MethodInvoker m = new MethodInvoker(() => Program.runView(cellDependencies, name));
                this.Invoke(m);

                // Close the Client GUI
                MethodInvoker m1 = new MethodInvoker(() => this.Close());
                if (this.InvokeRequired)
                    this.Invoke(m1);
            }

        }


        private void ProcessError(int code, string source)
        {
            if(code == 1)
            {
                MessageBox.Show(source, "Connection Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        /// <summary>
        /// When the New Spreadsheet button is clicked, verify that the name
        /// doesn't exist, then create a new spreadsheet with the given name
        /// </summary>  
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NewSpreadsheetButton_Click(object sender, EventArgs e)
        {
            //prompt user to type in a new spreadsheet name
            string newSheetName = Interaction.InputBox("Enter name of new spreadsheet:", "New Spreadsheet", "", -1, -1);

            //If the string is not null or whitespace, two things could happen.
            //Either the Spreadsheet already exists, or it doesn't. The loop 
            //Allows users multiple opportunities to enter a valid spreadsheet name.
            while (!String.IsNullOrWhiteSpace(newSheetName))
            {
                //If the spreadsheet already exists, let the user know and allow them
                //another chance to write out a different spreadsheet name.
                if (ListOfSpreadsheets.Items.Contains(newSheetName))
                {
                    MessageBox.Show("The spreadsheet already exists.\n\nPlease enter a different name.",
                                    "Spreadsheet Already Exists",
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Stop);
                    newSheetName = Interaction.InputBox("Enter name of new spreadsheet:", "New Spreadsheet", "", -1, -1);
                }
                else //If the spreadsheet doesn't already exist, send a message to make a spreadsheet
                {
                    
                    name = newSheetName;
                    ssController.ChooseSpreadsheet(newSheetName, UsernameTextBox.Text, PasswordTextBox.Text);
                    break;
                }
            }

            //If the string is null or whitespace, the code will end up here, just do nothing
        }

        /// <summary>
        /// Happens when the user attempts to enter 
        /// a name that the Spreadsheet Controller
        /// doesn't like.
        /// </summary>
        private void UsernameInvalid()
        {
            MessageBox.Show("The specified username is invalid.\n\nUsernames cannot have commas.", 
                            "Invalid Username", 
                            MessageBoxButtons.OK, 
                            MessageBoxIcon.Stop);
        }

        /// <summary>
        /// When the connect button is clicked, disable the 
        /// controls so users don't mash buttons while connecting
        /// </summary>
        private void DisableEverything()
        {
            ListOfSpreadsheets.Enabled = false;
            NewSpreadsheetButton.Enabled = false;
            EditSpreadsheetButton.Enabled = false;
            ConnectButton.Enabled = false;
            UsernameTextBox.Enabled = false;
            PasswordTextBox.Enabled = false;
            AddressTextBox.Enabled = false;

            //Force the label to update so it shows up when attempting to connect
            AttemptingToConnectLabel.Text = "Attempting to connect to\n" + AddressTextBox.Text + "...";
            AttemptingToConnectLabel.Refresh();
        }

        /// <summary>
        /// Enables all of the controls that were disabled after
        /// the attempted connection
        /// </summary>
        /// <param name="success">whether or not there was a successful connection</param>
        private void EnableEverything(bool success)
        {
            //These should be reenabled if the connection is successful
            if (success)
            {
                NewSpreadsheetButton.Enabled = true;
                EditSpreadsheetButton.Enabled = true;
                ConnectButton.Text = "Connected";
            }
            else
            {
                //These should be reenabled if the connection fails
                ListOfSpreadsheets.Enabled = true;
                ConnectButton.Enabled = true;
                AddressTextBox.Enabled = true;
                ConnectButton.Text = "Connect";
            }
            //These should be reenabled regardless of the resulting connection
            UsernameTextBox.Enabled = true;
            PasswordTextBox.Enabled = true;
            AttemptingToConnectLabel.Text = "";

        }
    }
}

