namespace SpreadsheetListGUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ListOfSpreadsheets = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // ListOfSpreadsheets
            // 
            this.ListOfSpreadsheets.FormattingEnabled = true;
            this.ListOfSpreadsheets.ItemHeight = 16;
            this.ListOfSpreadsheets.Location = new System.Drawing.Point(9, 11);
            this.ListOfSpreadsheets.Name = "ListOfSpreadsheets";
            this.ListOfSpreadsheets.Size = new System.Drawing.Size(537, 340);
            this.ListOfSpreadsheets.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.ListOfSpreadsheets);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox ListOfSpreadsheets;
    }
}

