using Newtonsoft.Json;
using SpreadsheetUtilities;
using SS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CS3505
{
    /// <summary>
    /// Controller class for Spreadsheet communication with a server. 
    /// Sends, receives, and processes information between the spreadsheet
    /// client and server
    /// </summary>
    public class SpreadsheetController
    {
        private Socket theServer;
        private SocketState theServerState;

        //public delegate void SpreadsheetUpdatedEventHandler(List<string> updatedCells);
        public delegate void SpreadsheetUpdatedEventHandler(Dictionary<string, IEnumerable<string>> updatedDependencies);
        public event SpreadsheetUpdatedEventHandler SpreadsheetUpdated;

        public delegate void SpreadsheetErrorEventHandler(int code, string source);
        public event SpreadsheetErrorEventHandler SpreadsheetError;
        public delegate void SpreadsheetsReceivedHandler();
        public event SpreadsheetsReceivedHandler SpreadsheetsReceived;

        /// <summary>
        /// Usernames cannot have whitespace, this lets the client know
        /// that the username contains a whitespace
        /// </summary>
        public delegate void InvalidUsernameHandler();
        public event InvalidUsernameHandler InvalidUsername;

        /// <summary>
        /// LogIn Username
        /// </summary>
        private string Username;

        /// <summary>
        /// LogIn Password
        /// </summary>
        private string Password;

        /// <summary>
        /// JSON terminator string
        /// </summary>
        private const string ENDOFMESSAGE = "\n\n";

        /// <summary>
        /// The representation of a spreadsheet that will be updated
        /// as changes are sent to the server and verified
        /// </summary>
        private Spreadsheet sheet;

        public Spreadsheet Sheet
        {
            get
            {
                return sheet;
            }

        }


        /// <summary>
        /// The list of sheets available to the user
        /// </summary>
        private string[] SheetOptions;

        /// <summary>
        /// Public property for accessing the list of sheets available
        /// </summary>
        public string[] Sheets
        {
            get
            {
                return SheetOptions;
            }
        }

        public SpreadsheetController(Spreadsheet spreadsheet)
        {
            sheet = spreadsheet;
        }
        /// <summary>
        /// Connects to the given server initiating the client server handshake
        /// </summary>
        /// <param name="ipAddress"></param>
        public void Connect(string ipAddress)
        {
            theServer = Networking.ConnectToServer(ipAddress, ReceiveSpreadsheetsList);
        }


        /// <summary>
        /// Receive a list of available spreadsheets
        /// </summary>
        /// <param name="ss"></param>
        private void ReceiveSpreadsheetsList(SocketState ss)
        {
            // begin parsing the data
            string totalData = ss.sb.ToString();
            string[] parts = Regex.Split(totalData, @"(?<=[\n][\n])");

            foreach (string p in parts)
            {
                // ignore empty strings
                if (p.Length == 0)
                {
                    continue;
                }
                // if the last two chars are not new lines then there are
                // no more full messages be evaluated
                if (p.Length < 3)
                {
                    continue;
                }
                if (p[p.Length - 1] != '\n' || p[p.Length - 2] != '\n')
                {
                    break;
                }


                // Create a dynamic type for processing the kind of message sent
                var receive = new
                {
                    type = ""
                };

                //if (ss.sb.ToString().Length != 0)
                //{ 
                receive = JsonConvert.DeserializeAnonymousType(p, receive);


                // ignore if it is the wrong kind of message
                if (receive.type != "list")
                {
                    ss.sb.Remove(0, p.Length);
                    Networking.GetData(ss);
                    return;
                }

                //Otherwise Process the message and output the lists
                var list = new
                {
                    type = "",
                    spreadsheets = new string[0]
                };

                list = JsonConvert.DeserializeAnonymousType(ss.sb.ToString(), list);

                this.SheetOptions = list.spreadsheets;

                // Notify the client that new spreadsheets are available
                SpreadsheetsReceived();
                theServerState = ss;
                //Networking.GetData(ss);
                ss.sb.Remove(0, p.Length);
            }
            Networking.GetData(ss);
        }

        /// <summary>
        /// Public method to be called by Client to communicate to the server
        /// The desired spreadsheet to be opened
        /// </summary>
        /// <param name="sheet"></param>
        public void ChooseSpreadsheet(string sheetName, string username, string password)
        {
            Username = username;

            //Usernames cannot have whitespaces. If the given username has a whitespace,
            //Alert the client and do not proceed with the request.
            if (Username.Contains(" "))
            {
                InvalidUsername();
                return;
            }

            Password = password;
            // create the JSon object to be sent
            var open = new
            {
                type = "open",
                name = sheetName,
                username = Username,
                password = Password
            };

            // send the request to the server
            string message = JsonConvert.SerializeObject(open) + ENDOFMESSAGE;
            Networking.Send(theServer, message);

            theServerState.CallMe = ReceiveEdit;
            Networking.GetData(theServerState);
        }


        /// <summary>
        /// Method that the CLient will call when a spreadsheet cell is updated
        /// </summary>
        /// <param name="cellName"></param>
        /// <param name="cellContents"></param>
        public void ClientEdit(string cellName, string cellContents)
        {
            string[] depend = new string[0];
            // if a formula is entered
            if (cellContents.Length != 0 && cellContents[0] == '=')
            {
                // create a formula 
                Formula formula = new Formula(cellContents.Substring(1));
                depend = formula.GetVariables().ToArray();
            }

            double contents;
            if (double.TryParse(cellContents, out contents))
            {
                var edit = new
                {
                    type = "edit",
                    cell = cellName,
                    value = contents, 
                    dependencies = depend
                };
                Networking.Send(theServer, JsonConvert.SerializeObject(edit) + ENDOFMESSAGE);
            }
            else
            {
                // create a JSon object
                var edit = new
                {
                    type = "edit",
                    cell = cellName,
                    value = cellContents, 
                    dependencies = depend
                };
                Networking.Send(theServer, JsonConvert.SerializeObject(edit) + ENDOFMESSAGE);
            }
           
        }

        /// <summary>
        /// Method that the client will call when a spreadsheet undo is requested
        /// </summary>
        public void ClientUndo()
        {
            // create the request
            var undo = new { type = "undo" };
            // send the message
            Networking.Send(theServer, JsonConvert.SerializeObject(undo) + ENDOFMESSAGE);
        }


        /// <summary>
        /// Method that the client will call when a spreadsheet revert is requested
        /// </summary>
        /// <param name="cellName"></param>
        /// <param name="cellContents"></param>
        public void ClientRevert(string cellName)
        {
            // create the request
            var revert = new { type = "revert", cell = cellName };
            // send the message
            Networking.Send(theServer, JsonConvert.SerializeObject(revert) + ENDOFMESSAGE);
        }

        /// <summary>
        /// Basic function for receiving edits in the server-client edit loop
        /// </summary>
        /// <param name="ss"></param>
        private void ReceiveEdit(SocketState ss)
        {
            string totalData = ss.sb.ToString();
            string[] parts = Regex.Split(totalData, @"(?<=[\n][\n])");

           // lock (sheet)
            {
                foreach (string p in parts)
                {
                    // ignore empty strings
                    if (p.Length == 0)
                    {
                        continue;
                    }
                    // if the last two chars are not new lines then there are
                    // no more full messages be evaluated

                    if (p.Length < 3)
                    {
                        continue;
                    }
                    if (p[p.Length - 1] != '\n' || p[p.Length - 2] != '\n')
                    {
                        break;
                    }

                    // Create a dynamic type for processing the kind of message sent
                    var recieve = new
                    {
                        type = ""
                    };

                    var check = JsonConvert.DeserializeAnonymousType(p, recieve);

                    if (check.type == "error")
                    {
                        ProcessError(p);

                    }
                    else if (check.type == "full send")
                    {
                        ProcessFullSend(p);
                    }
                    // if unexpected message comes ignore it for now?? ...
                    ss.sb.Remove(0, p.Length);

                }
            }

            // ask for more data
            Networking.GetData(ss);
        }

        /// <summary>
        /// Helper Method for Processing an Error message from the server
        /// </summary>
        /// <param name="v"></param>
        private void ProcessError(string message)
        {
            //Deserialize the message
            var error = new
            {
                type = "",
                code = 0,
                source = ""
            };

            error = JsonConvert.DeserializeAnonymousType(message, error);

            if (error.code == 1)
            {
                // notify the client
                SpreadsheetError(error.code, "");
            }
            else // code 2
            {
                // notify the client
                SpreadsheetError(error.code, error.source);
            }
        }

       

        /// <summary>
        /// Helper Method for Processing a Full Send message from the server
        /// </summary>
        /// <param name="sb"></param>
        private void ProcessFullSend(string message)
        {
            var fullsend = new
            {
                type = "",
                spreadsheet = new Dictionary<string, string>()
            };

            fullsend = JsonConvert.DeserializeAnonymousType(message, fullsend);
            Dictionary<string, string> edits = fullsend.spreadsheet;

            Dictionary<string, IEnumerable<string>> cellDependencies = new Dictionary<string, IEnumerable<string>>();
           // lock (sheet)
            {
                // process changes
                foreach (string cell in edits.Keys)
                {
                   cellDependencies[cell] = this.sheet.SetContentsOfCell(cell, edits[cell]);
                }



            }
            // let the subscribers (client) know that the spreadsheet has been updated
            SpreadsheetUpdated(cellDependencies);

        }
    }
}

