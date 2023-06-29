using System;
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

namespace TakiClient.ViewsModels
{
    public class LoginViewModel : ViewsModelBase
    {
        private string _username;
        private SecureString _password;
        private string _error;
        private Client clientHandler;


        public string Username
        {
            get
            {
                return _username;
            }

            set
            {
                _username = value;
                OnPropertyChanged(nameof(Username));
            }
        }

        public SecureString Password
        {
            get
            {
                return _password;
            }

            set
            {
                _password = value;
                OnPropertyChanged(nameof(Password));
            }
        }

        public string Error
        {
            get
            {
                return _error;
            }

            set
            {
                _error = value;
                OnPropertyChanged(nameof(Error));
            }
        }


        public ICommand LoginCommand { get; }
        public ICommand CloseScreenCommand { get; }
        public ICommand HideScreenCommand { get; }
        public ICommand MaximizeOrMinimizeCommand { get; }
        public ICommand SignupCommand { get; }
        

        public LoginViewModel()
        {
            this.clientHandler = Manager.GetManager().getClient();
            LoginCommand = new ViewModelCommand(ExecuteLoginCommand, CanExecuteLoginCommand);
            CloseScreenCommand = new ViewModelCommand(ExecutedCloseCommand);
            HideScreenCommand = new ViewModelCommand(ExecutedHideCommand);
            MaximizeOrMinimizeCommand = new ViewModelCommand(ExecutedMaximizeOrMinimizeCommand);
            SignupCommand = new ViewModelCommand(ExecutedSignupCommand);
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

        private bool CanExecuteLoginCommand(object obj)
        {
            return !(string.IsNullOrWhiteSpace(Username) || Password == null);
        }

        private void ExecuteLoginCommand(object obj)
        {
            string password = new System.Net.NetworkCredential(string.Empty, Password).Password;
            string result = clientHandler.GetLogin(Username, password);
            if(result == "1")
            {
                Manager.GetManager().SetUsername(_username);
                var menuView = new MenuView();

                Window w = Application.Current.MainWindow;
                Application.Current.MainWindow = menuView;
                menuView.Show();
                w.Close();
            }
            else
            {
                Error = result;
            }
        }
    }
}
