using SS;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;
using CS3505;

namespace SpreadsheetGUI
{
    public partial class SpreadsheetView : Form
    {
        /// <summary>
        /// Underlying data structure that keeps track of the contents of the cells and values for updating and 
        /// displaying cell information on the application
        /// </summary>
        private Spreadsheet formSheet;
        /// <summary>
        /// private member that keeps track if the sheet has been saved since the last edit
        /// </summary>
        private bool saved = true;
        /// <summary>
        /// The name of the spreadsheet loaded or saved, deafault is an empty string.
        /// </summary>
        private string sheetName = "";
        /// <summary>
        /// Keeps track of if ctrl has been pressed or not
        /// </summary>
        private bool ctrl = true;
        /// <summary>
        /// Sound player for playing the chosen music by the user
        /// </summary>
        private SoundPlayer music;

        /// <summary>
        /// Controller for sending and receiving edits from a server
        /// </summary>
        private SpreadsheetController ssController;

        public SpreadsheetView(SpreadsheetController ssController)
        {
            InitializeComponent();
            spreadsheetPanel1.SelectionChanged += OnSelectionChanged;
            FormClosing += saveCheck;
            SetCellContentsText.KeyUp += KeyReleased;
            SetCellContentsText.PreviewKeyDown += KeyPressed;
            // SetCellContentsText.KeyDown += KeyReleased;
            music = new SoundPlayer(Directory.GetCurrentDirectory() + "\\WiiMusic.wav");

            this.ssController = ssController;

            ssController.SpreadsheetUpdated += SpreadsheetUpdate;
            formSheet = ssController.Sheet;
            //formSheet = new Spreadsheet(x => true, x => x.ToUpper(), "ps6");

            this.AcceptButton = SetCellContentsButton;
            
            // the initial selection should be the first cell
            spreadsheetPanel1.SetSelection(0, 0);
            SetCellContentsText.Focus();
        }

       


        #region(oldocde)
        /// <summary>
        /// Method for detecting what key has been released for key navigation
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void KeyReleased(Object sender, EventArgs e)
        {
            if (ModifierKeys.HasFlag(Keys.Control))
            {
                ctrl = !ctrl;

            }

        }

        /// <summary>
        /// Method for determining what key has been pressed for spreadsheet navigation
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void KeyPressed(Object sender, PreviewKeyDownEventArgs e)
        {
            if (ModifierKeys.HasFlag(Keys.Control))
            {
                ctrl = true;
            }
            if (e.KeyData == Keys.Up)
            {
                moveUp();
            }
            else if (e.KeyData == Keys.Down)
            {
                moveDown();
            }
            else if (e.KeyData == Keys.Left && ctrl)
            {
                moveLeft();
            }
            else if (e.KeyData == Keys.Right && ctrl)
            {
                moveRight();
            }
        }
        /// <summary>
        /// Moves the selection of the spreadsheet up 1 from the current selection.
        /// </summary>
        private void moveUp()
        {
            int col;
            int row;

            spreadsheetPanel1.GetSelection(out col, out row);


            spreadsheetPanel1.SetSelection(col, row - 1);

            displayCellName(spreadsheetPanel1);
            displayCellContents(spreadsheetPanel1);
            displayCellValue(spreadsheetPanel1);


        }
        /// <summary>
        /// Moves the selection of the spreadsheet up 1 from the current selection.
        /// </summary>
        private void moveLeft()
        {
            int col;
            int row;

            spreadsheetPanel1.GetSelection(out col, out row);


            spreadsheetPanel1.SetSelection(col - 1, row);

            displayCellName(spreadsheetPanel1);
            displayCellContents(spreadsheetPanel1);
            displayCellValue(spreadsheetPanel1);


        }
        /// <summary>
        /// Moves the selection of the spreadsheet up 1 from the current selection.
        /// </summary>
        private void moveRight()
        {
            int col;
            int row;

            spreadsheetPanel1.GetSelection(out col, out row);


            spreadsheetPanel1.SetSelection(col + 1, row);

            displayCellName(spreadsheetPanel1);
            displayCellContents(spreadsheetPanel1);
            displayCellValue(spreadsheetPanel1);


        }
        /// <summary>
        /// Moves the selection of the spreadsheet up 1 from the current selection.
        /// </summary>
        private void moveDown()
        {
            int col;
            int row;

            spreadsheetPanel1.GetSelection(out col, out row);


            spreadsheetPanel1.SetSelection(col, row + 1);

            displayCellName(spreadsheetPanel1);
            displayCellContents(spreadsheetPanel1);
            displayCellValue(spreadsheetPanel1);


        }



