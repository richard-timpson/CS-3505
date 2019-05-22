namespace DialogBox
{
    partial class DialogTextBox
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
            this.AnswerTextBox = new System.Windows.Forms.TextBox();
            this.OKButton = new System.Windows.Forms.Button();
            this.CancelButton = new System.Windows.Forms.Button();
            this.GenericLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // AnswerTextBox
            // 
            this.AnswerTextBox.Location = new System.Drawing.Point(12, 101);
            this.AnswerTextBox.Name = "AnswerTextBox";
            this.AnswerTextBox.Size = new System.Drawing.Size(253, 22);
            this.AnswerTextBox.TabIndex = 0;
            // 
            // OKButton
            // 
            this.OKButton.Location = new System.Drawing.Point(12, 138);
            this.OKButton.Name = "OKButton";
            this.OKButton.Size = new System.Drawing.Size(97, 28);
            this.OKButton.TabIndex = 1;
            this.OKButton.Text = "OK";
            this.OKButton.UseVisualStyleBackColor = true;
            this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
            // 
            // CancelButton
            // 
            this.CancelButton.Location = new System.Drawing.Point(168, 138);
            this.CancelButton.Name = "CancelButton";
            this.CancelButton.Size = new System.Drawing.Size(97, 28);
            this.CancelButton.TabIndex = 2;
            this.CancelButton.Text = "Cancel";
            this.CancelButton.UseVisualStyleBackColor = true;
            // 
            // GenericLabel
            // 
            this.GenericLabel.AutoSize = true;
            this.GenericLabel.Location = new System.Drawing.Point(12, 38);
            this.GenericLabel.Name = "GenericLabel";
            this.GenericLabel.Size = new System.Drawing.Size(132, 17);
            this.GenericLabel.TabIndex = 3;
            this.GenericLabel.Text = "Generic Label Here";
            // 
            // DialogTextBox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(291, 187);
            this.Controls.Add(this.GenericLabel);
            this.Controls.Add(this.CancelButton);
            this.Controls.Add(this.OKButton);
            this.Controls.Add(this.AnswerTextBox);
            this.Name = "DialogTextBox";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox AnswerTextBox;
        private System.Windows.Forms.Button OKButton;
        private System.Windows.Forms.Button CancelButton;
        private System.Windows.Forms.Label GenericLabel;
    }
}

