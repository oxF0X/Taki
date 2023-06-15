using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows;
using TakiClient.Modules;

namespace TakiClient.ViewsModels
{

    public class JoinRoomViewModel : ViewsModelBase
    {
        private RoomData[] _rooms;
        private Client clientHandler;
        private string _roomName;
        private int _roomId;

        public RoomData[] Rooms
        {
            get { return _rooms; }
            set
            {
                _rooms = value;
                OnPropertyChanged(nameof(Rooms));
            }
        }

        public ICommand JoinRoomCommand { get; }

        public JoinRoomViewModel()
        {
            this.clientHandler = Client.GetClient();
            JoinRoomCommand = new ViewModelCommand(ExecuteJoinRoom);
            _rooms = this.clientHandler.GetRooms();
        }

        private void ExecuteJoinRoom(object roomId)
        {
            // Handle the join room logic using the provided roomId
        }

        public RoomData[] GetUpdatedRooms()
        {
            return this.clientHandler.GetRooms();
        }

        public void UpdateRooms(RoomData[] updatedRooms)
        {
            Rooms = updatedRooms;
        }


    }
}
