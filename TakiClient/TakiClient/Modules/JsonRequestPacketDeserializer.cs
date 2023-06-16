using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using System.Text.Json.Serialization;


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

    struct GetRoomsResponse
    {
        public int status { get; set; }
        public RoomData[] rooms { get; set; }
    }

    struct GetPlayersResponse
    {
        public int status { get; set; }
        public string[] players { get; set; }
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
    }
}
