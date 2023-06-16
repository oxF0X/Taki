using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows;
using TakiClient.Modules;
using TakiClient.ViewsModels;


namespace TakiClient.ViewsModels
{
    internal class JoinedRoomViewModel : ViewsModelBase
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

        public ICommand LeaveRoomCommand { get; }



        public JoinedRoomViewModel()
        {
            this.clientHandler = Manager.GetManager().getClient();
            LeaveRoomCommand = new ViewModelCommand(ExecuteLeaveRoom);
            //this._users = clientHandler.GetPlayersInRoom(Manager.GetManager().getRoomId());
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


        private void ExecuteLeaveRoom(object obj)
        {
            this.clientHandler.GetLiveRoom();
        }
    }
}