        /// <summary>
        /// A private helper method that, upon closing the application, if the data in the spreadsheet
        /// has not been saved asks if it should be saved, with a yes, no, or cancel MessageBox
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void saveCheck(Object sender, FormClosingEventArgs e)
        {
            if (!saved)
            {
                DialogResult saveResult = MessageBox.Show("Your data has not been saved. Would you like to save before continuing?", "Unsaved Data", MessageBoxButtons.YesNoCancel);
                if (saveResult == DialogResult.Yes)
                {
                    save();
                }
                else if (saveResult == DialogResult.Cancel)
                {
                    e.Cancel = true;
                }
            }
        }
        /// <summary>
        /// A private helper method that, upon loading an existing sheet if the current sheet
        /// has not been saved asks if it should be saved, with a yes, no, or cancel MessageBox
        /// if the sheet is saved afterwards or a save is not desired then true is returned.
        /// if cancel is desired false is returned
        /// </summary>
        private bool saveCheck()
        {
            if (!saved)
            {
                DialogResult saveResult = MessageBox.Show("Your data has not been saved. Would you like to save before continuing?", "Unsaved Data", MessageBoxButtons.YesNoCancel);
                if (saveResult == DialogResult.Yes)
                {
                    save();
                    return true;
                }
                else if (saveResult == DialogResult.Cancel)
                {
                    return false;
                }


            }
            return true;
        }

        /// <summary>
        /// Event handler that catches events of type SelectionChanged. This takes the cellContentsText and 
        /// inserts the correct cell contents into the text box for easier editing
        /// </summary>
        /// <param name="ss"></param>
        private void OnSelectionChanged(SpreadsheetPanel ss)
        {
            //TODO SET TEXT BOX FOR EDITING THE CELL DIRECTLY

          
            // set the cursor to the set cell contents text box when a new cell is selected
            SetCellContentsText.Focus();
            displayCellName(ss);
            displayCellContents(ss);
            displayCellValue(ss);


        }
        /// <summary>
        /// Helper method that displays the value of the selected cell in the ValueDisplayBox 
        /// </summary>
        /// <param name="ss"></param>
        private void displayCellValue(SpreadsheetPanel ss)
        {
            int col;
            int row;

            ss.GetSelection(out col, out row);
            // add one so that it appears to be highlighting the correct cell, because the panel is index 0
            row = row + 1;

            char columnLetter = getColumnLetter(col);//(char)(65 + col);

            string cellName = (columnLetter.ToString() + row.ToString());

            ValueDisplayBox.Text = ssController.Sheet.GetCellValue(cellName).ToString();
        }

        /// <summary>
        /// Helper method that displays the name of the selected cell in the CellNameText box
        /// </summary>
        /// <param name="ss"></param>
        private void displayCellName(SpreadsheetPanel ss)
        {
            int col;
            int row;

            ss.GetSelection(out col, out row);
            // add one so that it appears to be highlighting the correct cell, because the panel is index 0
            row = row + 1;

            char columnLetter = getColumnLetter(col);//(char)(65 + col);

            string cellName = (columnLetter.ToString() + row.ToString());

            CellNameText.Text = cellName;
        }

        /// <summary>
        /// private helper method that helps display the correct contents of the sellected Cell
        /// </summary>
        /// <param name="ss"></param>
        private void displayCellContents(SpreadsheetPanel ss)
        {

            // get the column row so that the name can be found and the contents can be displayed 
            int col;
            int row;

            ss.GetSelection(out col, out row);
            // add one so that it appears to be highlighting the correct cell, because the panel is index 0
            row = row + 1;

            char columnLetter = getColumnLetter(col);//(char)(65 + col);

            string cellName = (columnLetter.ToString() + row.ToString());

            cellEditBox.Location = new Point(col * 80 + 29, row * 20 + 90);

            if (formSheet.GetCellContents(cellName) is SpreadsheetUtilities.Formula)
            {
                SetCellContentsText.Text = "=" + formSheet.GetCellContents(cellName).ToString();
                this.cellEditBox.Visible = true;
                cellEditBox.Text = "=" + formSheet.GetCellContents(cellName).ToString();
                cellEditBox.Focus();
            }
            else
            {
                //********** Set the Contents of the text box to the contents of the selected cell ****
                SetCellContentsText.Text = formSheet.GetCellContents(cellName).ToString();

                this.cellEditBox.Visible = true;
                cellEditBox.Text = formSheet.GetCellContents(cellName).ToString();
                cellEditBox.Focus();
            }

        }

