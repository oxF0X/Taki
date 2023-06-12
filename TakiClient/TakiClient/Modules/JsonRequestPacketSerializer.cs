using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace TakiClient.Modules
{
    struct LoginRequest
    {
        public string username { get; set; }
        public string password { get; set; }
    }

    struct SignupRequest
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }
        public string address { get; set; }
        public string birthday { get; set; }
        public string phoneNumber { get; set; }
    }

    class JsonRequestPacketSerializer
    {
        public const int LOGIN_CODE = 10;
        public const int SIGNUP_CODE = 11;

        public static byte[] SerializeLogin(string username, string password)
        {
            LoginRequest request = new LoginRequest()
            {
                username = username,
                password = password
            };

            string jsonString = JsonSerializer.Serialize(request);
            return buildMsg(jsonString, LOGIN_CODE);
        }


        public static  byte[] SerializeSignup(string username, string password, string email, string address, string birthday, string phoneNumber)
        {
            SignupRequest request = new SignupRequest()
            {
                username = username,
                password = password,
                email = email,
                birthday = birthday,
                phoneNumber = phoneNumber,
                address = address
            };

            string jsonString = JsonSerializer.Serialize(request);
            return buildMsg(jsonString, SIGNUP_CODE);
        }

        public static byte[] buildMsg(string json, int code)
        {
            /*            string msg = ((char)code).ToString();
                        int size = json.Length;

                        byte[] sizeBytes = new byte[4];

                        // Store the size in the byte array
                        sizeBytes[0] = (byte)size;
                        sizeBytes[1] = (byte)(size >> 8);
                        sizeBytes[2] = (byte)(size >> 16);
                        sizeBytes[3] = (byte)(size >> 24);

                        // Append the size bytes to the message
                        msg += Encoding.ASCII.GetString(sizeBytes) + json;

                        return msg;*/

            string msg = ((char)code).ToString();
            int size = json.Length;

            byte[] sizeBytes = new byte[4];

            // Store the size in the byte array
            sizeBytes[0] = (byte)size;
            sizeBytes[1] = (byte)(size >> 8);
            sizeBytes[2] = (byte)(size >> 16);
            sizeBytes[3] = (byte)(size >> 24);

            // Concatenate the size bytes and the JSON string
            byte[] messageBytes = Encoding.ASCII.GetBytes(msg);
            byte[] jsonBytes = Encoding.ASCII.GetBytes(json);

            byte[] finalBytes = new byte[messageBytes.Length + sizeBytes.Length + jsonBytes.Length];
            Buffer.BlockCopy(messageBytes, 0, finalBytes, 0, messageBytes.Length);
            Buffer.BlockCopy(sizeBytes, 0, finalBytes, messageBytes.Length, sizeBytes.Length);
            Buffer.BlockCopy(jsonBytes, 0, finalBytes, messageBytes.Length + sizeBytes.Length, jsonBytes.Length);

            return finalBytes;

        }
    }
}
