using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace TakiClient.Modules
{
    class LoginRequest
    {
        public string username { get; set; }
        public string password { get; set; }
    }

    class JsonRequestPacketSerializer
    {
        public const int LOGIN_CODE = 10;

        public static string SerializeLogin(string username, string password)
        {
            LoginRequest request = new LoginRequest()
            {
                username = username,
                password = password
            };

            string jsonString = JsonSerializer.Serialize(request);
            string msg = ((char)LOGIN_CODE).ToString();
            int size = jsonString.Length;

            byte[] sizeBytes = new byte[4];

            // Store the size in the byte array
            sizeBytes[0] = (byte)size;
            sizeBytes[1] = (byte)(size >> 8);
            sizeBytes[2] = (byte)(size >> 16);
            sizeBytes[3] = (byte)(size >> 24);

            // Append the size bytes to the message
            msg += Encoding.ASCII.GetString(sizeBytes) + jsonString;

            return msg;
        }
    }
}
