using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

/// <summary>
/// Took from Lab11, UofU CS3500 course
/// Slightly changed and updated by Zachary Muhlestein and Connor Grimes
/// Assignment 07, CS 3500
/// 18 November 2018
/// </summary>
/// </summary>
namespace NetworkController
{
    //delegate used to hold the method that will be sent by caller and called by this class
    //once it is completed with its communication
    public delegate void NetworkAction(SocketState ss);

    public delegate void ServerAction(ConnectionState cs);



    /// <summary>
    /// This class holds all the necessary state to represent a socket connection
    /// Note that all of its fields are public because we are using it like a "struct"
    /// It is a simple collection of fields
    /// </summary>
    public class SocketState
    {
        //The socket 
        public Socket theSocket;
        //
        public int ID;

        // This is the buffer where we will receive data from the socket
        public byte[] messageBuffer = new byte[1024];

        // This is a larger (growable) buffer, in case a single receive does not contain the full message.
        public StringBuilder sb = new StringBuilder();

        public NetworkAction callMe;


        /// <summary>
        /// This is the constructer for this class. This class only holds certain things like the Socket and its ID
        /// so that it can be passed around with the relivent information for other methods to use.
        /// </summary>
        /// <param name="s"> Socket to hold</param>
        /// <param name="id"> Socket State ID to differentiate from others</param>
        public SocketState(Socket s, int id)
        {
            theSocket = s;
            ID = id;

        }
    }

    public class ConnectionState
    {
        //The socket 
        public Socket theSocket;
        //a tcplistener to use
        public TcpListener listener;

        //a method to call
        public NetworkAction callMe;


    }

    /// <summary>
    /// This class has all the relevant methods to be able to connect and communicate to a 
    /// server
    /// </summary>
    public class Networking
    {
        //random port to communicate through
        public const int DEFAULT_PORT = 2112;

        public static event NetworkAction DisconnectedFromServer;

        /// <summary>
        /// Creates a Socket object for the given host string
        /// </summary>
        /// <param name="hostName">The host name or IP address</param>
        /// <param name="socket">The created Socket</param>
        /// <param name="ipAddress">The created IPAddress</param>
        public static void MakeSocket(string hostName, out Socket socket, out IPAddress ipAddress)
        {
            //initializes the IP Address and socket (solves scope issues)
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
                        System.Diagnostics.Debug.WriteLine("Invalid addres: " + hostName);
                        throw new ArgumentException("Invalid address");
                    }
                }
                catch (Exception)
                {
                    // see if host name is actually an ipaddress, i.e., 155.99.123.456
                    System.Diagnostics.Debug.WriteLine("using IP");
                    ipAddress = IPAddress.Parse(hostName);
                }

                // Create a TCP/IP socket.
                socket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                socket.SetSocketOption(SocketOptionLevel.IPv6, SocketOptionName.IPv6Only, false);

