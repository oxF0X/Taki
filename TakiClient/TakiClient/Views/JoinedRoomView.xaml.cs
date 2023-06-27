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
using System.Windows.Shapes;
using TakiClient.Modules;
using TakiClient.ViewsModels;

namespace TakiClient.Views
{
    public partial class JoinedRoomView : Window
    {
        private JoinedRoomViewModel viewModel;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;

        public JoinedRoomView(JoinedRoomViewModel viewModel)
        {
            InitializeComponent();

            this.viewModel = viewModel;
            DataContext = viewModel;

            // Create and start the task for room updates
            Manager.GetManager().SetThreading(true);
            cancellationTokenSource = new CancellationTokenSource();
            roomUpdateTask = Task.Run(() => RoomUpdateThreadMethod(cancellationTokenSource.Token));

            Unloaded += JoinRoom_Unloaded;
        }

        private void JoinRoom_Unloaded(object sender, RoutedEventArgs e)
        {
            cancellationTokenSource.Cancel();
        }

        private async Task RoomUpdateThreadMethod(CancellationToken cancellationToken)
        {
            while (!cancellationToken.IsCancellationRequested && Manager.GetManager().IsThreading())
            {        
                string[] users = viewModel.UpdateUsers();
                if(users == null)
                {
                    return;
                }
                viewModel.UpdateUsers(users);

                await Task.Delay(5);
            }
        }
    }
}
