namespace AdminClient
{
    partial class ServerControllerView
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
            this.offButton = new System.Windows.Forms.Button();
            this.logoutButton = new System.Windows.Forms.Button();
            this.userListView = new System.Windows.Forms.ListView();
            this.spreadsheetListView = new System.Windows.Forms.ListView();
            this.addUserButton = new System.Windows.Forms.Button();
            this.addSpreadsheetButton = new System.Windows.Forms.Button();
            this.confirmAddUserButton = new System.Windows.Forms.Button();
            this.newUserTextBox = new System.Windows.Forms.TextBox();
            this.newPasswordTextBox = new System.Windows.Forms.TextBox();
            this.newUserLabel = new System.Windows.Forms.Label();
            this.newPasswordLabel = new System.Windows.Forms.Label();
            this.confirmNewSpreadsheetButton = new System.Windows.Forms.Button();
            this.newSpreadhseetTextBox = new System.Windows.Forms.TextBox();
            this.newSpreadsheetNameLabel = new System.Windows.Forms.Label();
            this.logTextBox = new System.Windows.Forms.RichTextBox();
            this.logLabel = new System.Windows.Forms.Label();
            this.cancelButton = new System.Windows.Forms.Button();
            this.deleteUserButton = new System.Windows.Forms.Button();
            this.deleteSpreadsheetButton = new System.Windows.Forms.Button();
            this.activeSpreadsheetsAndUsers = new System.Windows.Forms.ListView();
            this.usersLabel = new System.Windows.Forms.Label();
            this.spreadsheetsLabel = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // offButton
            // 
            this.offButton.Location = new System.Drawing.Point(13, 16);
            this.offButton.Name = "offButton";
            this.offButton.Size = new System.Drawing.Size(100, 50);
            this.offButton.TabIndex = 0;
            this.offButton.Text = "Turn Off";
            this.offButton.UseVisualStyleBackColor = true;
            this.offButton.Click += new System.EventHandler(this.offButton_Click);
            // 
            // logoutButton
            // 
            this.logoutButton.Location = new System.Drawing.Point(12, 74);
            this.logoutButton.Name = "logoutButton";
            this.logoutButton.Size = new System.Drawing.Size(100, 50);
            this.logoutButton.TabIndex = 1;
            this.logoutButton.Text = "Logout";
            this.logoutButton.UseVisualStyleBackColor = true;
            this.logoutButton.Click += new System.EventHandler(this.logoutButton_Click);
            // 
            // userListView
            // 
            this.userListView.Location = new System.Drawing.Point(156, 31);
            this.userListView.Name = "userListView";
            this.userListView.Size = new System.Drawing.Size(200, 386);
            this.userListView.TabIndex = 2;
            this.userListView.UseCompatibleStateImageBehavior = false;
            this.userListView.SelectedIndexChanged += new System.EventHandler(this.userListView_SelectedIndexChanged);
            // 
            // spreadsheetListView
            // 
            this.spreadsheetListView.Location = new System.Drawing.Point(362, 31);
            this.spreadsheetListView.Name = "spreadsheetListView";
            this.spreadsheetListView.Size = new System.Drawing.Size(174, 386);
            this.spreadsheetListView.TabIndex = 3;
            this.spreadsheetListView.UseCompatibleStateImageBehavior = false;
            this.spreadsheetListView.SelectedIndexChanged += new System.EventHandler(this.spreadsheetListView_SelectedIndexChanged);
            // 
            // addUserButton
            // 
            this.addUserButton.ForeColor = System.Drawing.Color.ForestGreen;
            this.addUserButton.Location = new System.Drawing.Point(13, 149);
            this.addUserButton.Name = "addUserButton";
            this.addUserButton.Size = new System.Drawing.Size(100, 50);
            this.addUserButton.TabIndex = 4;
            this.addUserButton.Text = "Add User";
            this.addUserButton.UseVisualStyleBackColor = true;
            this.addUserButton.Click += new System.EventHandler(this.addUserButton_Click);
            // 
            // addSpreadsheetButton
            // 
            this.addSpreadsheetButton.ForeColor = System.Drawing.Color.ForestGreen;
            this.addSpreadsheetButton.Location = new System.Drawing.Point(13, 207);
            this.addSpreadsheetButton.Name = "addSpreadsheetButton";
            this.addSpreadsheetButton.Size = new System.Drawing.Size(100, 50);
            this.addSpreadsheetButton.TabIndex = 5;
            this.addSpreadsheetButton.Text = "Add Spreadsheet";
            this.addSpreadsheetButton.UseVisualStyleBackColor = true;
            this.addSpreadsheetButton.Click += new System.EventHandler(this.addSpreadsheetButton_Click);
            // 
            // confirmAddUserButton
            // 
            this.confirmAddUserButton.Enabled = false;
            this.confirmAddUserButton.Location = new System.Drawing.Point(1049, 74);
            this.confirmAddUserButton.Name = "confirmAddUserButton";
            this.confirmAddUserButton.Size = new System.Drawing.Size(133, 23);
            this.confirmAddUserButton.TabIndex = 6;
            this.confirmAddUserButton.Text = "Confirm Add User";
            this.confirmAddUserButton.UseVisualStyleBackColor = true;
            this.confirmAddUserButton.Visible = false;
            this.confirmAddUserButton.Click += new System.EventHandler(this.confirmAddUserButton_Click);
            // 
            // newUserTextBox
            // 
            this.newUserTextBox.Enabled = false;
            this.newUserTextBox.Location = new System.Drawing.Point(1049, 22);
            this.newUserTextBox.Name = "newUserTextBox";
            this.newUserTextBox.Size = new System.Drawing.Size(138, 20);
            this.newUserTextBox.TabIndex = 7;
            this.newUserTextBox.Visible = false;
            // 
            // newPasswordTextBox
            // 
            this.newPasswordTextBox.Enabled = false;
            this.newPasswordTextBox.Location = new System.Drawing.Point(1049, 48);
            this.newPasswordTextBox.Name = "newPasswordTextBox";
            this.newPasswordTextBox.Size = new System.Drawing.Size(138, 20);
            this.newPasswordTextBox.TabIndex = 8;
            this.newPasswordTextBox.Visible = false;
            // 
            // newUserLabel
            // 
            this.newUserLabel.AutoSize = true;
            this.newUserLabel.Enabled = false;
            this.newUserLabel.Location = new System.Drawing.Point(958, 29);
            this.newUserLabel.Name = "newUserLabel";
            this.newUserLabel.Size = new System.Drawing.Size(85, 13);
            this.newUserLabel.TabIndex = 9;
            this.newUserLabel.Text = "New User Name";
            this.newUserLabel.Visible = false;
            // 
            // newPasswordLabel
            // 
            this.newPasswordLabel.AutoSize = true;
            this.newPasswordLabel.Enabled = false;
            this.newPasswordLabel.Location = new System.Drawing.Point(965, 51);
            this.newPasswordLabel.Name = "newPasswordLabel";
            this.newPasswordLabel.Size = new System.Drawing.Size(78, 13);
            this.newPasswordLabel.TabIndex = 10;
            this.newPasswordLabel.Text = "New Password";
            this.newPasswordLabel.Visible = false;
            // 
            // confirmNewSpreadsheetButton
            // 
            this.confirmNewSpreadsheetButton.Enabled = false;
            this.confirmNewSpreadsheetButton.Location = new System.Drawing.Point(968, 162);
            this.confirmNewSpreadsheetButton.Name = "confirmNewSpreadsheetButton";
            this.confirmNewSpreadsheetButton.Size = new System.Drawing.Size(189, 23);
            this.confirmNewSpreadsheetButton.TabIndex = 11;
            this.confirmNewSpreadsheetButton.Text = "Confirm New Spreadsheet";
            this.confirmNewSpreadsheetButton.UseVisualStyleBackColor = true;
            this.confirmNewSpreadsheetButton.Visible = false;
            this.confirmNewSpreadsheetButton.Click += new System.EventHandler(this.confirmNewSpreadsheetButton_Click);
            // 
            // newSpreadhseetTextBox
            // 
            this.newSpreadhseetTextBox.Enabled = false;
            this.newSpreadhseetTextBox.Location = new System.Drawing.Point(1071, 132);
            this.newSpreadhseetTextBox.Name = "newSpreadhseetTextBox";
            this.newSpreadhseetTextBox.Size = new System.Drawing.Size(111, 20);
            this.newSpreadhseetTextBox.TabIndex = 12;
            this.newSpreadhseetTextBox.Visible = false;
            // 
            // newSpreadsheetNameLabel
            // 
            this.newSpreadsheetNameLabel.AutoSize = true;
            this.newSpreadsheetNameLabel.Enabled = false;
            this.newSpreadsheetNameLabel.Location = new System.Drawing.Point(942, 135);
            this.newSpreadsheetNameLabel.Name = "newSpreadsheetNameLabel";
            this.newSpreadsheetNameLabel.Size = new System.Drawing.Size(123, 13);
            this.newSpreadsheetNameLabel.TabIndex = 13;
            this.newSpreadsheetNameLabel.Text = "New Spreadsheet Name";
            this.newSpreadsheetNameLabel.Visible = false;
            // 
            // logTextBox
            // 
            this.logTextBox.Location = new System.Drawing.Point(945, 252);
            this.logTextBox.Name = "logTextBox";
            this.logTextBox.Size = new System.Drawing.Size(237, 164);
            this.logTextBox.TabIndex = 14;
            this.logTextBox.Text = "";
            // 
            // logLabel
            // 
            this.logLabel.AutoSize = true;
            this.logLabel.Location = new System.Drawing.Point(1027, 236);
            this.logLabel.Name = "logLabel";
            this.logLabel.Size = new System.Drawing.Size(71, 13);
            this.logLabel.TabIndex = 15;
            this.logLabel.Text = "Message Log";
            // 
            // cancelButton
            // 
            this.cancelButton.Enabled = false;
            this.cancelButton.Location = new System.Drawing.Point(1023, 210);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 16;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Visible = false;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // deleteUserButton
            // 
            this.deleteUserButton.Enabled = false;
            this.deleteUserButton.ForeColor = System.Drawing.Color.DarkRed;
            this.deleteUserButton.Location = new System.Drawing.Point(12, 276);
            this.deleteUserButton.Name = "deleteUserButton";
            this.deleteUserButton.Size = new System.Drawing.Size(109, 50);
            this.deleteUserButton.TabIndex = 17;
            this.deleteUserButton.Text = "Delete User";
            this.deleteUserButton.UseVisualStyleBackColor = true;
            this.deleteUserButton.Visible = false;
            this.deleteUserButton.Click += new System.EventHandler(this.deleteUserButton_Click);
            // 
            // deleteSpreadsheetButton
            // 
            this.deleteSpreadsheetButton.Enabled = false;
            this.deleteSpreadsheetButton.ForeColor = System.Drawing.Color.DarkRed;
            this.deleteSpreadsheetButton.Location = new System.Drawing.Point(12, 332);
            this.deleteSpreadsheetButton.Name = "deleteSpreadsheetButton";
            this.deleteSpreadsheetButton.Size = new System.Drawing.Size(110, 50);
            this.deleteSpreadsheetButton.TabIndex = 18;
            this.deleteSpreadsheetButton.Text = "Delete Spreadsheet";
            this.deleteSpreadsheetButton.UseVisualStyleBackColor = true;
            this.deleteSpreadsheetButton.Visible = false;
            this.deleteSpreadsheetButton.Click += new System.EventHandler(this.deleteSpreadsheetButton_Click);
            // 
            // activeSpreadsheetsAndUsers
            // 
            this.activeSpreadsheetsAndUsers.Location = new System.Drawing.Point(542, 30);
            this.activeSpreadsheetsAndUsers.Name = "activeSpreadsheetsAndUsers";
            this.activeSpreadsheetsAndUsers.Size = new System.Drawing.Size(377, 387);
            this.activeSpreadsheetsAndUsers.TabIndex = 19;
            this.activeSpreadsheetsAndUsers.UseCompatibleStateImageBehavior = false;
            // 
            // usersLabel
            // 
            this.usersLabel.AutoSize = true;
            this.usersLabel.Location = new System.Drawing.Point(234, 9);
            this.usersLabel.Name = "usersLabel";
            this.usersLabel.Size = new System.Drawing.Size(34, 13);
            this.usersLabel.TabIndex = 20;
            this.usersLabel.Text = "Users";
            // 
            // spreadsheetsLabel
            // 
            this.spreadsheetsLabel.AutoSize = true;
            this.spreadsheetsLabel.Location = new System.Drawing.Point(411, 9);
            this.spreadsheetsLabel.Name = "spreadsheetsLabel";
            this.spreadsheetsLabel.Size = new System.Drawing.Size(72, 13);
            this.spreadsheetsLabel.TabIndex = 21;
            this.spreadsheetsLabel.Text = "Spreadsheets";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(654, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(156, 13);
            this.label3.TabIndex = 22;
            this.label3.Text = "Active Spreadsheets and Users";
            // 
            // ServerControllerView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1190, 446);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.spreadsheetsLabel);
            this.Controls.Add(this.usersLabel);
            this.Controls.Add(this.activeSpreadsheetsAndUsers);
            this.Controls.Add(this.deleteSpreadsheetButton);
            this.Controls.Add(this.deleteUserButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.logLabel);
            this.Controls.Add(this.logTextBox);
            this.Controls.Add(this.newSpreadsheetNameLabel);
            this.Controls.Add(this.newSpreadhseetTextBox);
            this.Controls.Add(this.confirmNewSpreadsheetButton);
            this.Controls.Add(this.newPasswordLabel);
            this.Controls.Add(this.newUserLabel);
            this.Controls.Add(this.newPasswordTextBox);
            this.Controls.Add(this.newUserTextBox);
            this.Controls.Add(this.confirmAddUserButton);
            this.Controls.Add(this.addSpreadsheetButton);
            this.Controls.Add(this.addUserButton);
            this.Controls.Add(this.spreadsheetListView);
            this.Controls.Add(this.userListView);
            this.Controls.Add(this.logoutButton);
            this.Controls.Add(this.offButton);
            this.MinimumSize = new System.Drawing.Size(730, 470);
            this.Name = "ServerControllerView";
            this.Padding = new System.Windows.Forms.Padding(5);
            this.Text = "Spreadsheet Admin";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button offButton;
        private System.Windows.Forms.Button logoutButton;
        private System.Windows.Forms.ListView userListView;
        private System.Windows.Forms.ListView spreadsheetListView;
        private System.Windows.Forms.Button addUserButton;
        private System.Windows.Forms.Button addSpreadsheetButton;
        private System.Windows.Forms.Button confirmAddUserButton;
        private System.Windows.Forms.TextBox newUserTextBox;
        private System.Windows.Forms.TextBox newPasswordTextBox;
        private System.Windows.Forms.Label newUserLabel;
        private System.Windows.Forms.Label newPasswordLabel;
        private System.Windows.Forms.Button confirmNewSpreadsheetButton;
        private System.Windows.Forms.TextBox newSpreadhseetTextBox;
        private System.Windows.Forms.Label newSpreadsheetNameLabel;
        private System.Windows.Forms.RichTextBox logTextBox;
        private System.Windows.Forms.Label logLabel;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button deleteUserButton;
        private System.Windows.Forms.Button deleteSpreadsheetButton;
        private System.Windows.Forms.ListView activeSpreadsheetsAndUsers;
        private System.Windows.Forms.Label usersLabel;
        private System.Windows.Forms.Label spreadsheetsLabel;
        private System.Windows.Forms.Label label3;
    }
}

