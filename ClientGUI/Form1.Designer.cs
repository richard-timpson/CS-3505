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
            this.LogInButton = new System.Windows.Forms.Button();
            this.NewUserButton = new System.Windows.Forms.Button();
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
            this.EnterUsernameAndPasswordLabel.Location = new System.Drawing.Point(30, 164);
            this.EnterUsernameAndPasswordLabel.Name = "EnterUsernameAndPasswordLabel";
            this.EnterUsernameAndPasswordLabel.Size = new System.Drawing.Size(208, 17);
            this.EnterUsernameAndPasswordLabel.TabIndex = 2;
            this.EnterUsernameAndPasswordLabel.Text = "Enter Username and Password:";
            // 
            // UsernameLabel
            // 
            this.UsernameLabel.AutoSize = true;
            this.UsernameLabel.Location = new System.Drawing.Point(32, 184);
            this.UsernameLabel.Name = "UsernameLabel";
            this.UsernameLabel.Size = new System.Drawing.Size(77, 17);
            this.UsernameLabel.TabIndex = 3;
            this.UsernameLabel.Text = "Username:";
            // 
            // UsernameTextBox
            // 
            this.UsernameTextBox.Location = new System.Drawing.Point(33, 209);
            this.UsernameTextBox.Name = "UsernameTextBox";
            this.UsernameTextBox.Size = new System.Drawing.Size(206, 22);
            this.UsernameTextBox.TabIndex = 4;
            // 
            // PasswordTextBox
            // 
            this.PasswordTextBox.Location = new System.Drawing.Point(33, 280);
            this.PasswordTextBox.Name = "PasswordTextBox";
            this.PasswordTextBox.PasswordChar = '·';
            this.PasswordTextBox.Size = new System.Drawing.Size(206, 22);
            this.PasswordTextBox.TabIndex = 6;
            // 
            // PasswordLabel
            // 
            this.PasswordLabel.AutoSize = true;
            this.PasswordLabel.Location = new System.Drawing.Point(32, 255);
            this.PasswordLabel.Name = "PasswordLabel";
            this.PasswordLabel.Size = new System.Drawing.Size(73, 17);
            this.PasswordLabel.TabIndex = 5;
            this.PasswordLabel.Text = "Password:";
            // 
            // LogInButton
            // 
            this.LogInButton.Location = new System.Drawing.Point(33, 317);
            this.LogInButton.Name = "LogInButton";
            this.LogInButton.Size = new System.Drawing.Size(80, 29);
            this.LogInButton.TabIndex = 7;
            this.LogInButton.Text = "Log In";
            this.LogInButton.UseVisualStyleBackColor = true;
            this.LogInButton.Click += new System.EventHandler(this.LogInButton_Click);
            // 
            // NewUserButton
            // 
            this.NewUserButton.Location = new System.Drawing.Point(147, 317);
            this.NewUserButton.Name = "NewUserButton";
            this.NewUserButton.Size = new System.Drawing.Size(92, 29);
            this.NewUserButton.TabIndex = 8;
            this.NewUserButton.Text = "New User";
            this.NewUserButton.UseVisualStyleBackColor = true;
            this.NewUserButton.Click += new System.EventHandler(this.NewUserButton_Click);
            // 
            // ClientLogIn
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(290, 413);
            this.Controls.Add(this.NewUserButton);
            this.Controls.Add(this.LogInButton);
            this.Controls.Add(this.PasswordTextBox);
            this.Controls.Add(this.PasswordLabel);
            this.Controls.Add(this.UsernameTextBox);
            this.Controls.Add(this.UsernameLabel);
            this.Controls.Add(this.EnterUsernameAndPasswordLabel);
            this.Controls.Add(this.OnlineSpreadsheetSuiteLabel);
            this.Controls.Add(this.TheGenericsLabel);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "ClientLogIn";
            this.Text = "Log In";
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
        private System.Windows.Forms.Button LogInButton;
        private System.Windows.Forms.Button NewUserButton;
    }
}