        /// <summary>
        /// Helper method that can be used to convert the column number to an int usable as a cell
        /// name in the formsheet
        /// </summary>
        /// <param name="col"></param>
        /// <returns></returns>
        private char getColumnLetter(int col)
        {
            return (char)(65 + col);
        }

        private void SetCellContentsButton_Click(object sender, EventArgs e)
        {


            // setSelectedCell();
            SendEdit();

        }
        #endregion
        /// <summary>
        /// Helper method that uses the Spreadsheet controller to send an edit Request to the server
        /// </summary>
        private void SendEdit()
        {
            int col;
            int row;

            spreadsheetPanel1.GetSelection(out col, out row);

            cellEditBox.Visible = false;

            // get the appropriate column letter and cell name
            char columnLetter = getColumnLetter(col);
            string cellName = columnLetter.ToString() + (row + 1).ToString();

            SetCellContentsText.Text = cellEditBox.Text;
            ssController.ClientEdit(cellName, SetCellContentsText.Text);

        }

        /// <summary>
        /// Helper method for when the spreadsheet panel opens to set all of the non-empy cells
        /// In the ssController
        /// </summary>
        public void PopulateSpreadsheet(Dictionary<string, IEnumerable<string>> cellDependies)
        {
            //FIXME
            SpreadsheetUpdate(cellDependies);
        }

        /// <summary>
        /// Helper function that subscribes to srpeadsheet controller's spreadsheetupdated event
        /// Tells the GUI to update the contents of the given cells
        /// </summary>
        /// <param name="updatedCells"></param>
        private void SpreadsheetUpdate(Dictionary<string, IEnumerable<string>> cellDependies)
        {
           
            //update the underlying spreadsheet and all of the values that rely on the updated cells
            foreach (string dependent in cellDependies.Keys)
            {
                foreach(string cell in cellDependies[dependent])
                {
                    // get the location of the dependent cell
                    int col = (int)cell[0] - 65;
                    int row = int.Parse(cell.Substring(1)) - 1;
                    //set the new value to the dependent cells                
                    spreadsheetPanel1.SetValue(col, row, formSheet.GetCellValue(cell).ToString());
                }
            }

        }

        /// <summary>
        /// The logic function that takes the currently selected cell and inputs the information given to it
        /// by the setContentsText box into the underlying spreadsheet data
        /// </summary>
        private void setSelectedCell(string cellName, string setcellcontents)
        {
            // get the information about where the selection has been made
            //int col;
            //int row;

            //spreadsheetPanel1.GetSelection(out col, out row);

            //// get the appropriate column letter and cell name
            //char columnLetter = getColumnLetter(col);
            //string cellName = columnLetter.ToString() + (row + 1).ToString();
            IEnumerable<string> dependentList;
            try
            {
               dependentList = formSheet.SetContentsOfCell(cellName, SetCellContentsText.Text);
               //dependentList = formSheet.get


                //update the underlying spreadsheet and all of the values that rely on the updated cell
                foreach (string dependent in dependentList)
                {
                    // get the location of the dependent cell
                    int col = (int)dependent[0] - 65;
                    int row = int.Parse(dependent.Substring(1)) - 1;
                    //set the new value to the dependent cells                
                    spreadsheetPanel1.SetValue(col, row, formSheet.GetCellValue(dependent).ToString());
                }
                saved = false;
            }
            catch (SpreadsheetUtilities.FormulaFormatException e)
            {

                //MessageBox errorMessage = new MessageBox("Invalid Formula Entered");
                MessageBox.Show(e.Message, "Error Message");
            }
            catch (CircularException e)
            {
               
                MessageBox.Show("Cells Cannot Be Set So That a Circular Dependency is Introduced to the SpreadSheet /n" + e.Message, "Input Error");
            }



        }

