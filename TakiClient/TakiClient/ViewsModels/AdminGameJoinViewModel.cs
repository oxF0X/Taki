using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using TakiClient.Modules;

namespace TakiClient.ViewsModels
{
    public  class AdminGameJoinViewModel : ViewsModelBase
    {
        private string[] _users;

        private Client clientHandler;


        public String[] Users
        {
            get { return _users; }
            set
            {
                _users = value;
                OnPropertyChanged(nameof(Users));
            }
        }

        public ICommand CloseRoomCommand { get; }



        public AdminGameJoinViewModel()
        {
            this.clientHandler = Manager.GetManager().getClient();
            CloseRoomCommand = new ViewModelCommand(ExecuteCloseRoom);
            //this._users = clientHandler.
            //(Manager.GetManager().getRoomId());
        }

        public string[] UpdateUsers()
        {
            GetRoomsStateResponse? state = this.clientHandler.GetRoomState();
            string[] players = state?.players;
            return players;
        }

        public void UpdateUsers(string[] arr)
        {
            Users = arr;
            this._users = arr;
        }


        private void ExecuteCloseRoom(object obj)
        {
            this.clientHandler.GetCloseRoom();
        }
    }
}
