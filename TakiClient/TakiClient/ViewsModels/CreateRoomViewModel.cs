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
using TakiClient.Views;

namespace TakiClient.ViewsModels
{
    public class CreateRoomViewModel : ViewsModelBase
    {
        private string _maxUsers;
        private string _roomName;
        private Client clientHandler;

        public string MaxUsers
        {
            get { return _maxUsers; }
            set
            {
                _maxUsers = value;
                OnPropertyChanged(nameof(MaxUsers));
            }
        }

        public string RoomName
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
            this.clientHandler = Manager.GetManager().getClient();
            CreateRoomCommand = new ViewModelCommand(ExecuteCreateRoom, CanExecuteCreateRoom);
        }

        private bool CanExecuteCreateRoom(object obj)
        {
            return !(string.IsNullOrWhiteSpace(RoomName) || string.IsNullOrWhiteSpace(MaxUsers));
        }

        private void ExecuteCreateRoom(object obj)
        {
                int maxUsersValue = (int)(_maxUsers[_maxUsers.Length - 1]) - 48;
                this.clientHandler.CreateRoom(_roomName, maxUsersValue, 3) ;
                var viewModel = new AdminGameJoinViewModel();
                var view = new AdminGameJoinView(viewModel);
                Window w = Application.Current.MainWindow;
                Application.Current.MainWindow = view;
                view.Show();
                w.Close();
            
        }
    }
}
