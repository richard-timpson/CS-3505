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
        /// Used to connect to the server
        /// </summary>
        private SpreadsheetController ssController;

        public ClientLogIn()
        {
            InitializeComponent();

            //On start up, set the Spreadsheet in the controller to null, since there
            //is no Spreadsheet associated with the client yet.
            ssController = new SpreadsheetController(null);
            

            //The client has not connected, disable the list of Spreadsheets
            ListOfSpreadsheets.Enabled = false;

            //Initial Connect before username/password?
            EditSpreadsheetButton.Enabled = false;
            NewSpreadsheetButton.Enabled = false;

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void TestPopulateListView()
        {
            ListOfSpreadsheets.Enabled = true;
            // Set the selection mode to one. Should we be able to select multiple?
            ListOfSpreadsheets.SelectionMode = SelectionMode.One;

            // Shutdown the painting of the ListView as items are added.
            ListOfSpreadsheets.BeginUpdate();
            // Loop through and add 100 items to the ListView.
            Random rng = new Random();
            for (int x = 1; x <= 100; x++)
            {
                string s = "";
                for (int i = 0; i < 5; i++)
                {
                    s += (char)(65 + rng.Next(27));
                }
                ListOfSpreadsheets.Items.Add(s);
            }
            // Allow the ListView to repaint and display the new items.
            ListOfSpreadsheets.EndUpdate();
            //
        }

        /// <summary>
        /// Sends the selected spreadsheet from the ListOfSpreadsheets to the server
        /// along with username, password, and IP address.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void EditSpreadsheetButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show(ListOfSpreadsheets.SelectedItem.ToString());
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
                //connectedToServer = true;
                }
                else //Otherwise, connect with the given address
                {
                    try
                    {
                        //connectedToServer = true;
                        //Maybe make another connect method with only an address argument?
                        ssController.Connect(AddressTextBox.Text, "", "");
                
                    }
                    catch //Fails to connect because of invalid address.
                    {
                        //connectedToServer = false;
                        //Handle invalid server error gracefully.
                        MessageBox.Show("Invalid Server Address.\n\nPlease enter a different address.",
                                        "Failed To Connect",
                                        MessageBoxButtons.OK,
                                        MessageBoxIcon.Error);
                    }
                }
                TestPopulateListView();
                NewSpreadsheetButton.Enabled = true;
                
            
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
    }
}
