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
    public partial class AdminGameJoinView : Window
    {
        private AdminGameJoinViewModel _viewModel;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;

        public AdminGameJoinView(AdminGameJoinViewModel viewModel)
        {
            InitializeComponent();

            _viewModel = viewModel;
            DataContext = _viewModel;

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
                _viewModel.UpdateUsers(_viewModel.UpdateUsers());

                await Task.Delay(5);
            }
        }
    }
}
