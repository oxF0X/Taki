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
using TakiClient.Views;

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
        public ICommand StartGameCommand { get; }



        public AdminGameJoinViewModel()
        {
            this.clientHandler = Manager.GetManager().getClient();
            CloseRoomCommand = new ViewModelCommand(ExecuteCloseRoom);
            StartGameCommand = new ViewModelCommand(ExecuteStartGame);
            //this._users = clientHandler.
            //(Manager.GetManager().getRoomId());
        }

        private void ExecuteStartGame(object obj)
        {
            this.clientHandler.GetStartGame();
            var view = new TakiGameView();
            Window w = Application.Current.MainWindow;
            Application.Current.MainWindow = view;
            view.Show();
            w.Close();
        }

        public string[] UpdateUsers()
        {
            GetRoomsStateResponse? state = this.clientHandler.GetRoomState();
            string[] players = state?.players;
            players[0] += " (admin)";
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
            var view = new MenuView();
            Window w = Application.Current.MainWindow;
            Application.Current.MainWindow = view;
            view.Show();
            w.Close();
        }
    }
}
