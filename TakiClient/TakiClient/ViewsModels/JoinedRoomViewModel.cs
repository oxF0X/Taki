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
        private readonly object usersLock = new object();

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
        public ICommand CloseScreenCommand { get; }
        public ICommand HideScreenCommand { get; }
        public ICommand MaximizeOrMinimizeCommand { get; }

        public JoinedRoomViewModel()
        {
            CloseScreenCommand = new ViewModelCommand(ExecutedCloseCommand);
            HideScreenCommand = new ViewModelCommand(ExecutedHideCommand);
            MaximizeOrMinimizeCommand = new ViewModelCommand(ExecutedMaximizeOrMinimizeCommand);
            this.clientHandler = Manager.GetManager().getClient();
            LeaveRoomCommand = new ViewModelCommand(ExecuteLeaveRoom);
            this._users = new string[1];
        }

        public string[] UpdateUsers()
        {
            GetRoomsStateResponse? state = this.clientHandler.GetRoomState();

            if (state == null)
            {
                Manager.GetManager().SetThreading(false);
                Application.Current.Dispatcher.Invoke(() =>
                {
                    var view = new TakiGameView();
                    Window w = Application.Current.MainWindow;
                    Application.Current.MainWindow = view;
                    view.Show();
                    w.Close();
                });
                return null;
            }
            string[] players = state?.players;
            players[0] += " (admin)";
            return players;
        }

        public void UpdateUsers(string[] arr)
        {
            lock (usersLock)
            {
                Users = arr;
                this._users = arr;
            }
        }

        private void ExecuteLeaveRoom(object obj)
        {
            Manager.GetManager().SetThreading(false);
            this.clientHandler.GetLeaveRoom();
            Application.Current.Dispatcher.Invoke(() =>
            {
                var view = new MenuView();
                Window w = Application.Current.MainWindow;
                Application.Current.MainWindow = view;
                view.Show();
                w.Close();
            });
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
