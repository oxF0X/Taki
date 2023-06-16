﻿using System;
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
        public bool _isThreading;

        public int Id 
        { 

            get { return _roomId; }
            set
            {
                _roomId = value;
                OnPropertyChanged(nameof(Id));
            }
        }

        public RoomData[] Rooms
        {
            get { return _rooms; }
            set
            {
                _rooms = value;
                OnPropertyChanged(nameof(Rooms));
            }
        }

        public ICommand JoinRoomCommand { get; set; }

        public JoinRoomViewModel()
        {
            this.clientHandler = Manager.GetManager().getClient();
            JoinRoomCommand = new ViewModelCommand(ExecuteJoinRoom);            
        }

        private void ExecuteJoinRoom(object obj)
        {
            this.clientHandler.GetJoinRoom(Convert.ToInt32(Id.ToString()));
        }

        public RoomData[] GetUpdatedRooms()
        {
            return this.clientHandler.GetRooms();
        }

        public void UpdateRooms(RoomData[] updatedRooms)
        {
            RoomData[] _rooms = this.clientHandler.GetRooms();           
            Rooms = _rooms;
        }


    }
}
