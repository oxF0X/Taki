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
    public class JoinedRoomViewModel : ViewsModelBase
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
            this._users = new string[1];
        }

        public string[] UpdateUsers()
        {
           GetRoomsStateResponse? state = this.clientHandler.GetRoomState();
           
            if(state == null)
            {
                Manager.GetManager().SetThreading(false);
                var view = new TakiGameView();
                Window w = Application.Current.MainWindow;
                Application.Current.MainWindow = view;
                view.Show();
                w.Close();
                return null;
            }
            string[] players = state?.players;
            players[0] += " (admin)";
            return players;
        }

        public void UpdateUsers(string[] arr)
        {
            Users = arr;
            this._users = arr;
        }


        private void ExecuteLeaveRoom(object obj)
        {
            Manager.GetManager().SetThreading(false);
            this.clientHandler.GetLeaveRoom();
            var view = new MenuView();
            Window w = Application.Current.MainWindow;
            Application.Current.MainWindow = view;
            view.Show();
            w.Close();
        }
    }
}
