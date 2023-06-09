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

namespace TakiClient.ViewsModels
{
    public class LoginViewModel : ViewsModelBase
    {
        private string _username;
        private SecureString _password;
        //private string _email;
        private string _error;
        private bool _isViewVisible = true;
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


        public bool IsViewVisible
        {
            get
            {
                return _isViewVisible;
            }

            set
            {
                _isViewVisible = value;
                OnPropertyChanged(nameof(IsViewVisible));
            }
        }


        public ICommand LoginCommand { get; }
        public ICommand ShowPasswordCommand { get; }

        public LoginViewModel()
        {
            this.clientHandler = new Client();
            LoginCommand = new ViewModelCommand(ExecuteLoginCommand, CanExecuteLoginCommand);
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
                IsViewVisible = false;
            }
            else
            {
                Error = result;
            }
        }
    }
}
