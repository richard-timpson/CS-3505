using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace CS3505
{
    /// <summary>
    /// WE MIGHT NOT NEED THIS BECAUSE IT WILL BE IMPLEMENTED IN C++?
    /// </summary>
    /// <param name="ss"></param>

    public delegate void NetworkAction(SocketState ss);

    /// <summary>
    /// This class holds all the necessary state to represent a socket connection
    /// Note that all of its fields are public because we are using it like a "struct"
    /// It is a simple collection of fields
    ///  Author: Tyler Brewster and Peter Forsling and Daniel Kopta
    /// Version: November 2018
    /// </summary>
    public class SocketState
    {
        public Socket theSocket;
        public int ID;
        public NetworkAction CallMe;
        public delegate void ConnectionTimeoutEventHandler();
        public event ConnectionTimeoutEventHandler Timeout;

        // This is the buffer where we will receive data from the socket
        public byte[] messageBuffer = new byte[2048];

        // This is a larger (growable) buffer, in case a single receive does not contain the full message.
        public StringBuilder sb = new StringBuilder();

        /// <summary>
        /// Constructs a new SocketState
        /// </summary>
        /// <param name="s">The socket the SocketState is based off of</param>
        /// <param name="id">The ID of the owner of the socket</param>
        public SocketState(Socket s, int id)
        {
            theSocket = s;
            ID = id;
        }
    }
    /// <summary>
    /// This class holds the necessary information to pass around a delegate call me 
    /// and a Tcp listener for clients to interact with the server. It is a simple
    /// collection of fields. 
    /// Author: Tyler Brewster and Peter Forsling and Daniel Kopta
    /// Version: November 2018
    /// </summary>
    public class ServerState
    {
        public TcpListener listener;
        public NetworkAction CallMe;

        //TODO ask about ID??
        public ServerState(TcpListener listen)
        {
            listener = listen;
        }

    }

    /// <summary>
    /// A static class devoted to Connecting, receiving, and sending data
    /// from one location to another
    /// Authors: Tyler Brewster, Peter Forsling, Professor Daniel Kopta
    /// Version: December 2018
    /// </summary>
    public static class Networking
    {
        public delegate void ConnectionTimeoutEventHandler();
        public static event ConnectionTimeoutEventHandler Timeout;

        public delegate void ConnectionLostEventHandler();
        public static event ConnectionLostEventHandler ConnectionLost;


        public const int DEFAULT_PORT = 2112;

        /// <summary>
        /// Creates a Socket object for the given host string
        /// </summary>
        /// <param name="hostName">The host name or IP address</param>
        /// <param name="socket">The created Socket</param>
        /// <param name="ipAddress">The created IPAddress</param>
        public static void MakeSocket(string hostName, out Socket socket, out IPAddress ipAddress)
        {

            ipAddress = IPAddress.None;
            socket = null;
            try
            {
                // Establish the remote endpoint for the socket.
                IPHostEntry ipHostInfo;

                // Determine if the server address is a URL or an IP
                try
                {
                    ipHostInfo = Dns.GetHostEntry(hostName);
                    bool foundIPV4 = false;
                    foreach (IPAddress addr in ipHostInfo.AddressList)
                        if (addr.AddressFamily != AddressFamily.InterNetworkV6)
                        {
                            foundIPV4 = true;
                            ipAddress = addr;
                            break;
                        }
                    // Didn't find any IPV4 addresses
                    if (!foundIPV4)
                    {

                        throw new ArgumentException("Invalid address");
                    }
                }
                catch (Exception)
                {
                    // see if host name is actually an ipaddress, i.e., 155.99.123.456

                    ipAddress = IPAddress.Parse(hostName);
                }

                // Create a TCP/IP socket.
                socket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                socket.SetSocketOption(SocketOptionLevel.IPv6, SocketOptionName.IPv6Only, false);

                // Disable Nagle's algorithm - can speed things up for tiny messages, 
                // such as for a game
                socket.NoDelay = true;

            }
            catch 
            {

                throw new ArgumentException("Invalid address");
            }
        }

        /// <summary>
        /// Start attempting to connect to the server
        /// Move this function to a standalone networking library.
        /// </summary>
        /// <param name="hostName"> server to connect to </param>
        /// <returns>a socket containing the connection</returns>
        public static Socket ConnectToServer(string hostName, NetworkAction call)
        {


            // Create a TCP/IP socket.
            Socket socket;
            IPAddress ipAddress;

            Networking.MakeSocket(hostName, out socket, out ipAddress);

            SocketState ss = new SocketState(socket, -1);
            ss.CallMe = call;

            socket.BeginConnect(ipAddress, Networking.DEFAULT_PORT, ConnectedCallback, ss);

            return socket;

        }

        /// <summary>
        /// This function is "called" by the operating system when the remote site acknowledges the connect request
        /// Move this function to a standalone networking library.
        /// </summary>
        /// <param name="ar"></param>
        private static void ConnectedCallback(IAsyncResult ar)
        {
            SocketState ss = (SocketState)ar.AsyncState;

            try
            {
                // Complete the connection.
                ss.theSocket.EndConnect(ar);
            }
            catch (System.Net.Sockets.SocketException e)
            {
                System.Diagnostics.Debug.WriteLine(e.Message);
                return;
            }
            // Start an event loop to receive data from the server/ client.
            ss.CallMe(ss);


        }
        /// <summary>
        /// Public method to request information
        /// </summary>
        /// <param name="ss"></param>
        public static void GetData(SocketState ss)
        {
            try
            {
                ss.theSocket.BeginReceive(ss.messageBuffer, 0, ss.messageBuffer.Length, SocketFlags.None, ReceiveCallback, ss);
            }
            catch(Exception e)
            {

            }
        }

        /// <summary>
        /// Send information to the Network Controller
        /// </summary>
        /// <param name="message">The message to be sent</param>
        /// <returns>True if the send was successful, false otherwise</returns>
        public static bool Send(Socket s, string message)
        {
            //FIXME Handle disconnected clients
            // append a newline and send data
            byte[] messageBytes = Encoding.UTF8.GetBytes(message);
            try
            {
                s.BeginSend(messageBytes, 0, messageBytes.Length, SocketFlags.None, SendCallback, s);
                return true;
            }
            catch 
            {
                System.Diagnostics.Debug.WriteLine("Send Exception caught");
                return false;
            }


        }

        /// <summary>
        /// Sends call back and ends the send
        /// </summary>
        /// <param name="ar"></param>
        private static void SendCallback(IAsyncResult ar)
        {
            Socket s = (Socket)ar.AsyncState;

            try
            {
                if (s.Connected)
                {
                    s.EndSend(ar);

                }
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("SendCallback Exception caught");
                s.Close();
                ConnectionLost();
            }


        }


        /// <summary>
        /// This function is "called" by the operating system when data arrives on the socket
        /// </summary>
        /// <param name="ar"></param>
        private static void ReceiveCallback(IAsyncResult ar)
        {
            SocketState ss = (SocketState)ar.AsyncState;
            try
            {

                int bytesRead = ss.theSocket.EndReceive(ar);


                // If the socket is still open
                if (bytesRead > 0)
                {
                    string theMessage = Encoding.UTF8.GetString(ss.messageBuffer, 0, bytesRead);
                    // Append the received data to the growable buffer.
                    // It may be an incomplete message, so we need to start building it up piece by piece
                    lock (ar)
                    {
                        ss.sb.Append(theMessage);
                    }
                    ss.CallMe(ss);
                }
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.Message);
                System.Diagnostics.Debug.WriteLine(e.StackTrace);
                ss.theSocket.Close();
                ConnectionLost();
            }
            // continue the loop -- actually happens in ss.CallMe


        }

        //TODO Verify and complete New Methods for PS8
        /// <summary>
        /// The "heart" of the server code. This starts a TCP listener and then 
        /// gives the server the needed information to start the event loop
        /// </summary>
        /// <param name="CallThis"></param>
        public static void ServerAwaitingClientLoop(NetworkAction CallThis)
        {
            TcpListener listn = new TcpListener(IPAddress.Any, DEFAULT_PORT);

            listn.Start();

            ServerState serv = new ServerState(listn);

            serv.CallMe = CallThis;


            listn.BeginAcceptSocket(AcceptNewClient, serv);

        }
        // FIXME?
        /// <summary>
        /// Call back that begin Accept Socket uses for TCP Listening. 
        /// Uses the AsyncResult to extract a ServerState and then create a new
        /// socket
        /// </summary>
        /// <param name="ar"></param>
        private static void AcceptNewClient(IAsyncResult ar)
        {
            ServerState serv = (ServerState)ar.AsyncState;

            Socket s = serv.listener.EndAcceptSocket(ar);

            SocketState ss = new SocketState(s, -1);

            ss.CallMe = serv.CallMe;

            ss.CallMe(ss);

            serv.listener.BeginAcceptSocket(AcceptNewClient, serv);


        }
    }
}
