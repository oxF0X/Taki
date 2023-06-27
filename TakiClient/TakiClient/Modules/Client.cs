using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Text.Json;

namespace TakiClient.Modules
{
    public class Client
    {
        const int ERROR_CODE = 102;
        const int LOGIN_RES = 100;
        const int SIGNUP_RES = 101;
        const int GET_ROOMS_RES = 103;
        const int CREATE_ROOMS_RES = 106;
        const int JOIN_ROOMS_RES = 105;
        const int SIGNOUT_RES = 111;
        const int GET_PLAYERS_RES = 104;
        const int GET_ROOM_STATE_RES = 110;
        const int GET_LEAVE_ROOM_RES = 109;
        const int GET_CLOSE_ROOM_RES = 107;
        const int GET_START_GAME_RES = 108;
        const int GET_GAME_STATE_RES = 112;




        const int GET_ROOMS_REQ = 13;
        const int GET_SIGN_OUT = 12;
        const int GET_LEAVE_ROOM = 19;
        const int GET_CLOSE_ROOM = 17;
        const int GET_START_GAME_REQ = 18;
        const int GET_GAME_STATE_REQ = 24;
        const int PlayCard_REQ = 22;
        const int DrawCard_REQ = 23;
        const int GetGameResult_REQ = 25;




        private TcpClient socket;
        private static Client instance;
        NetworkStream clientStream;

        public Client()
        {
            socket = new TcpClient();
            socket.Connect(IPAddress.Parse("127.0.0.1"), 4444);
            clientStream = socket.GetStream();
        }

        ~Client()
        {
            this.socket.Close();
        }


        public string GetLogin(string username, string password)
        {
            byte[] data = JsonRequestPacketSerializer.SerializeLogin(username, password);
            clientStream.Write(data, 0, data.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return "Something went wrong";
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);

            switch (code)
            {
                case ERROR_CODE:
                    return JsonRequestPacketDeserializer.DeserializeError(str).message;

                case LOGIN_RES:
                    return JsonRequestPacketDeserializer.DeserializeLogIn(str).status.ToString();

                default:
                    return "Something went wrong";
            }
        }

        public RoomData[] GetRooms()
        {
            byte [] reqCode = new byte[5] { GET_ROOMS_REQ, 0, 0, 0, 0 };
            clientStream.Write(reqCode, 0, reqCode.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return null;
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);

            switch (code)
            {
                case ERROR_CODE:
                    return null;

                case GET_ROOMS_RES:
                    return JsonRequestPacketDeserializer.DeserializeGetRooms(str).rooms;

                default:
                    return null;
            }
        }

        public string CreateRoom(string roomName, int maxUsers, int answerTimeout)
        {
            byte[] req = JsonRequestPacketSerializer.SerializeCreateRoom(roomName, maxUsers, answerTimeout);
            clientStream.Write(req, 0, req.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return "Something went wrong";
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);

            switch (code)
            {
                case ERROR_CODE:
                    return JsonRequestPacketDeserializer.DeserializeError(str).message;

                case CREATE_ROOMS_RES:
                    return JsonRequestPacketDeserializer.DeserializeLogIn(str).status.ToString();
                default:
                    return "Something went wrong";
            }
        }

        public string GetSignup(string username, string password, string email, string address, string birthday, string phoneNumber)
        {
            byte[] data = JsonRequestPacketSerializer.SerializeSignup(username, password, email, address, birthday, phoneNumber);
            clientStream.Write(data, 0, data.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return "Something went wrong";
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);

            switch (code)
            {
                case ERROR_CODE:
                    return JsonRequestPacketDeserializer.DeserializeError(str).message;

                case SIGNUP_RES:
                    return JsonRequestPacketDeserializer.DeserializeLogIn(str).status.ToString();

                default:
             
                    return "Something went wrong";
            }
        }

        public bool GetLogout()
        {
            byte[] reqCode = new byte[5] { GET_SIGN_OUT, 0, 0, 0, 0 };
            clientStream.Write(reqCode, 0, reqCode.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return false;
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);
            

            return code == SIGNOUT_RES;
        }