        #region(oldocde)
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            save();

        }
        /// <summary>
        /// Helper mehtod that uses a savedialogbox to get a file path and then save to that file
        /// </summary>
        private void save()
        {

            string filePath = getSaveFile();
            saveToFile(filePath);
        }



        /// <summary>
        /// private helper method that usues an SaveFileDialog to get the file path for a file to 
        /// be saved to. Default file type is set to .sprd files
        /// </summary>
        /// <returns></returns>
        private string getSaveFile()
        {
            using (SaveFileDialog saveFile = new SaveFileDialog())
            {

                try
                {
                    saveFile.InitialDirectory = "c:\\";
                    saveFile.Filter = "All files (*.*)|*.*| sprd files (*.sprd)|*.sprd";
                    saveFile.FilterIndex = 2;


                    saveFile.RestoreDirectory = true;

                    // string fileName = saveFile.FileName;
                    saveFile.OverwritePrompt = false;
                    saveFile.FileOk += openFileDialog1_FileOk;
                    //saveFile.FileOk
                    saveFile.ShowDialog();
                    string fileName = saveFile.FileName;
                    if (saveFile.FileName != sheetName)
                    {
                        saveFile.OverwritePrompt = true;
                    }
                    //When filtering by .sprd the .spred should automatically be appended to the end of the file name
                    if (saveFile.FilterIndex == 2)
                    {
                        saveFile.DefaultExt = "sprd";
                           
                           }


                  

                    return saveFile.FileName;
                }
                catch (SpreadsheetReadWriteException e)
                {
                    return "";
                }

            }
        }

        /// <summary>
        /// This event checks to see if the File is ok to save to by checkng to see if the user wants to 
        /// overwrite existing data
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void openFileDialog1_FileOk(object sender,
            CancelEventArgs e)
        {
            if (sender is SaveFileDialog)
            {
                SaveFileDialog overWrite = (SaveFileDialog)sender;
                // if the file is correct do nothing
                if (overWrite.FileName == sheetName || !File.Exists(overWrite.FileName))
                {

                }
                // if the filename is wrong display the overwrite message
                else
                {

                    DialogResult saveResult = MessageBox.Show("Do you want to overwrite the data in the given file?", "Overwrite Data", MessageBoxButtons.YesNo);
                    // if yes then nothing 
                    if (saveResult == DialogResult.Yes)
                    {

                    }
                    // if No specify a different path
                    else if (saveResult == DialogResult.No)
                    {
                        overWrite.FileName = "";
                        e.Cancel = true;
                    }


                }
            }
        }

