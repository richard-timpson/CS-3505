using CS3505;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace SpreadsheetListGUI
{
    public partial class Form1 : Form
    {
        private SpreadsheetController ssController;
        public Form1()
        {
            InitializeComponent();
            InitializeSpreadsheetListBox();
        }

        /// <summary>
        /// Used when the Client GUI successfully connects and has a
        /// Spreadsheet controller with a SocketState on it.
        /// </summary>
        /// <param name="ssc">The Client GUI's Spreadsheet Controller</param>
        public Form1(SpreadsheetController ssc)
        {
            ssController = ssc;
            InitializeComponent();
            InitializeSpreadsheetListBox();
        }

        /// <summary>
        /// Starts up the ListOfSpreadsheetsListBox
        /// </summary>
        private void InitializeSpreadsheetListBox()
        {
            // Set the selection mode to one. Should we be able to select multiple?
            ListOfSpreadsheets.SelectionMode = SelectionMode.One;

            // Shutdown the painting of the ListBox as items are added.
            ListOfSpreadsheets.BeginUpdate();
            // Loop through and add 50 items to the ListBox.
            Random rng = new Random();
            for (int x = 1; x <= 50; x++)
            {
                string s = "";
                for (int i = 0; i < 5; i++)
                {
                    s += (char)(65 + rng.Next(27));
                }
                ListOfSpreadsheets.Items.Add(s);
            }
            // Allow the ListBox to repaint and display the new items.
            ListOfSpreadsheets.EndUpdate();
            //
        }
    }
}
