using CS3505;
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
            ssController = new SpreadsheetController(null);
            //Subscribe To Spreadsheets Received by updating ListOfSpreadsheets
            ssController.SpreadsheetsReceived += UpdateListOfSpreadsheets;
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
            ListOfSpreadsheets.Enabled = true;


            // Shutdown the ListOfSpreadsheets as items are added.
            ListOfSpreadsheets.BeginUpdate();

            //If there are no Spreadsheets, don't update
            if (ssController.Sheets != null)
            {
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
        /// Sends the selected spreadsheet from the ListOfSpreadsheets to the server
        /// along with username, password, and IP address.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void EditSpreadsheetButton_Click(object sender, EventArgs e)
        {

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
            //DisableEverything();
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


        //private void DisableEverything()
        //{
        //    NewSpreadsheetButton.Enabled = false;
        //    EditSpreadsheetButton.Enabled = false;
        //    ConnectButton = false;

        //}
    }
}
