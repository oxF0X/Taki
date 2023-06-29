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


        private string _username;
        public string Username
        {
            get { return _username; }
            set
            {
                _username = value;
                OnPropertyChanged(nameof(_username));
            }
        }


        public ICommand CloseRoomCommand { get; }
        public ICommand StartGameCommand { get; }
        public ICommand CloseScreenCommand { get; }
        public ICommand HideScreenCommand { get; }
        public ICommand MaximizeOrMinimizeCommand { get; }

        public AdminGameJoinViewModel()
        {
            Username = "You are logged in as " + Manager.GetManager().GetUsername();

            this.clientHandler = Manager.GetManager().getClient();
            CloseRoomCommand = new ViewModelCommand(ExecuteCloseRoom);
            StartGameCommand = new ViewModelCommand(ExecuteStartGame);
            CloseScreenCommand = new ViewModelCommand(ExecutedCloseCommand);
            HideScreenCommand = new ViewModelCommand(ExecutedHideCommand);
            MaximizeOrMinimizeCommand = new ViewModelCommand(ExecutedMaximizeOrMinimizeCommand);
            this._users = new string[1];
        }

        private void ExecuteStartGame(object obj)
        {
            this.clientHandler.GetStartGame();

            Manager.GetManager().SetThreading(false);
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
            if (players.Length > 0)
            {
                players[0] += " (admin)";
            }
            return players;
        }

        public void UpdateUsers(string[] arr)
        {
            Users = arr;
            this._users = arr;
        }

        private void ExecuteCloseRoom(object obj)
        {
            Manager.GetManager().SetThreading(false);
            this.clientHandler.GetCloseRoom();
            var view = new MenuView();
            Window w = Application.Current.MainWindow;
            Application.Current.MainWindow = view;
            view.Show();
            w.Close();
        }


        private void ExecutedMaximizeOrMinimizeCommand(object obj)
        {
            if (Application.Current.MainWindow.WindowState == WindowState.Maximized)
            {
                Application.Current.MainWindow.WindowState = WindowState.Normal;
                Application.Current.MainWindow.Width = 600;
                Application.Current.MainWindow.Height = 500;
            }
            else
            {
                Application.Current.MainWindow.WindowState = WindowState.Maximized;
            }
        }

        private void ExecutedHideCommand(object obj)
        {
            Application.Current.MainWindow.WindowState = WindowState.Minimized;

        }

        private void ExecutedCloseCommand(object obj)
        {
            Application.Current.Shutdown();
        }
    }
}
