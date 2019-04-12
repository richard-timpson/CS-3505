using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NewSpreadsheetDialog
{
    public partial class NewSpreadsheetDialogBox : Form
    {
        public static string NewSpreadsheetName;

        public NewSpreadsheetDialogBox()
        {
            InitializeComponent();
            NewSpreadsheetName = null;
        }

        private void OKButton_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(NewSpreadsheetNameTextBox.Text))
            {
                NewSpreadsheetName = NewSpreadsheetNameTextBox.Text;
            }
            this.Close();
        }

        private void CancelButton_Click(object sender, EventArgs e)
        {
            NewSpreadsheetName = null;
            this.Close();
        }

        private void NewSpreadsheetDialogBox_FormClosing(object sender, FormClosingEventArgs e)
        {
            NewSpreadsheetName = null;
        }
    }
}