        /// <summary>
        /// Private helper method that uses the underlying spreadsheet to save to the specified file
        /// </summary>
        /// <param name="filePath"></param>
        private void saveToFile(string filePath)
        {
            if (filePath == "") return;
            sheetName = filePath;
            try
            {


                formSheet.Save(filePath);
                saved = true;
                this.Text = sheetName;
            }
            catch (SpreadsheetReadWriteException e)
            {
                MessageBox.Show("There was a problem saving to the specified file", "Save Error");
            }

        }
        /// <summary>
        /// Event handler that starts the process for saving files
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveCheck())
            {
                string filePath = getLoadFile();
                loadSavedSheet(filePath);
            }
        }


        /// <summary>
        /// private helper method that usues an OpenFileDialog to get the file path for a file to 
        /// be loaded from. Default file type is set to .sprd files
        /// </summary>
        /// <returns></returns>
        private string getLoadFile()
        {
            using (OpenFileDialog openFile = new OpenFileDialog())
            {
                try
                {
                    openFile.InitialDirectory = "c:\\";
                    openFile.Filter = "All files (*.*)|*.*| sprd files (*.sprd)|*.sprd";
                    openFile.FilterIndex = 2;

                    openFile.ShowDialog();
                    openFile.RestoreDirectory = true;
                    string fileName = openFile.FileName;
                    // when reading from a file if the .sprd filter is applyed the name extension must end with .sprd
                    if (fileName != "" && openFile.FilterIndex == 2 && fileName.Substring(fileName.Length - 5) != ".sprd")
                    {
                        fileName = fileName + ".sprd";
                    }

                    return openFile.FileName;
                }
                catch (SpreadsheetReadWriteException e)
                {
                    return "";
                }
            }
        }
        /// <summary>
        /// private helper mehtod that takes in a filepath to be read from and then set the classes formSheet
        /// to be the sheet in the loaded file. Using the getNamesofAllNonemptyCells method the cells with new 
        /// values are updated in the view to display the correct values
        /// </summary>
        /// <param name="filePath"></param>
        private void loadSavedSheet(string filePath)
        {
            if (filePath == "") return;
            sheetName = filePath;
            formSheet = new Spreadsheet(filePath, s => true, s => s.ToUpper(), "ps6");
            saved = true;
            //clear cells from last load
            spreadsheetPanel1.Clear();
            // fill in the new cell values
            foreach (string cell in formSheet.GetNamesOfAllNonemptyCells())
            {
                // get the location of the dependent cell
                int col = (int)cell[0] - 65;
                int row = int.Parse(cell.Substring(1)) - 1;
                //set the new value to the dependent cells                
                spreadsheetPanel1.SetValue(col, row, formSheet.GetCellValue(cell).ToString());
            }
            // reset the selected cell to the first and display the value, name, and contents
            spreadsheetPanel1.SetSelection(0, 0);
            displayCellName(spreadsheetPanel1);
            displayCellContents(spreadsheetPanel1);
            displayCellValue(spreadsheetPanel1);
            this.Text = sheetName;


        }
        /// <summary>
        /// Eventfired when the close menu button is clicked, closes the current window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        /// <summary>
        /// Event fired when the new tool strip menu is clicked calls the function to create a new thread.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            newWindow();
        }

        /// <summary>
        /// Helper method that creates a new window on a seperate thread.
        /// </summary>
        private void newWindow()
        {
            SpreadsheetAplicationContext.getAppContext().RunForm(new SpreadsheetView(null));
        }

        private void eventLog1_EntryWritten(object sender, System.Diagnostics.EntryWrittenEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // the initial selectioon should be the first cell
            spreadsheetPanel1.SetSelection(0, 0);
            SetCellContentsText.Focus();
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
        /// <summary>
        /// Displays a message box that contians help information for: Selecting Cells
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void selectingCellsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Cells can be selected by moving the mouse cursor over the desired cell and left clicking"

       + ". Upon selection in the SetContents text box the contents of the cell will be displayed"

       + " and the cursor will focus this box for editing.Additionally the other two text boxes will update with"

        + " the cell name on the left and the cell value on the right.", "Help - Selecting Cells");
        }
        /// <summary>
        /// Displays a message box that contians help information for: Editing Cells
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void editingCellsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Cells can be edited by selecting the desired cell and then in the Set Contents textbox "

       + " changing the contents of the cells. Cells can contain numbers, letters, or a formula. Numbers and words "

        + "can be added using plain text. Formulas require that an '=' precedes the desired formula. Formulas are "

       + " mathematical equations that can use other cells as variable names. Strings or words cannot be added to numbers "

       + " and no number can be divided by 0. After placing the desired cell contents into the text box press the "

       + " 'Set Contents' button or press enter to solidify the edit of the cell.", "Help - Editing Cells");
        }

        /// <summary>
        /// Displays a message box that contians help information for: TextBoxes and Buttons
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBoxesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("There are three text boxes and one button. The top left text box is editable and allows "

       + "for the user to enter the desired contents of the selected cell (see Editng Cells and Selecting Cells). The "

       + "button to its right allows for the text entered into the text box to be added to the selected cell. The bottom "

       + "two text boxes are not editable and only display information.The one on the left displays the sected cell's name "

       + "and the one on the right displays the selected cell's value.", "Textboxes and Buttons");
        }

        /// <summary>
        /// Displays a message box that contians help information for: Invalid Formulas
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void invalidFormulasToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Formulas must consist of a mathematically correct statement including numbers and "
        + "variables only. \n\nVariables must be of the form: a letter followed by a number. Variables are not case "
        + "sensitive, 'a1' will be treated the same as 'A1'. The values for variables will be drawn from the "
        + " spreadsheet itself and the corresponding cell values displayed. \n\nIf a variable is introduced that does not "
        + " follow the given pattern the user will be told that the formula is incorrect and the cell contents will not "
        + " be set, the same applies if mathematically the statement is incorrect. If a cell that does not exist or contains "
        + " a word inside of it is attempted to be added to a number inside of the cell the value will display an error message. ", "Invalid Formulas");
        }

        /// <summary>
        /// Displays a message box that contians help information for: Circular Dependencies
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void circularDependenciesToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Inside a working spreadsheet it is impossible that a cell contains a reference "

         + "directly or indirectly to itself. This breaks the code of the spreadsheet and creates what is called a circular "

         + "dependency. If such a dependency is created the user is notified and the contents of the cell will not be "

         + "set. ", "Circular Dependencies");
        }

        private void optionsToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void fontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            changeFont();
        }

        /// <summary>
        /// Helper mehhod for changing the font of the spreadsheet, uses a fontDialog
        /// </summary>
        private void changeFont()
        {
            FontDialog font = new FontDialog();

            font.ShowDialog();

            this.Font = font.Font;
            spreadsheetPanel1.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right | AnchorStyles.Top | AnchorStyles.Left);

        }

        private void colorsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            changeColor();
        }

        /// <summary>
        /// Helper method for change the color of the spreadsheet, uses a colorDialog
        /// </summary>
        private void changeColor()
        {
            ColorDialog color = new ColorDialog();

            color.ShowDialog();

            this.BackColor = color.Color;



        }
        /// <summary>
        /// Displays a dialog box that explains how to change colors
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void colorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("In the options menu when colors is clicked a color dialog pop up will appear allowing"
                + " the user to select a desired color. The color will be show around the edges of the spreadsheet "
                + "and will not affect the spreadsheet cells, different form windows will have different colors.", "Help- Colors");
        }
        /// <summary>
        /// Displays a dialog box that explains how to change fonts
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void fontToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("In the options menu when Font is clicked a Font Dialog pop up will appear that allows"
                + " the user to select their desired font. The new font will be applied to the entire spreadsheet.", "Help - Font");
        }
        /// <summary>
        /// Displays a dialog box that explains how to navigate using arrow keys
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void arrowKeyNavigationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show(" Cell selection can be changed by pressing the up and down arrow keys which will move the "

         + "selection one up and one down accordingly. Additionally the left and right arrow keys are defaulted set to "

         + "navigate left and right. However for easier text editing navigation left and right arrow keys can be toggled "

         + "off for cell navigation by pressing ctrl and left or right. To toggle them back on simply press ctrl", "Help - Arrow Key Navigation");
        }

        private void playToolStripMenuItem_Click(object sender, EventArgs e)
        {
            playMusic();
        }
        /// <summary>
        /// Method for playing music from the soundplayer embedded in the spreadsheet
        /// </summary>
        private void playMusic()
        {
            if (music.SoundLocation == "")
            {
                loadMusic();
            }
            try
            {
                music.Play();
            }
            catch( Exception e)
            {
                MessageBox.Show("Invalid Music file path, please be sure a wav file has been selected", "Music error");
            }
        }
        /// <summary>
        /// Uses a file Dialog to load a wav file to the music player
        /// </summary>
        private void loadMusic()
        {
            using (OpenFileDialog musicFile = new OpenFileDialog())
            {
                try
                {
                    musicFile.InitialDirectory = "c:\\";
                    musicFile.Filter = "wav files (*.wav)|*.wav";
                    

                    musicFile.ShowDialog();
                    musicFile.RestoreDirectory = true;
                    string fileName = musicFile.FileName;

                    music.SoundLocation = fileName;
                }catch(System.ArgumentException e)
                {

                }
              
                catch (Exception e)
                {
                    MessageBox.Show("An error occured while selecting the file");
                }
            }
        }

        private void chooseSongToolStripMenuItem_Click(object sender, EventArgs e)
        {
            loadMusic();
        }


        private void stopToolStripMenuItem_Click(object sender, EventArgs e)
        {
            music.Stop();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void musicToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Wav files can be played through the spreadsheet through a built in soundplayer."
                + " A default song has been set but under the music menu there are options for playing the"
                + " chosen music, choosing a new wav file, and stopping the music.", "Help - Music");
        }
        #endregion

        private void UndoButton_Click(object sender, EventArgs e)
        {
            ssController.ClientUndo();
        }

        private void Revert_Click(object sender, EventArgs e)
        {

            // get the information about where the selection has been made
            int col;
            int row;

            spreadsheetPanel1.GetSelection(out col, out row);

            // get the appropriate column letter and cell name
            char columnLetter = getColumnLetter(col);
            string cellName = columnLetter.ToString() + (row + 1).ToString();

            ssController.ClientRevert(cellName);
        }
    }




}

