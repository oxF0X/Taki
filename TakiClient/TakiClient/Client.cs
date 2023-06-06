using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Net.NetworkInformation;
using JsonRequestPacketSerializer;
using JsonRequestPacketDeserializer;


namespace Client 
{
    class Client
    {
        const int ERROR_CODE = 102;
        const int LOGIN_RES = 100;
        const int SIGNUP_RES = 101;

        private TcpClient socket;
        NetworkStream clientStream;

        public Client()
        {
            this.socket = new TcpClient();
            this.socket.Connect(IPAddress.Parse("127.0.0.1"), 4444);
            this.clientStream = this.socket.GetStream();
        }

        public string GetLogin(string username, string password)
        {
            string data = JsonRequestPacketSerializer.JsonRequestPacketSerializer.SerializeLogin(username, password);
            this.clientStream.Write(Encoding.UTF8.GetBytes(data), 0, data.Length);
            int code = this.GetCodeFromSocket();
            int size = this.GetSizeFromSocket();
            if (size <= 0)
            {
                return "Something went wrong";
            }

            byte[] buffer = new byte[size];
            this.clientStream.Read(buffer, 0, size);
            string str = System.Text.Encoding.Default.GetString(buffer);
            
            switch(code)
            {
                case ERROR_CODE:
                    return (JsonRequestPacketDeserializer.JsonRequestPacketDeserializer.DeserializeError(str)).message;

                case LOGIN_RES:
                    return ((JsonRequestPacketDeserializer.JsonRequestPacketDeserializer.DeserializeLogIn(str)).status).ToString();

                case SIGNUP_RES:
                    return ((JsonRequestPacketDeserializer.JsonRequestPacketDeserializer.DeserializeSignUp(str)).status).ToString();


                default:
                    return "Something went wrong";
            }

        }

        private byte GetCodeFromSocket()
        {
            byte [] buffer = new byte[1];
            this.clientStream.Read(buffer, 0, 1);
            return buffer[0];
        }

        private int GetSizeFromSocket()
        {
            byte[] bytes = new byte[4];
            this.clientStream.Read(bytes, 0, 4);
            return (int)((bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0]);
        }


    }
}
