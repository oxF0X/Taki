using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using TakiClient.Modules;
using TakiClient.ViewsModels;

namespace TakiClient.Views
{
    public partial class JoinRoom : Page
    {
        private JoinRoomViewModel viewModel;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;

        public JoinRoom()
        {
            InitializeComponent();

            viewModel = new JoinRoomViewModel();
            DataContext = viewModel;

            // Create and start the task for room updates
            cancellationTokenSource = new CancellationTokenSource();
            roomUpdateTask = Task.Run(() => RoomUpdateThreadMethod(cancellationTokenSource.Token));

            Unloaded += JoinRoom_Unloaded;
        }

        private void JoinRoom_Unloaded(object sender, RoutedEventArgs e)
        {
            // Stop the task when the page is unloaded
            cancellationTokenSource.Cancel();
        }

        private async Task RoomUpdateThreadMethod(CancellationToken cancellationToken)
        {
            while (!cancellationToken.IsCancellationRequested && IsLoaded && Manager.GetManager().IsThreading())
            {
                RoomData[] updatedRooms = await Task.Run(() => viewModel.GetUpdatedRooms());

                // Update the Rooms property on the UI thread if the page is still loaded
                if (IsLoaded)
                    viewModel.UpdateRooms(updatedRooms);

                await Task.Delay(5);
            }
        }
    }
}
