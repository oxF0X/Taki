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
    public class RegisterViewModel : ViewsModelBase
    {
        private string _username;
        private SecureString _password;
        private string _email;
        private string _phoneNumber;
        private string _address;
        private string _birthDay;
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

        public string Email
        {
            get
            {
                return _email;
            }

            set
            {
                _email = value;
                OnPropertyChanged(nameof(Email));
            }
        }

        public string Address
        {
            get
            {
                return _address;
            }

            set
            {
                _address = value;
                OnPropertyChanged(nameof(Address));
            }
        }

        public string PhoneNumber
        {
            get
            {
                return _phoneNumber;
            }

            set
            {
                _phoneNumber = value;
                OnPropertyChanged(nameof(PhoneNumber));
            }
        }

        public string Birthday
        {
            get
            {
                return _birthDay;
            }

            set
            {
                _birthDay = value;
                OnPropertyChanged(nameof(Birthday));
            }
        }




        public ICommand RegisterCommand { get; }
        public ICommand CloseScreenCommand { get; }
        public ICommand HideScreenCommand { get; }
        public ICommand MaximizeOrMinimizeCommand { get; }
        public ICommand SigninCommand { get; }


        public RegisterViewModel()
        {
            this.clientHandler = Client.GetClient();
            RegisterCommand = new ViewModelCommand(ExecuteRegisterCommand, CanExecuteRegisterCommand);
            CloseScreenCommand = new ViewModelCommand(ExecutedCloseCommand);
            HideScreenCommand = new ViewModelCommand(ExecutedHideCommand);
            MaximizeOrMinimizeCommand = new ViewModelCommand(ExecutedMaximizeOrMinimizeCommand);
            SigninCommand = new ViewModelCommand(ExecutedSigninCommand);
        }

        private void ExecutedSigninCommand(object obj)
        {
            /* var loginView = new LoginView();
             loginView.Show();
             Application.Current.MainWindow.Close(); // Close the current window
             */

            /*            var windowsToClose = Application.Current.Windows.OfType<RegisterView>().ToList();
                        foreach (var window in windowsToClose)
                        {
                            window.Close();
                        }*/

            var loginView = new LoginView();
            Window w = Application.Current.MainWindow;
            Application.Current.MainWindow = loginView;
            loginView.Show();
            w.Close();

        }

        private void ExecutedMaximizeOrMinimizeCommand(object obj)
        {
            /*            foreach (Window window in Application.Current.Windows)
                        {
                            if (window.WindowState == WindowState.Maximized)
                            {
                                window.WindowState = WindowState.Normal;
                                window.Width = 600;
                                window.Height = 500;
                            }
                            else
                            {
                                window.WindowState = WindowState.Maximized;
                            }
                        }*/
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
            /*            foreach (Window window in Application.Current.Windows)
                        {
                            window.WindowState = WindowState.Minimized;
                        }*/

            Application.Current.MainWindow.WindowState = WindowState.Minimized;
        }

        private void ExecutedCloseCommand(object obj)
        {
            Application.Current.Shutdown();
        }

        private bool CanExecuteRegisterCommand(object obj)
        {
            return !(string.IsNullOrWhiteSpace(Username) || Password == null || string.IsNullOrWhiteSpace(Email) || string.IsNullOrWhiteSpace(Address) ||
                string.IsNullOrWhiteSpace(Birthday) || string.IsNullOrWhiteSpace(PhoneNumber));
        }

        private void ExecuteRegisterCommand(object obj)
        {
            string password = new System.Net.NetworkCredential(string.Empty, Password).Password;
            string result = clientHandler.GetLogin(Username, password);
            if (result == "1")
            {
                var mainView = new MenuView();
                mainView.Show();
                Application.Current.MainWindow.Close();
            }
            else
            {
                Error = result;
            }
        }
    }
}
