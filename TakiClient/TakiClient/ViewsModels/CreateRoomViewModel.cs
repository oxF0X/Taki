using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows;
using TakiClient.Modules;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace TakiClient.ViewsModels
{
    public class CreateRoomViewModel : ViewsModelBase
    {
        private int _answerTimeOut;
        private int _maxUsers;
        private string _roomName;

        private Client clientHandler;


        public int AnswerTimeOut
        {
            get { return _answerTimeOut; }
            set
            {
                _answerTimeOut = value;
                OnPropertyChanged(nameof(AnswerTimeOut));
            }
        }


        public int MaxUsers
        {
            get { return _maxUsers; }
            set
            {
                _maxUsers = value;
                OnPropertyChanged(nameof(MaxUsers));
            }
        }

        public String RoomName
        {
            get { return _roomName; }
            set
            {
                _roomName = value;
                OnPropertyChanged(nameof(RoomName));
            }
        }

        public ICommand CreateRoomCommand { get; }



        public CreateRoomViewModel()
        {
            this.clientHandler = Client.GetClient();
            CreateRoomCommand = new ViewModelCommand(ExecuteCreateRooms, CanExecuteCreateRoom);
        }

        private bool CanExecuteCreateRoom(object obj)
        {
            return !(string.IsNullOrWhiteSpace(RoomName) || MaxUsers == 0 || AnswerTimeOut == 0);
        }

        private void ExecuteCreateRooms(object obj)
        {
            this.clientHandler.CreateRoom(_roomName, _maxUsers, _answerTimeOut);
            //throw new NotImplementedException();
        }
    }
}
