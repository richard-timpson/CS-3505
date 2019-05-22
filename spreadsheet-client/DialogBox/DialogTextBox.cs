using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DialogBox
{
    public partial class DialogTextBox : Form
    {

        public string result;

        public DialogTextBox()
        {
            InitializeComponent();
        }

        public DialogTextBox(string dialogMessage, string dialogLabel)
        {
            GenericLabel.Text = dialogMessage;
            this.Text = dialogLabel;
            InitializeComponent();
            result = null;
        }

        private void OKButton_Click(object sender, EventArgs e)
        {
            result = AnswerTextBox.Text;
        }
    }
}