                // Disable Nagle's algorithm - can speed things up for tiny messages, 
                // such as for a game
                socket.NoDelay = true;

            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("Unable to create socket. Error occured: " + e);
                throw new ArgumentException("Invalid address");
            }
        }

        /// <summary>
        /// Start attempting to connect to the server
        /// </summary>
        /// <param name="hostName"> server to connect to </param>
        /// <returns>Returns the socket of the server</returns>
        public static Socket ConnectToServer(string hostName, NetworkAction call)
        {
            System.Diagnostics.Debug.WriteLine("connecting  to " + hostName);

            // Create a TCP/IP socket.
            Socket socket;
            IPAddress ipAddress;
            //creates socket
            Networking.MakeSocket(hostName, out socket, out ipAddress);

            //makes socket state to hold socket and relivent info
            SocketState ss = new SocketState(socket, -1);
            ss.callMe = call;

            //starts communication
            socket.BeginConnect(ipAddress, Networking.DEFAULT_PORT, ConnectedCallback, ss);
            //returns the socket
            return socket;

        }
        /// <summary>
        /// This function is "called" by the operating system when the remote site acknowledges the connect request
        /// </summary>
        /// <param name="ar">Async result</param>
        private static void ConnectedCallback(IAsyncResult ar)
        {
            //get the socketstate out of the asincresult passed in
            SocketState ss = (SocketState)ar.AsyncState;

            try
            {
                // Complete the connection.
                ss.theSocket.EndConnect(ar);
            }
            catch (Exception except)
            {
                //let the user know there were errors
                System.Diagnostics.Debug.WriteLine("Unable to connect to server. Error occured: " + except);

            }

            // Call what we have been told to call so caller can continue as requested.
            ss.callMe(ss);
        }
        /// <summary>
        /// This function is "called" by the operating system when data arrives on the socket
        /// </summary>
        /// <param name="ar">Async result</param>
        private static void ReceiveCallback(IAsyncResult ar)
        {
            //get the socketstate out of the asincresult passed in
            SocketState ss = (SocketState)ar.AsyncState;
            int bytesRead = 0;
            try
            {
                //get the message that was sent
                bytesRead = ss.theSocket.EndReceive(ar);
            }
            catch (Exception)
            {

                Console.WriteLine("Client: " + ss.ID + " was disconnected");
            }

            // If the socket is still open
            if (bytesRead > 0)
            {
                string theMessage = Encoding.UTF8.GetString(ss.messageBuffer, 0, bytesRead);
                // Append the received data to the growable buffer.
                // It may be an incomplete message, so we need to start building it up piece by piece
                ss.sb.Append(theMessage);

                //ProcessMessage(ss);
                ss.callMe(ss);
            }


        }

        /// <summary>
        /// Method that allows caller to begin recieving data from server
        /// </summary>
        /// <param name="ss">Socket State used</param>
        public static void GetData(SocketState ss)
        {
            try
            {
                ss.theSocket.BeginReceive(ss.messageBuffer, 0, ss.messageBuffer.Length, SocketFlags.None, ReceiveCallback, ss);

            }
            catch (Exception)
            {
                DisconnectedFromServer(ss);
            }
        }

        /// <summary>
        /// A callback invoked when a send operation completes
        /// </summary>
        /// <param name="ar">Async result</param>
        public static void SendCallback(IAsyncResult ar)
        {
            SocketState ss = null;
            Socket s = null;

            try
            {
                ss = (SocketState)ar.AsyncState;
            }
            catch (Exception)
            {

                s = (Socket)ar.AsyncState;
            }
            // Nothing much to do here, just conclude the send operation so the socket is happy.
            try
            {
                if (ss != null)
                    ss.theSocket.EndSend(ar);
                else
                    s.EndSend(ar);
            }
            catch (Exception e)
            {


                if (s == null)
                    DisconnectedFromServer(ss);
            }
        }
        /// <summary>
        /// This method awaits a new client to serve
        /// </summary>
        /// <param name="call">The network action being passed in to the socketstate</param>
        public static void ServerAwaitingClientLoop(NetworkAction call)
        {
            //create a listener on the 11000 port and start listening
            TcpListener clientListener = new TcpListener(IPAddress.Any, 11000);
            clientListener.Start();
            //tell the server console that we have started waiting
            Console.WriteLine("Awaiting Clients...");
            //create a new connectionState and fill it with required items
            ConnectionState cs = new ConnectionState();
            cs.listener = clientListener;
            cs.callMe = call;
            //begin accepting sockets
            clientListener.BeginAcceptSocket(AcceptNewClient, cs);

        }

        /// <summary>
        /// This method does what is neccesary to accept new clients
        /// </summary>
        /// <param name="ar">Async result</param>
        private static void AcceptNewClient(IAsyncResult ar)
        {
            //grab the connection state out of the result
            ConnectionState cs = (ConnectionState)ar.AsyncState;
            //create a socket out of the listener
            Socket socket = cs.listener.EndAcceptSocket(ar);
            //create a socket state with the needed information
            SocketState ss = new SocketState(socket, -1);
            ss.theSocket = socket;
            ss.callMe = cs.callMe;
            //call the given method
            ss.callMe(ss);
            //begin the cycle of accepting new clients again.
            cs.listener.BeginAcceptSocket(AcceptNewClient, cs);
            //let server know someone new has entered the battlefield
            Console.WriteLine("A client has connected");
        }

    }

}
