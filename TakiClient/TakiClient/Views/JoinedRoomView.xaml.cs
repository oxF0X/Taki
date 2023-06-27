using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using TakiClient.Modules;
using TakiClient.ViewsModels;

namespace TakiClient.Views
{
    public partial class JoinedRoomView : Window
    {
        private JoinedRoomViewModel viewModel;
        private Thread roomUpdateThread;
        private bool isThreadRunning;

        public JoinedRoomView(JoinedRoomViewModel viewModel)
        {
            InitializeComponent();

            WindowStyle = WindowStyle.None;
            WindowState = WindowState.Maximized;

            double screenWidth = SystemParameters.PrimaryScreenWidth;
            double screenHeight = SystemParameters.PrimaryScreenHeight;

            Width = screenWidth;
            Height = screenHeight;

            this.viewModel = viewModel;
            DataContext = viewModel;

            // Create and start the thread for room updates
            Manager.GetManager().SetThreading(true);
            isThreadRunning = true;
            roomUpdateThread = new Thread(RoomUpdateThreadMethod);
            roomUpdateThread.Start();

            Unloaded += JoinRoom_Unloaded;
        }

        private void JoinRoom_Unloaded(object sender, RoutedEventArgs e)
        {
            isThreadRunning = false;
        }

        private void RoomUpdateThreadMethod()
        {
            while (isThreadRunning && Manager.GetManager().IsThreading())
            {
                string[] users = viewModel.UpdateUsers();
                viewModel.UpdateUsers(users);

                Thread.Sleep(5);
            }
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                DragMove();
            }
        }


        private void Border_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                this.DragMove();
            }
        }
    }
}
