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

        public ICommand CreateRoomCommand { get; }



        public JoinedRoomViewModel()
        {
            this.clientHandler = Manager.GetManager().getClient();
            CreateRoomCommand = new ViewModelCommand(ExecuteCreateRooms, CanExecuteCreateRoom);
            //this._users = clientHandler.GetPlayersInRoom(Manager.GetManager().getRoomId());
        }

        private bool CanExecuteCreateRoom(object obj)
        {
            return true;
           // return !(string.IsNullOrWhiteSpace(RoomName) || MaxUsers == 0 || AnswerTimeOut == 0);
        }

        private void ExecuteCreateRooms(object obj)
        {
           // this.clientHandler.CreateRoom(_roomName, _maxUsers, _answerTimeOut);
            //throw new NotImplementedException();
        }
    }
}
