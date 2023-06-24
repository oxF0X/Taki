using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using System.Text.Json.Serialization;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;


namespace TakiClient.Modules
{

    struct SignupResponse
    {
        public int status { get; set; }
    }
    struct LoginResponse
    {
        public int status { get; set; }
    }
    struct ErrorResponse
    {
        public string message { get; set; }
    }

    public struct RoomData
    {
        public int id { get; set; }
        public int maxPlayers { get; set; }
        public int timePerPlay { get; set; }
        public int isActive { get; set; }
        public string name { get; set; }
    }

    public struct GetRoomsResponse
    {
        public int status { get; set; }
        public RoomData[] rooms { get; set; }
    }

    public struct GetPlayersResponse
    {
        public int status { get; set; }
        public string[] players { get; set; }
    }

    public struct GetRoomsStateResponse
    {
        public int status { get; set; }
        public bool hasGameBegun { get; set; }
        public string[] players { get; set; }
    }


    public struct GetGameStateResponse
    {
        public string[] cards { get; set; }
        public int[] cardsPerPlayer { get; set; }
        public bool hasGameEnd { get; set; }
        public string[] players { get; set; }
        public int status { get; set; }
    }

    class JsonRequestPacketDeserializer
    {
        static public ErrorResponse DeserializeError(string err)
        {
            return JsonSerializer.Deserialize<ErrorResponse>(err);
        }

        static public LoginResponse DeserializeLogIn(string res)
        {
            return JsonSerializer.Deserialize<LoginResponse>(res);
        }

        static public SignupResponse DeserializeSignUp(string res)
        {
            return JsonSerializer.Deserialize<SignupResponse>(res);
        }

        static public GetRoomsResponse DeserializeGetRooms(string res)
        {
            return JsonSerializer.Deserialize<GetRoomsResponse>(res);
        }

        static public GetPlayersResponse DeserializeGetPalyersInRoom(string res)
        {
            return JsonSerializer.Deserialize<GetPlayersResponse>(res);
        }

        static public GetRoomsStateResponse DeserializeGetRoomState(string res)
        {
            return JsonSerializer.Deserialize<GetRoomsStateResponse>(res);
        }

        static public GetGameStateResponse DeserializeGetGameState(string res)
        {
            int x = 0;
            x++;
            return JsonSerializer.Deserialize<GetGameStateResponse>(res);
        }
    }
}
