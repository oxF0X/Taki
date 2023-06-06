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
using Client;

namespace TakiClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    public partial class MainWindow : Window
    {
        private Client.Client clientHandler;



        public MainWindow()
        {
            this.clientHandler = new Client.Client();
            InitializeComponent();

            Loaded += MainWindow_Loaded;
        }


        private void textUsername_MouseDown(object sender, MouseButtonEventArgs e)
        {
            txtUsername.Focus();
        }

        private void txtUsername_TextChanged(object sender, TextChangedEventArgs e)
        {
            if(string.IsNullOrEmpty(txtUsername.Text))
            {

               txtUsername.Visibility = Visibility.Collapsed;
                textUsername.Visibility = Visibility.Visible;
            }
            else
            {
                textUsername.Visibility = Visibility.Collapsed;
                txtUsername.Visibility = Visibility.Visible;
            }
        }

        private void textPassword_MouseDown(object sender, MouseButtonEventArgs e)
        {
            txtPassword.Focus();
        }

        private void txtPassword_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (string.IsNullOrEmpty(txtPassword.Text))
            {
                txtPassword.Visibility = Visibility.Collapsed;
                textPassword.Visibility = Visibility.Visible;
            }
            else
            {
                txtPassword.Visibility = Visibility.Visible;
                textPassword.Visibility = Visibility.Collapsed;
            }
        }

        private void SignInButtonClick(object sender, RoutedEventArgs e)
        {
            if(string.IsNullOrEmpty(txtUsername.Text) || string.IsNullOrEmpty(txtPassword.Text))
            {
                return;
            }

            string response = this.clientHandler.GetLogin(txtUsername.Text, txtPassword.Text);
            if(response == "1")
            {
                MessageBox.Show("Logegd In");
            }
            else
            {
                MessageBox.Show(response);
            }
        }

        private void Border_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if(e.ChangedButton == MouseButton.Left)
            {
                this.DragMove();
            }
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            WindowStyle = WindowStyle.None;
            WindowState = WindowState.Maximized;
            AdjustWindowSizeToScreen();
        }

        private void AdjustWindowSizeToScreen()
        {
            // Get the primary screen dimensions
            double screenWidth = SystemParameters.PrimaryScreenWidth;
            double screenHeight = SystemParameters.PrimaryScreenHeight;

            Width = screenWidth;
            Height = screenHeight;
        }


        private void FullScreenButton_Click(object sender, RoutedEventArgs e)
        {
            ToggleFullScreen();
        }

        private void ToggleFullScreen()
        {
            if (WindowStyle == WindowStyle.None) // Window is already in full-screen mode
            {
                WindowStyle = WindowStyle.SingleBorderWindow; // Switch to windowed mode
                WindowState = WindowState.Normal;
            }
            else // Window is currently in windowed mode
            {
                WindowStyle = WindowStyle.None; // Switch to full-screen mode
                WindowState = WindowState.Maximized;
            }
        }

        private void Image_MouseUp(object sender, MouseButtonEventArgs e)
        {
            Application.Current.Shutdown();
        }


    }
}
