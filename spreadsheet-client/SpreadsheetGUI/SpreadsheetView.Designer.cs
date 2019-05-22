using System;

namespace SpreadsheetGUI
{
    partial class SpreadsheetView
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
            this.spreadsheetPanel1 = new SS.SpreadsheetPanel();
            this.SetCellContentsText = new System.Windows.Forms.TextBox();
            this.SetCellContentsButton = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.Menu = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fontToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.colorsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.musicToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.basicCommandsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectingCellsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editingCellsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.textBoxesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.errorsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.invalidFormulasToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.circularDependenciesToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.additionalFeaturesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.colorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fontToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.arrowKeyNavigationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.musicToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.musicToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.playToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.chooseSongToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eventLog1 = new System.Diagnostics.EventLog();
            this.CellNameText = new System.Windows.Forms.TextBox();
            this.ValueDisplayBox = new System.Windows.Forms.TextBox();
            this.fileSystemWatcher1 = new System.IO.FileSystemWatcher();
            this.UndoButton = new System.Windows.Forms.Button();
            this.Revert = new System.Windows.Forms.Button();
            this.cellEditBox = new System.Windows.Forms.TextBox();
            this.DisconnectedLabel = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eventLog1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileSystemWatcher1)).BeginInit();
            this.SuspendLayout();
            // 
            // spreadsheetPanel1
            // 
            this.spreadsheetPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.spreadsheetPanel1.Location = new System.Drawing.Point(0, 78);
            this.spreadsheetPanel1.Name = "spreadsheetPanel1";
            this.spreadsheetPanel1.Size = new System.Drawing.Size(806, 387);
            this.spreadsheetPanel1.TabIndex = 0;
            // 
            // SetCellContentsText
            // 
            this.SetCellContentsText.Location = new System.Drawing.Point(12, 28);
            this.SetCellContentsText.Name = "SetCellContentsText";
            this.SetCellContentsText.Size = new System.Drawing.Size(155, 20);
            this.SetCellContentsText.TabIndex = 1;
            // 
            // SetCellContentsButton
            // 
            this.SetCellContentsButton.Location = new System.Drawing.Point(188, 28);
            this.SetCellContentsButton.Name = "SetCellContentsButton";
            this.SetCellContentsButton.Size = new System.Drawing.Size(121, 20);
            this.SetCellContentsButton.TabIndex = 2;
            this.SetCellContentsButton.Text = "Set Contents";
            this.SetCellContentsButton.UseVisualStyleBackColor = true;
            this.SetCellContentsButton.Click += new System.EventHandler(this.SetCellContentsButton_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Menu,
            this.helpToolStripMenuItem,
            this.musicToolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // Menu
            // 
            this.Menu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.closeToolStripMenuItem,
            this.optionsToolStripMenuItem});
            this.Menu.Name = "Menu";
            this.Menu.Size = new System.Drawing.Size(50, 20);
            this.Menu.Text = "Menu";
            this.Menu.Click += new System.EventHandler(this.Menu_Click);
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.newToolStripMenuItem.Text = "New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // closeToolStripMenuItem
            // 
            this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
            this.closeToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.closeToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.closeToolStripMenuItem.Text = "Close";
            this.closeToolStripMenuItem.Click += new System.EventHandler(this.closeToolStripMenuItem_Click);
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fontToolStripMenuItem,
            this.colorsToolStripMenuItem,
            this.musicToolStripMenuItem});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(146, 22);
            this.optionsToolStripMenuItem.Text = "Options";
            this.optionsToolStripMenuItem.Click += new System.EventHandler(this.optionsToolStripMenuItem_Click);
            // 
            // fontToolStripMenuItem
            // 
            this.fontToolStripMenuItem.Name = "fontToolStripMenuItem";
            this.fontToolStripMenuItem.Size = new System.Drawing.Size(108, 22);
            this.fontToolStripMenuItem.Text = "Font";
            this.fontToolStripMenuItem.Click += new System.EventHandler(this.fontToolStripMenuItem_Click);
            // 
            // colorsToolStripMenuItem
            // 
            this.colorsToolStripMenuItem.Name = "colorsToolStripMenuItem";
            this.colorsToolStripMenuItem.Size = new System.Drawing.Size(108, 22);
            this.colorsToolStripMenuItem.Text = "Colors";
            this.colorsToolStripMenuItem.Click += new System.EventHandler(this.colorsToolStripMenuItem_Click);
            // 
            // musicToolStripMenuItem
            // 
            this.musicToolStripMenuItem.Name = "musicToolStripMenuItem";
            this.musicToolStripMenuItem.Size = new System.Drawing.Size(108, 22);
            this.musicToolStripMenuItem.Text = "Music";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.basicCommandsToolStripMenuItem,
            this.errorsToolStripMenuItem,
            this.additionalFeaturesToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            this.helpToolStripMenuItem.Click += new System.EventHandler(this.helpToolStripMenuItem_Click);
            // 
            // basicCommandsToolStripMenuItem
            // 
            this.basicCommandsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectingCellsToolStripMenuItem,
            this.editingCellsToolStripMenuItem,
            this.textBoxesToolStripMenuItem});
            this.basicCommandsToolStripMenuItem.Name = "basicCommandsToolStripMenuItem";
            this.basicCommandsToolStripMenuItem.Size = new System.Drawing.Size(176, 22);
            this.basicCommandsToolStripMenuItem.Text = "Basic Commands";
            // 
            // selectingCellsToolStripMenuItem
            // 
            this.selectingCellsToolStripMenuItem.Name = "selectingCellsToolStripMenuItem";
            this.selectingCellsToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
            this.selectingCellsToolStripMenuItem.Text = "Selecting Cells";
            this.selectingCellsToolStripMenuItem.Click += new System.EventHandler(this.selectingCellsToolStripMenuItem_Click);
            // 
            // editingCellsToolStripMenuItem
            // 
            this.editingCellsToolStripMenuItem.Name = "editingCellsToolStripMenuItem";
            this.editingCellsToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
            this.editingCellsToolStripMenuItem.Text = "Editing Cells";
            this.editingCellsToolStripMenuItem.Click += new System.EventHandler(this.editingCellsToolStripMenuItem_Click);
            // 
            // textBoxesToolStripMenuItem
            // 
            this.textBoxesToolStripMenuItem.Name = "textBoxesToolStripMenuItem";
            this.textBoxesToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
            this.textBoxesToolStripMenuItem.Text = "Text Boxes";
            this.textBoxesToolStripMenuItem.Click += new System.EventHandler(this.textBoxesToolStripMenuItem_Click);
            // 
            // errorsToolStripMenuItem
            // 
            this.errorsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.invalidFormulasToolStripMenuItem1,
            this.circularDependenciesToolStripMenuItem1});
            this.errorsToolStripMenuItem.Name = "errorsToolStripMenuItem";
            this.errorsToolStripMenuItem.Size = new System.Drawing.Size(176, 22);
            this.errorsToolStripMenuItem.Text = "Errors";
            // 
            // invalidFormulasToolStripMenuItem1
            // 
            this.invalidFormulasToolStripMenuItem1.Name = "invalidFormulasToolStripMenuItem1";
            this.invalidFormulasToolStripMenuItem1.Size = new System.Drawing.Size(192, 22);
            this.invalidFormulasToolStripMenuItem1.Text = "Invalid Formulas";
            this.invalidFormulasToolStripMenuItem1.Click += new System.EventHandler(this.invalidFormulasToolStripMenuItem1_Click);
            // 
            // circularDependenciesToolStripMenuItem1
            // 
            this.circularDependenciesToolStripMenuItem1.Name = "circularDependenciesToolStripMenuItem1";
            this.circularDependenciesToolStripMenuItem1.Size = new System.Drawing.Size(192, 22);
            this.circularDependenciesToolStripMenuItem1.Text = "Circular Dependencies";
            this.circularDependenciesToolStripMenuItem1.Click += new System.EventHandler(this.circularDependenciesToolStripMenuItem1_Click);
            // 
            // additionalFeaturesToolStripMenuItem
            // 
            this.additionalFeaturesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.colorToolStripMenuItem,
            this.fontToolStripMenuItem1,
            this.arrowKeyNavigationToolStripMenuItem,
            this.musicToolStripMenuItem2});
            this.additionalFeaturesToolStripMenuItem.Name = "additionalFeaturesToolStripMenuItem";
            this.additionalFeaturesToolStripMenuItem.Size = new System.Drawing.Size(176, 22);
            this.additionalFeaturesToolStripMenuItem.Text = "Additional Features";
            // 
            // colorToolStripMenuItem
            // 
            this.colorToolStripMenuItem.Name = "colorToolStripMenuItem";
            this.colorToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.colorToolStripMenuItem.Text = "Color";
            this.colorToolStripMenuItem.Click += new System.EventHandler(this.colorToolStripMenuItem_Click);
            // 
            // fontToolStripMenuItem1
            // 
            this.fontToolStripMenuItem1.Name = "fontToolStripMenuItem1";
            this.fontToolStripMenuItem1.Size = new System.Drawing.Size(189, 22);
            this.fontToolStripMenuItem1.Text = "Font";
            this.fontToolStripMenuItem1.Click += new System.EventHandler(this.fontToolStripMenuItem1_Click);
            // 
            // arrowKeyNavigationToolStripMenuItem
            // 
            this.arrowKeyNavigationToolStripMenuItem.Name = "arrowKeyNavigationToolStripMenuItem";
            this.arrowKeyNavigationToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.arrowKeyNavigationToolStripMenuItem.Text = "Arrow Key Navigation";
            this.arrowKeyNavigationToolStripMenuItem.Click += new System.EventHandler(this.arrowKeyNavigationToolStripMenuItem_Click);
            // 
            // musicToolStripMenuItem2
            // 
            this.musicToolStripMenuItem2.Name = "musicToolStripMenuItem2";
            this.musicToolStripMenuItem2.Size = new System.Drawing.Size(189, 22);
            this.musicToolStripMenuItem2.Text = "Music";
            this.musicToolStripMenuItem2.Click += new System.EventHandler(this.musicToolStripMenuItem2_Click);
            // 
            // musicToolStripMenuItem1
            // 
            this.musicToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.playToolStripMenuItem,
            this.chooseSongToolStripMenuItem,
            this.stopToolStripMenuItem});
            this.musicToolStripMenuItem1.Name = "musicToolStripMenuItem1";
            this.musicToolStripMenuItem1.Size = new System.Drawing.Size(51, 20);
            this.musicToolStripMenuItem1.Text = "Music";
            // 
            // playToolStripMenuItem
            // 
            this.playToolStripMenuItem.Name = "playToolStripMenuItem";
            this.playToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
            this.playToolStripMenuItem.Size = new System.Drawing.Size(185, 22);
            this.playToolStripMenuItem.Text = "Play";
            this.playToolStripMenuItem.Click += new System.EventHandler(this.playToolStripMenuItem_Click);
            // 
            // chooseSongToolStripMenuItem
            // 
            this.chooseSongToolStripMenuItem.Name = "chooseSongToolStripMenuItem";
            this.chooseSongToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.T)));
            this.chooseSongToolStripMenuItem.Size = new System.Drawing.Size(185, 22);
            this.chooseSongToolStripMenuItem.Text = "Choose Song";
            this.chooseSongToolStripMenuItem.Click += new System.EventHandler(this.chooseSongToolStripMenuItem_Click);
            // 
            // stopToolStripMenuItem
            // 
            this.stopToolStripMenuItem.Name = "stopToolStripMenuItem";
            this.stopToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.stopToolStripMenuItem.Size = new System.Drawing.Size(185, 22);
            this.stopToolStripMenuItem.Text = "Stop";
            this.stopToolStripMenuItem.Click += new System.EventHandler(this.stopToolStripMenuItem_Click);
            // 
            // eventLog1
            // 
            this.eventLog1.SynchronizingObject = this;
            this.eventLog1.EntryWritten += new System.Diagnostics.EntryWrittenEventHandler(this.eventLog1_EntryWritten);
            // 
            // CellNameText
            // 
            this.CellNameText.Location = new System.Drawing.Point(12, 52);
            this.CellNameText.Name = "CellNameText";
            this.CellNameText.ReadOnly = true;
            this.CellNameText.Size = new System.Drawing.Size(40, 20);
            this.CellNameText.TabIndex = 4;
            this.CellNameText.Text = "A1";
            // 
            // ValueDisplayBox
            // 
            this.ValueDisplayBox.Location = new System.Drawing.Point(67, 52);
            this.ValueDisplayBox.Name = "ValueDisplayBox";
            this.ValueDisplayBox.ReadOnly = true;
            this.ValueDisplayBox.Size = new System.Drawing.Size(242, 20);
            this.ValueDisplayBox.TabIndex = 5;
            // 
            // fileSystemWatcher1
            // 
            this.fileSystemWatcher1.EnableRaisingEvents = true;
            this.fileSystemWatcher1.SynchronizingObject = this;
            // 
            // UndoButton
            // 
            this.UndoButton.Location = new System.Drawing.Point(315, 28);
            this.UndoButton.Name = "UndoButton";
            this.UndoButton.Size = new System.Drawing.Size(82, 20);
            this.UndoButton.TabIndex = 6;
            this.UndoButton.Text = "Undo";
            this.UndoButton.UseVisualStyleBackColor = true;
            this.UndoButton.Click += new System.EventHandler(this.UndoButton_Click);
            // 
            // Revert
            // 
            this.Revert.Location = new System.Drawing.Point(404, 28);
            this.Revert.Name = "Revert";
            this.Revert.Size = new System.Drawing.Size(75, 20);
            this.Revert.TabIndex = 7;
            this.Revert.Text = "Revert";
            this.Revert.UseVisualStyleBackColor = true;
            this.Revert.Click += new System.EventHandler(this.Revert_Click);
            // 
            // cellEditBox
            // 
            this.cellEditBox.Location = new System.Drawing.Point(485, 29);
            this.cellEditBox.Name = "cellEditBox";
            this.cellEditBox.Size = new System.Drawing.Size(80, 20);
            this.cellEditBox.TabIndex = 8;
            this.cellEditBox.Visible = false;
            // 
            // DisconnectedLabel
            // 
            this.DisconnectedLabel.AutoSize = true;
            this.DisconnectedLabel.Location = new System.Drawing.Point(167, 9);
            this.DisconnectedLabel.Name = "DisconnectedLabel";
            this.DisconnectedLabel.Size = new System.Drawing.Size(0, 13);
            this.DisconnectedLabel.TabIndex = 9;
            this.DisconnectedLabel.Click += new System.EventHandler(this.label1_Click);
            // 
            // SpreadsheetView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.DisconnectedLabel);
            this.Controls.Add(this.cellEditBox);
            this.Controls.Add(this.Revert);
            this.Controls.Add(this.UndoButton);
            this.Controls.Add(this.ValueDisplayBox);
            this.Controls.Add(this.CellNameText);
            this.Controls.Add(this.SetCellContentsButton);
            this.Controls.Add(this.SetCellContentsText);
            this.Controls.Add(this.spreadsheetPanel1);
            this.Controls.Add(this.menuStrip1);
            this.HelpButton = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "SpreadsheetView";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eventLog1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fileSystemWatcher1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

       


        #endregion

        private SS.SpreadsheetPanel spreadsheetPanel1;
        private System.Windows.Forms.TextBox SetCellContentsText;
        private System.Windows.Forms.Button SetCellContentsButton;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem Menu;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Diagnostics.EventLog eventLog1;
        private System.Windows.Forms.TextBox CellNameText;
        private System.Windows.Forms.TextBox ValueDisplayBox;
        private System.IO.FileSystemWatcher fileSystemWatcher1;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem basicCommandsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem selectingCellsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editingCellsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem textBoxesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem errorsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem invalidFormulasToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem circularDependenciesToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem additionalFeaturesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fontToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem colorsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem musicToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem colorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fontToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem arrowKeyNavigationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem musicToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem playToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem chooseSongToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem musicToolStripMenuItem2;
        private System.Windows.Forms.Button UndoButton;
        private System.Windows.Forms.Button Revert;
        private System.Windows.Forms.TextBox cellEditBox;
        private System.Windows.Forms.Label DisconnectedLabel;
    }
}

