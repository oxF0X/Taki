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
    }
}
