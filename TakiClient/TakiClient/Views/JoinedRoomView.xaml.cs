using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using TakiClient.Modules;
using TakiClient.ViewsModels;

namespace TakiClient.Views
{
    public partial class JoinedRoomView : Window
    {
        private JoinedRoomViewModel viewModel;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;

        public JoinedRoomView()
        {
            InitializeComponent();

            viewModel = new JoinedRoomViewModel();
            DataContext = viewModel;

            // Create and start the task for room updates
            Manager.GetManager().SetThreading(true);
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
            while (!cancellationToken.IsCancellationRequested && Manager.GetManager().IsThreading())
            {
                //string[] updatedRooms = await Task.Run(() => viewModel.UpdateUsers());

                // Update the Rooms property on the UI thread if the page is still loaded

                viewModel.UpdateUsers(viewModel.UpdateUsers());

                await Task.Delay(5);
            }
        }
    }
}
