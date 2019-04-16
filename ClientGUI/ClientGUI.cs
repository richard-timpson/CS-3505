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

        /// <summary>
        /// Holds onto the spreadsheet and server connection
        /// </summary>
        private SpreadsheetController ssController;

        public ClientLogIn()
        {
            InitializeComponent();

            //--------------------ssController Initialization-------------------------------
            //On start up, set the Spreadsheet in the controller to null, since there
            //is no Spreadsheet associated with the client yet.
            ssController = new SpreadsheetController(new Spreadsheet(x => true, x => x.ToUpper(), "cs3505"));
            //Subscribe To Spreadsheets Received by updating ListOfSpreadsheets
            ssController.SpreadsheetsReceived += UpdateListOfSpreadsheets;
            ssController.SpreadsheetUpdated += UpdateSpreadsheet;
            ssController.InvalidUsername += UsernameInvalid;
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

            ssView = null;
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

            //If AddressTextBox is null, empty, or whitespace, connect to Generics Server.
            if (String.IsNullOrWhiteSpace(AddressTextBox.Text))
            {
                //use the controller to connect to the Generics Server
            }
            else //Otherwise, connect with the given address
            {
                try //To connect to server with given address
                {
                    ssController.Connect(AddressTextBox.Text);
                    NewSpreadsheetButton.Enabled = true;

                }
                catch //Fails to connect because of invalid address.
                {
                    //Handle invalid server error gracefully.
                    MessageBox.Show("Invalid Server Address.\n\nPlease enter a different address.",
                                    "Failed To Connect",
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Error);
                }
            }
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
            //Is the spreadsheet already open?
            if (ssView == null)
            {
                //Open a new SpreadsheetGUI if it isn't
                ssView = new SpreadsheetView(ssController);
                MethodInvoker m = new MethodInvoker(() => SpreadsheetAplicationContext.getAppContext().RunForm(ssView));//new SpreadsheetView(ssController)));
                this.Invoke(m);
                System.Diagnostics.Debug.WriteLine("Opened new form");

                ssView.PopulateSpreadsheet(cellDependencies);
                
            }
        }

        //private async Task<DialogResult> ShowDialogAsync(this Form @this)
        //{
        //    await Task.Yield();
        //    if (@this.IsDisposed)
        //        return DialogResult.OK;
        //    return @this.ShowDialog();
        //}

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
            MessageBox.Show("The specified username is invalid.\n\nUsernames cannot have whitespaces.", 
                            "Invalid Username", 
                            MessageBoxButtons.OK, 
                            MessageBoxIcon.Stop);
        }


    }
}

