using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// This class stores the shared data between thw windows, socket, username and etc
namespace TakiClient.Modules
{
    public class Manager
    {
        private Client client;
        private bool _isThreading;
        private static Manager _instanse;
        private string username;
        int roomId;

        private Manager()
        {
            this.client = new Client();
            this._isThreading = false;
        }

        // Implemenating singelton ( singelton is required since it stores shared data between the windows and if the class
        // will be create each time it will lose the point)
        public static Manager GetManager()
        {
            if (_instanse == null)
            {
                _instanse = new Manager();
            }
            return _instanse;
        }

        public Client getClient()
        {
            return client;
        }

        public bool IsThreading()
        {
            return _isThreading;
        }

        public void SetThreading(bool isThreading)
        {
            _isThreading = isThreading;
        }


        public void SetRoomId(int roomId)
        {
            this.roomId = roomId;
        }

        public int GetRoomId()
        {
            return roomId;
        }

        public void SetUsername(string username)
        {
            this.username = username;
        }

        public string GetUsername()
        {
            return username;
        }

    }
}