        public string[] GetPlayersInRoom(int roomId)
        {
            byte[] data = JsonRequestPacketSerializer.SerializeGetPalayersInRoom(roomId);
            clientStream.Write(data, 0, data.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();


            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);


            if (code != GET_PLAYERS_RES)
            {
                return new String[1] { JsonRequestPacketDeserializer.DeserializeError(str).message };
            }

            return JsonRequestPacketDeserializer.DeserializeGetPalyersInRoom(str).players;

        }

        public string GetJoinRoom(int roomId)
        {
            byte[] data = JsonRequestPacketSerializer.SerializeJoinRoom(roomId);
            clientStream.Write(data, 0, data.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return "Something went wrong";
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);


            if (code != JOIN_ROOMS_RES)
            {
                return JsonRequestPacketDeserializer.DeserializeError(str).message;
            }

            return JsonRequestPacketDeserializer.DeserializeLogIn(str).status.ToString();

        }


        public GetRoomsStateResponse? GetRoomState()
        {
            byte[] reqCode = new byte[5] { JsonRequestPacketSerializer.GET_ROOM_STATE_REQ, 0, 0, 0, 0 };
            clientStream.Write(reqCode, 0, reqCode.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return null;
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);
            
            return code == GET_ROOM_STATE_RES ? JsonRequestPacketDeserializer.DeserializeGetRoomState(str) : null;
        }


        public bool GetLeaveRoom()
        {
            byte[] reqCode = new byte[5] { GET_LEAVE_ROOM, 0, 0, 0, 0 };
            clientStream.Write(reqCode, 0, reqCode.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return false;
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);


            return code == GET_LEAVE_ROOM_RES;
        }

        public bool GetCloseRoom()
        {
            byte[] reqCode = new byte[5] { GET_CLOSE_ROOM, 0, 0, 0, 0 };
            clientStream.Write(reqCode, 0, reqCode.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return false;
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);


            return code == GET_CLOSE_ROOM_RES;
        }

        public bool GetStartGame()
        {
            byte[] reqCode = new byte[5] { GET_START_GAME_REQ, 0, 0, 0, 0 };
            clientStream.Write(reqCode, 0, reqCode.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return false;
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            
            //string str = Encoding.Default.GetString(buffer);


            return code == GET_START_GAME_RES;
        }


        public GetGameStateResponse? GetGameState()
        {
            byte[] reqCode = new byte[5] { GET_GAME_STATE_REQ, 0, 0, 0, 0 };

            clientStream.Write(reqCode, 0, reqCode.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return null;
            }

            byte[] buffer = new byte[size];
            clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);
            return code == GET_GAME_STATE_RES ? JsonRequestPacketDeserializer.DeserializeGetGameState(str) : null;
        }

        public bool GetPlaceCard(string cardId)
        {
            byte[] req = JsonRequestPacketSerializer.SerializePlayCard(cardId);

            clientStream.Write(req, 0, req.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return false;
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);


            return true;
        }

        public bool GetDrawCard()
        {
            string cardId = "00";
            byte[] req = JsonRequestPacketSerializer.SerializePlayCard(cardId);

            clientStream.Write(req, 0, req.Length);
            int code = GetCodeFromSocket();
            int size = GetSizeFromSocket();
            if (size <= 0)
            {
                return false;
            }

            byte[] buffer = new byte[size];
            int bytesNum = clientStream.Read(buffer, 0, size);
            string str = Encoding.Default.GetString(buffer);


            return true;
        }


        private byte GetCodeFromSocket()
        {
            byte[] buffer = new byte[1];
            int bytesNum = clientStream.Read(buffer, 0, 1);
            return buffer[0];
        }

        private int GetSizeFromSocket()
        {
            byte[] bytes = new byte[4];
            int bytesNum = clientStream.Read(bytes, 0, 4);
            return bytes[3] << 24 | bytes[2] << 16 | bytes[1] << 8 | bytes[0];
        }

    }
}
