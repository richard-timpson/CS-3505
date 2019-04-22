namespace ClientGUI
{
    partial class ClientLogIn
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
            this.TheGenericsLabel = new System.Windows.Forms.Label();
            this.OnlineSpreadsheetSuiteLabel = new System.Windows.Forms.Label();
            this.EnterUsernameAndPasswordLabel = new System.Windows.Forms.Label();
            this.UsernameLabel = new System.Windows.Forms.Label();
            this.UsernameTextBox = new System.Windows.Forms.TextBox();
            this.PasswordTextBox = new System.Windows.Forms.TextBox();
            this.PasswordLabel = new System.Windows.Forms.Label();
            this.AddressTextBox = new System.Windows.Forms.TextBox();
            this.AddressLabel = new System.Windows.Forms.Label();
            this.ListOfSpreadsheets = new System.Windows.Forms.ListBox();
            this.EditSpreadsheetButton = new System.Windows.Forms.Button();
            this.NewSpreadsheetButton = new System.Windows.Forms.Button();
            this.ConnectButton = new System.Windows.Forms.Button();
            this.AttemptingToConnectLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // TheGenericsLabel
            // 
            this.TheGenericsLabel.AutoSize = true;
            this.TheGenericsLabel.Font = new System.Drawing.Font("Arial", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TheGenericsLabel.Location = new System.Drawing.Point(43, 9);
            this.TheGenericsLabel.Name = "TheGenericsLabel";
            this.TheGenericsLabel.Size = new System.Drawing.Size(181, 32);
            this.TheGenericsLabel.TabIndex = 0;
            this.TheGenericsLabel.Text = "The Generics";
            // 
            // OnlineSpreadsheetSuiteLabel
            // 
            this.OnlineSpreadsheetSuiteLabel.AutoSize = true;
            this.OnlineSpreadsheetSuiteLabel.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OnlineSpreadsheetSuiteLabel.Location = new System.Drawing.Point(29, 50);
            this.OnlineSpreadsheetSuiteLabel.Name = "OnlineSpreadsheetSuiteLabel";
            this.OnlineSpreadsheetSuiteLabel.Size = new System.Drawing.Size(233, 23);
            this.OnlineSpreadsheetSuiteLabel.TabIndex = 1;
            this.OnlineSpreadsheetSuiteLabel.Text = "Online Spreadsheet Suite";
            // 
            // EnterUsernameAndPasswordLabel
            // 
            this.EnterUsernameAndPasswordLabel.AutoSize = true;
            this.EnterUsernameAndPasswordLabel.Location = new System.Drawing.Point(30, 93);
            this.EnterUsernameAndPasswordLabel.Name = "EnterUsernameAndPasswordLabel";
            this.EnterUsernameAndPasswordLabel.Size = new System.Drawing.Size(208, 17);
            this.EnterUsernameAndPasswordLabel.TabIndex = 2;
            this.EnterUsernameAndPasswordLabel.Text = "Enter Username and Password:";
            // 
            // UsernameLabel
            // 
            this.UsernameLabel.AutoSize = true;
            this.UsernameLabel.Location = new System.Drawing.Point(30, 121);
            this.UsernameLabel.Name = "UsernameLabel";
            this.UsernameLabel.Size = new System.Drawing.Size(77, 17);
            this.UsernameLabel.TabIndex = 3;
            this.UsernameLabel.Text = "Username:";
            // 
            // UsernameTextBox
            // 
            this.UsernameTextBox.Location = new System.Drawing.Point(31, 146);
            this.UsernameTextBox.Name = "UsernameTextBox";
            this.UsernameTextBox.Size = new System.Drawing.Size(206, 22);
            this.UsernameTextBox.TabIndex = 4;
            // 
            // PasswordTextBox
            // 
            this.PasswordTextBox.Location = new System.Drawing.Point(31, 217);
            this.PasswordTextBox.Name = "PasswordTextBox";
            this.PasswordTextBox.PasswordChar = '·';
            this.PasswordTextBox.Size = new System.Drawing.Size(206, 22);
            this.PasswordTextBox.TabIndex = 6;
            // 
            // PasswordLabel
            // 
            this.PasswordLabel.AutoSize = true;
            this.PasswordLabel.Location = new System.Drawing.Point(30, 192);
            this.PasswordLabel.Name = "PasswordLabel";
            this.PasswordLabel.Size = new System.Drawing.Size(73, 17);
            this.PasswordLabel.TabIndex = 5;
            this.PasswordLabel.Text = "Password:";
            // 
            // AddressTextBox
            // 
            this.AddressTextBox.Location = new System.Drawing.Point(31, 288);
            this.AddressTextBox.Name = "AddressTextBox";
            this.AddressTextBox.Size = new System.Drawing.Size(206, 22);
            this.AddressTextBox.TabIndex = 9;
            // 
            // AddressLabel
            // 
            this.AddressLabel.AutoSize = true;
            this.AddressLabel.Location = new System.Drawing.Point(30, 263);
            this.AddressLabel.Name = "AddressLabel";
            this.AddressLabel.Size = new System.Drawing.Size(64, 17);
            this.AddressLabel.TabIndex = 8;
            this.AddressLabel.Text = "Address:";
            // 
            // ListOfSpreadsheets
            // 
            this.ListOfSpreadsheets.FormattingEnabled = true;
            this.ListOfSpreadsheets.ItemHeight = 16;
            this.ListOfSpreadsheets.Location = new System.Drawing.Point(290, 18);
            this.ListOfSpreadsheets.Name = "ListOfSpreadsheets";
            this.ListOfSpreadsheets.Size = new System.Drawing.Size(533, 340);
            this.ListOfSpreadsheets.TabIndex = 10;
            this.ListOfSpreadsheets.SelectedIndexChanged += new System.EventHandler(this.ListOfSpreadsheets_SelectedIndexChanged);
            // 
            // EditSpreadsheetButton
            // 
            this.EditSpreadsheetButton.Location = new System.Drawing.Point(290, 372);
            this.EditSpreadsheetButton.Name = "EditSpreadsheetButton";
            this.EditSpreadsheetButton.Size = new System.Drawing.Size(206, 29);
            this.EditSpreadsheetButton.TabIndex = 11;
            this.EditSpreadsheetButton.Text = "Edit Spreadsheet";
            this.EditSpreadsheetButton.UseVisualStyleBackColor = true;
            this.EditSpreadsheetButton.Click += new System.EventHandler(this.EditSpreadsheetButton_Click);
            // 
            // NewSpreadsheetButton
            // 
            this.NewSpreadsheetButton.Location = new System.Drawing.Point(617, 372);
            this.NewSpreadsheetButton.Name = "NewSpreadsheetButton";
            this.NewSpreadsheetButton.Size = new System.Drawing.Size(206, 29);
            this.NewSpreadsheetButton.TabIndex = 12;
            this.NewSpreadsheetButton.Text = "New Spreadsheet";
            this.NewSpreadsheetButton.UseVisualStyleBackColor = true;
            this.NewSpreadsheetButton.Click += new System.EventHandler(this.NewSpreadsheetButton_Click);
            // 
            // ConnectButton
            // 
            this.ConnectButton.Location = new System.Drawing.Point(31, 316);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(103, 29);
            this.ConnectButton.TabIndex = 13;
            this.ConnectButton.Text = "Connect";
            this.ConnectButton.UseVisualStyleBackColor = true;
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // AttemptingToConnectLabel
            // 
            this.AttemptingToConnectLabel.AutoSize = true;
            this.AttemptingToConnectLabel.Location = new System.Drawing.Point(28, 372);
            this.AttemptingToConnectLabel.Name = "AttemptingToConnectLabel";
            this.AttemptingToConnectLabel.Size = new System.Drawing.Size(0, 17);
            this.AttemptingToConnectLabel.TabIndex = 14;
            // 
            // ClientLogIn
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(839, 413);
            this.Controls.Add(this.AttemptingToConnectLabel);
            this.Controls.Add(this.ConnectButton);
            this.Controls.Add(this.NewSpreadsheetButton);
            this.Controls.Add(this.EditSpreadsheetButton);
            this.Controls.Add(this.ListOfSpreadsheets);
            this.Controls.Add(this.AddressTextBox);
            this.Controls.Add(this.AddressLabel);
            this.Controls.Add(this.PasswordTextBox);
            this.Controls.Add(this.PasswordLabel);
            this.Controls.Add(this.UsernameTextBox);
            this.Controls.Add(this.UsernameLabel);
            this.Controls.Add(this.EnterUsernameAndPasswordLabel);
            this.Controls.Add(this.OnlineSpreadsheetSuiteLabel);
            this.Controls.Add(this.TheGenericsLabel);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "ClientLogIn";
            this.Text = "Online Spreadsheet Suite";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label TheGenericsLabel;
        private System.Windows.Forms.Label OnlineSpreadsheetSuiteLabel;
        private System.Windows.Forms.Label EnterUsernameAndPasswordLabel;
        private System.Windows.Forms.Label UsernameLabel;
        private System.Windows.Forms.TextBox UsernameTextBox;
        private System.Windows.Forms.TextBox PasswordTextBox;
        private System.Windows.Forms.Label PasswordLabel;
        private System.Windows.Forms.TextBox AddressTextBox;
        private System.Windows.Forms.Label AddressLabel;
        private System.Windows.Forms.ListBox ListOfSpreadsheets;
        private System.Windows.Forms.Button EditSpreadsheetButton;
        private System.Windows.Forms.Button NewSpreadsheetButton;
        private System.Windows.Forms.Button ConnectButton;
        private System.Windows.Forms.Label AttemptingToConnectLabel;
    }
}

