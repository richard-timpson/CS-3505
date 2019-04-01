using Newtonsoft.Json;
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
            ProcessFullSend(ss.sb.ToString());
            //or
            ProcessError(ss.sb.ToString());

            throw new NotImplementedException();
        }

        /// <summary>
        /// Helper Method for Processing an Error message from the server
        /// </summary>
        /// <param name="v"></param>
        private void ProcessError(string message)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Helper Method for Processing a Full Send message from the server
        /// </summary>
        /// <param name="sb"></param>
        private void ProcessFullSend(string message)
        {
            throw new NotImplementedException();
        }
    }
}
