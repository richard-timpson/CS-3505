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
        public Form1()
        {
            InitializeComponent();
            // Set the selection mode to multiple and extended.
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
        }
    }
}
