using NetworkController;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;




namespace AdminClient
{
    class ServerControllerControl
    {
        private Socket theServer;
        private SocketState serverSocketState;
        public delegate void MessageArrivedHandler(IEnumerable<string> message);
        ServerControllerView view;
        public delegate void CloseHandler();
        public event CloseHandler closeEvent;

        public ServerControllerControl(ServerControllerView toUse)
        {
            view = toUse;
            try//connect
            {
                Networking.DisconnectedFromServer += unableToStayConnected;
                theServer = Networking.ConnectToServer(ServerControllerView.host, tryContact);
            }
            catch (Exception)//tell the view to communicate the error
            {

                throw new Exception();
            }
        }

        public void tryContact(SocketState ss)
        {
            if (!ss.theSocket.Connected)
            {
                view.issuesLogingIn = true;
                return;
            }

            ss.callMe = recieveStartupInfo;
            serverSocketState = ss;
            byte[] messageBytes = Encoding.UTF8.GetBytes("{\"type\":\"Admin\"}" + "\n" + "\n");

            theServer.BeginSend(messageBytes, 0, messageBytes.Length, SocketFlags.None, Networking.SendCallback, theServer);

        }

        public void startGetData()
        {
            Networking.GetData(serverSocketState);
        }

        private void recieveStartupInfo(SocketState ss)
        {
            string unfilteredInput = ss.sb.ToString();
            string[] incomingParts = Regex.Split(unfilteredInput, @"(?<=[\n][\n])");


            foreach (string input in incomingParts)
            {


                if (!input.Equals(""))
                {
                    if (input[input.Length - 1] == '\n')
                    {
                        JObject obj = JObject.Parse(input);
                        RecievedDataList recievedDataList;
                        if (obj["type"] != null)
                        {


                            if (obj["Spreadsheets"] != null)
                            {

                                recievedDataList = JsonConvert.DeserializeObject<RecievedDataList>(input);

                                view.recieveListData(recievedDataList.names(), 1);
                            }
                            else if (obj["Users"] != null)
                            {

                                recievedDataList = JsonConvert.DeserializeObject<RecievedDataList>(input);

                                view.recieveListData(recievedDataList.names(), 0);
                            }

                            else if (obj["sorce"] != null)
                            {
                                view.errorMessageShow(obj["source"].ToString());
                            }
                        }
                        ss.sb.Remove(0, input.Length);

                    }
                }
            }

            Networking.GetData(ss);
        }



        internal void endContact()
        {
            theServer.Disconnect(false);
        }

        public void SendCommand(OperationAdmin command)
        {


            byte[] messageBytes = Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(command) + "\n" + "\n");

            theServer.BeginSend(messageBytes, 0, messageBytes.Length, SocketFlags.None, Networking.SendCallback, theServer);
        }

        public void unableToStayConnected(SocketState ss)
        {
            closeEvent();
        }

    }

    public class RecievedDataList
    {


        [JsonProperty(PropertyName = "Spreadsheets")]
        private string[] namesSpread;
        [JsonProperty(PropertyName = "Users")]
        private string[] namesUser;





        public string[] names()
        {
            List<string> toreturn = new List<string>();
            if (namesUser != null)
            {

                return namesUser;
            }
            else
            {
                return namesSpread;
            }
        }

    }

    public class OperationAdmin
    {

        [JsonProperty(PropertyName = "Operation")]
        private string function;

        [JsonProperty(PropertyName = "Name")]
        public String name;

        [JsonProperty(PropertyName = "Password")]
        private String password;

        public OperationAdmin(String func, string nam, string pass)
        {
            function = func;
            name = nam;
            password = pass;
        }


    }
}

