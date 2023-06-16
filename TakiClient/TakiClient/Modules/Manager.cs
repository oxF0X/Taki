using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TakiClient.Modules
{
    public class Manager
    {
        private Client client;
        private bool _isThreading;
        private static Manager _instanse;

        private Manager()
        {
            this.client = new Client();
            this._isThreading = false;
        }

        public static Manager GetManager()
        {
            if(_instanse == null)
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
        { _isThreading = isThreading; }


    }
}
