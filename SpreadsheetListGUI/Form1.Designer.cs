namespace SpreadsheetListGUI
{
    partial class SpreadsheetSuiteGUI
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
            this.EditSpreadsheetButton = new System.Windows.Forms.Button();
            this.LogOutButton = new System.Windows.Forms.Button();
            this.NewSpreadsheetButton = new System.Windows.Forms.Button();
            this.AvailableSpreadsheetsLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // ListOfSpreadsheets
            // 
            this.ListOfSpreadsheets.FormattingEnabled = true;
            this.ListOfSpreadsheets.ItemHeight = 16;
            this.ListOfSpreadsheets.Location = new System.Drawing.Point(12, 98);
            this.ListOfSpreadsheets.Name = "ListOfSpreadsheets";
            this.ListOfSpreadsheets.Size = new System.Drawing.Size(537, 340);
            this.ListOfSpreadsheets.TabIndex = 0;
            // 
            // EditSpreadsheetButton
            // 
            this.EditSpreadsheetButton.Location = new System.Drawing.Point(555, 146);
            this.EditSpreadsheetButton.Name = "EditSpreadsheetButton";
            this.EditSpreadsheetButton.Size = new System.Drawing.Size(149, 42);
            this.EditSpreadsheetButton.TabIndex = 1;
            this.EditSpreadsheetButton.Text = "Edit Spreadsheet";
            this.EditSpreadsheetButton.UseVisualStyleBackColor = true;
            // 
            // LogOutButton
            // 
            this.LogOutButton.Location = new System.Drawing.Point(688, 12);
            this.LogOutButton.Name = "LogOutButton";
            this.LogOutButton.Size = new System.Drawing.Size(100, 35);
            this.LogOutButton.TabIndex = 2;
            this.LogOutButton.Text = "Log Out";
            this.LogOutButton.UseVisualStyleBackColor = true;
            // 
            // NewSpreadsheetButton
            // 
            this.NewSpreadsheetButton.Location = new System.Drawing.Point(555, 98);
            this.NewSpreadsheetButton.Name = "NewSpreadsheetButton";
            this.NewSpreadsheetButton.Size = new System.Drawing.Size(149, 42);
            this.NewSpreadsheetButton.TabIndex = 3;
            this.NewSpreadsheetButton.Text = "New Spreadsheet";
            this.NewSpreadsheetButton.UseVisualStyleBackColor = true;
            // 
            // AvailableSpreadsheetsLabel
            // 
            this.AvailableSpreadsheetsLabel.AutoSize = true;
            this.AvailableSpreadsheetsLabel.Location = new System.Drawing.Point(9, 68);
            this.AvailableSpreadsheetsLabel.Name = "AvailableSpreadsheetsLabel";
            this.AvailableSpreadsheetsLabel.Size = new System.Drawing.Size(157, 17);
            this.AvailableSpreadsheetsLabel.TabIndex = 4;
            this.AvailableSpreadsheetsLabel.Text = "Available Spreadsheets";
            // 
            // SpreadsheetSuiteGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.AvailableSpreadsheetsLabel);
            this.Controls.Add(this.NewSpreadsheetButton);
            this.Controls.Add(this.LogOutButton);
            this.Controls.Add(this.EditSpreadsheetButton);
            this.Controls.Add(this.ListOfSpreadsheets);
            this.Name = "SpreadsheetSuiteGUI";
            this.Text = "Spreadsheet Suite";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox ListOfSpreadsheets;
        private System.Windows.Forms.Button EditSpreadsheetButton;
        private System.Windows.Forms.Button LogOutButton;
        private System.Windows.Forms.Button NewSpreadsheetButton;
        private System.Windows.Forms.Label AvailableSpreadsheetsLabel;
    }
}

