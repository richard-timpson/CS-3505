namespace NewSpreadsheetDialog
{
    partial class NewSpreadsheetDialogBox
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
            this.PromptLabel = new System.Windows.Forms.Label();
            this.NewSpreadsheetNameTextBox = new System.Windows.Forms.TextBox();
            this.OKButton = new System.Windows.Forms.Button();
            this.CancelButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // PromptLabel
            // 
            this.PromptLabel.AutoSize = true;
            this.PromptLabel.Location = new System.Drawing.Point(12, 40);
            this.PromptLabel.Name = "PromptLabel";
            this.PromptLabel.Size = new System.Drawing.Size(263, 17);
            this.PromptLabel.TabIndex = 0;
            this.PromptLabel.Text = "Enter the name of the new Spreadsheet:";
            // 
            // NewSpreadsheetNameTextBox
            // 
            this.NewSpreadsheetNameTextBox.Location = new System.Drawing.Point(15, 70);
            this.NewSpreadsheetNameTextBox.Name = "NewSpreadsheetNameTextBox";
            this.NewSpreadsheetNameTextBox.Size = new System.Drawing.Size(307, 22);
            this.NewSpreadsheetNameTextBox.TabIndex = 1;
            // 
            // OKButton
            // 
            this.OKButton.Location = new System.Drawing.Point(15, 110);
            this.OKButton.Name = "OKButton";
            this.OKButton.Size = new System.Drawing.Size(102, 31);
            this.OKButton.TabIndex = 2;
            this.OKButton.Text = "OK";
            this.OKButton.UseVisualStyleBackColor = true;
            this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
            // 
            // CancelButton
            // 
            this.CancelButton.Location = new System.Drawing.Point(220, 110);
            this.CancelButton.Name = "CancelButton";
            this.CancelButton.Size = new System.Drawing.Size(102, 31);
            this.CancelButton.TabIndex = 3;
            this.CancelButton.Text = "Cancel";
            this.CancelButton.UseVisualStyleBackColor = true;
            this.CancelButton.Click += new System.EventHandler(this.CancelButton_Click);
            // 
            // NewSpreadsheetDialogBox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(381, 145);
            this.Controls.Add(this.CancelButton);
            this.Controls.Add(this.OKButton);
            this.Controls.Add(this.NewSpreadsheetNameTextBox);
            this.Controls.Add(this.PromptLabel);
            this.Name = "NewSpreadsheetDialogBox";
            this.Text = "New Spreadsheet";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.NewSpreadsheetDialogBox_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label PromptLabel;
        private System.Windows.Forms.TextBox NewSpreadsheetNameTextBox;
        private System.Windows.Forms.Button OKButton;
        private System.Windows.Forms.Button CancelButton;
    }
}

