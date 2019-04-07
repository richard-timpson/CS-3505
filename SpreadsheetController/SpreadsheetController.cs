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

        public delegate void SpreadsheetUpdatedEventHandler();
        public event SpreadsheetUpdatedEventHandler SpreadsheetUpdated;

        public delegate void SpreadsheetReceivedHandler();
        public event SpreadsheetReceivedHandler SpreadsheetReceived;

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

        public SpreadsheetController(Spreadsheet spreadsheet)
        {
            sheet = spreadsheet;
        }
        /// <summary>
        /// Connects to the given server initiating the client server handshake
        /// </summary>
        /// <param name="ipAddress"></param>
        public void Connect(string ipAddress, string username, string password)
        {
            
            Username = username;
            Password = password;
            theServer = Networking.ConnectToServer(ipAddress, RecieveSpreadsheetsList);
        }

        /// <summary>
        /// Receive a list of available spreadsheets
        /// </summary>
        /// <param name="ss"></param>
        private void RecieveSpreadsheetsList(SocketState ss)
        {
            // TODO Process List of Spreadsheets
            // IGNORE MESSAGES OTHER THAN THE LIST OF SPREADSHEETS

            // Set up the loop
            ss.CallMe = ReceiveEdit;

            // Create a dynamic type for processing the kind of message sent
            var recieve = new
            {
                type = ""
            };

            var message = JsonConvert.DeserializeAnonymousType(ss.sb.ToString(), recieve);
            
            // ignore if it is the wrong kind of message
            if(message.type != "list")
            {
                ss.sb.Clear();
                return;
            }

            //Otherwise Process the message and output the lists
            var list = new
            {
                type = "",
                sheets = new string[0]
            };

            list = JsonConvert.DeserializeAnonymousType(ss.sb.ToString(), list);



            //TODO send an open message SET UP SOME KIND OF EVENT LOOP WITH CLIENT
            // send desired spreadsheet
            // send desired username
            // send password

            // Networking.Send(ss.theSocket, Username + ENDOFMESSAGE);
            // Networking.GetData(ss);

            //var mess = new
            //{
            //    type = ss.sb.ToString(),
            //    cell = "A1",
                
            //};
            //JsonConvert.SerializeObject(mess);

            ///string message = Json(mess);

        }

        /// <summary>
        /// Method that the CLient will call when a spreadsheet cell is updated
        /// </summary>
        /// <param name="cellName"></param>
        /// <param name="cellContents"></param>
        public void ClientUpdate(string cellName, string cellContents)
        {
            //TODO Process edit and send to server
            // 
            // TODO MAKE SURE THAT AN ACTUAL AND VALID CHANGE HAS BEEN MADE BY THE CLIENT

            
            throw new NotImplementedException();
        }

        /// <summary>
        /// Method that the client will call when a spreadsheet undo is requested
        /// </summary>
        /// <param name="cellName"></param>
        /// <param name="cellContents"></param>
        public void ClientUndo(string cellName, string cellContents)
        {
            // TODO Send an undo request
            throw new NotImplementedException();
        }


        /// <summary>
        /// Method that the client will call when a spreadsheet revert is requested
        /// </summary>
        /// <param name="cellName"></param>
        /// <param name="cellContents"></param>
        public void ClientRevert(string cellName, string cellContents)
        {
            // TODO Send an revert request
            throw new NotImplementedException();
        }


        /// <summary>
        /// Basic function for receiving edits in the server-client edit loop
        /// </summary>
        /// <param name="ss"></param>
        private void ReceiveEdit(SocketState ss)
        {

            //TODO Process Full Send
            string totalData = ss.sb.ToString();
            string[] parts = Regex.Split(totalData, @"(?<=[\n\n])");

            foreach (string p in parts)
            {
                // ignore empty strings
                if(p.Length == 0)
                {
                    continue;
                }
                // if the last two chars are not new lines then there are
                // no more full messages be evaluated
                if (p[p.Length - 1] != '\n' && p[p.Length -2] != '\n')
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

            // ask for more data
            Networking.GetData(ss);
        }

        /// <summary>
        /// Helper Method for Processing an Error message from the server
        /// </summary>
        /// <param name="v"></param>
        private void ProcessError(string message)
        {
            var error = new
            {
                type = "",
                code = 0,
                source = ""
            };

            error = JsonConvert.DeserializeAnonymousType(message, error);

            if( error.code == 1)
            {
                // TODO notify client
            }
            else // code 2
            {
                // TODO notify client
                string source = error.source;
            }

            //TODO send error to client


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
                spreadsheet = new Spreadsheet()
            };

            fullsend = JsonConvert.DeserializeAnonymousType(message, fullsend);
            Spreadsheet edits = fullsend.spreadsheet;
            // process all of the edits
            foreach (string cell in edits.GetNamesOfAllNonemptyCells())
            {
                 
                object contents = edits.GetCellContents(cell);
                //check what kind of object GetCellContents returned
                if(contents is string)
                {
                    // TODO
                    // if it is an empty string it is actually a delete
                    this.sheet.SetContentsOfCell(cell, (string)edits.GetCellContents(cell));
                    
                } else if (contents is double)
                {
                    this.sheet.SetContentsOfCell(cell, (string) edits.GetCellContents(cell));
                }
                else // else it is a formula
                {
                    Formula formulaContents = (Formula) contents;

                    string formulaString = formulaContents.ToString();

                    this.sheet.SetContentsOfCell(cell, "=" + formulaString);

                }

            }




        }
    }
}
