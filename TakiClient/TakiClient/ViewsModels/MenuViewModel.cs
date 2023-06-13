﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using TakiClient.Modules;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using TakiClient.Views;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace TakiClient.ViewsModels
{
    public class MenuViewModel : ViewsModelBase
    {
        private string _username;
        private SecureString _password;
        private string _error;
        private Client clientHandler;
        private string _selectedPage;


        public string SelectedPage
        {
            get { return _selectedPage; }
            set
            {
                _selectedPage = value;
                OnPropertyChanged(nameof(SelectedPage));
            }
        }



        public ICommand StatisticsCommand { get; }
        public ICommand GetRoomsCommand { get; }
        public ICommand HideScreenCommand { get; }
        public ICommand MaximizeOrMinimizeCommand { get; }
        public ICommand SignupCommand { get; }
        public ICommand CloseScreenCommand { get; }



        public MenuViewModel()
        {
            this.clientHandler = Client.GetClient();
            StatisticsCommand = new ViewModelCommand(ExecuteShowStatistics);
            GetRoomsCommand = new ViewModelCommand(ExecuteShowRooms);
            CloseScreenCommand = new ViewModelCommand(ExecutedCloseCommand);
            HideScreenCommand = new ViewModelCommand(ExecutedHideCommand);
            MaximizeOrMinimizeCommand = new ViewModelCommand(ExecutedMaximizeOrMinimizeCommand);
        }



        private void ExecutedSignupCommand(object obj)
        {
            var registerView = new RegisterView();
            Window w = Application.Current.MainWindow;
            Application.Current.MainWindow = registerView;
            registerView.Show();
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

        private void ExecuteShowStatistics(object obj)
        {
            SelectedPage = "StatisticsPage.xaml";

        }

        private void ExecuteShowRooms(object obj)
        {
            throw new NotImplementedException();
        }
    }
}
