using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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
using TakiClient.Modules;
using TakiClient.ViewsModels;
using System.Threading;
using System.Windows.Controls;

namespace TakiClient.Views
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private JoinRoomViewModel viewModel;
        private Thread roomUpdateThread;
        private bool isThreadRunning;

        public JoinRoom()
        {
            InitializeComponent();

            viewModel = new JoinRoomViewModel();
            DataContext = viewModel;

            // Create and start the thread for room updates
            isThreadRunning = true;
            roomUpdateThread = new Thread(RoomUpdateThreadMethod);
            roomUpdateThread.Start();


            Unloaded += JoinRoom_Unloaded;
        }


        private void JoinRoom_Unloaded(object sender, System.Windows.RoutedEventArgs e)
        {
            // Stop the thread when the page is unloaded
            isThreadRunning = false;
            roomUpdateThread.Join();
        }

        private void RoomUpdateThreadMethod()
        {
            while (isThreadRunning)
            {
                // Get the updated rooms from the client handler
                RoomData[] updatedRooms = viewModel.GetUpdatedRooms();

                // Update the Rooms property on the UI thread
                Dispatcher.Invoke(() => viewModel.UpdateRooms(updatedRooms));

                // Sleep for a certain duration before updating again
                Thread.Sleep(5);
            }
        }
    }
}
