using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using UnityEngine;


namespace Client
{
    
    public class SocketClient
    {
        public static string MessageR;
        public static void StartClient(string txt)
        {
            byte[] bytes = new byte[1024];

            try
            {
                IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
                IPAddress ipAddress = ipHostInfo.AddressList[0];
                IPEndPoint remoteEP = new IPEndPoint(ipAddress, 11000);

                Socket sender = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                try
                {
                    sender.Connect(remoteEP);

                    Console.WriteLine("Socket connected to {0}",
                        sender.RemoteEndPoint.ToString());

                    // Encode the data string into a byte array.  



                    byte[] msg = Encoding.ASCII.GetBytes(txt);

                    // Send the data through the socket.  
                    int bytesSent = sender.Send(msg);

                    // Receive the response from the remote device.  
                    int bytesRec = sender.Receive(bytes);
                    MessageR = Encoding.ASCII.GetString(bytes, 0, bytesRec);
                    
                    // Release the socket.  
                    sender.Shutdown(SocketShutdown.Both);
                    sender.Close();

                }
                catch (ArgumentNullException ane)
                {
                    Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
                }
                catch (SocketException se)
                {
                    Console.WriteLine("SocketException : {0}", se.ToString());
                }
                catch (Exception e)
                {
                    Console.WriteLine("Unexpected exception : {0}", e.ToString());
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

        }

        public static int Main(String[] args)
        {
            while (true)
            {
                Console.WriteLine("Introduzca un texto");
                string txt = Console.ReadLine();
                StartClient(txt);
            }

            return 0;
        }
    }
}