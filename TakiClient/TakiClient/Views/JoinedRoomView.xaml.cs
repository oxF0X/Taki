using System;
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

        private int _myVariable;
        private JoinedRoomViewModel viewModel;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;

        public event EventHandler MyVariableChanged;

        public int MyVariable
        {
            get { return _myVariable; }
            set
            {
                if (_myVariable != value)
                {
                    _myVariable = value;
                    OnMyVariableChanged(EventArgs.Empty); // Raise the event
                }
            }
        }

        protected virtual void OnMyVariableChanged(EventArgs e)
        {
/*            Manager.GetManager().SetThreading(false);
            var view = new TakiGameView();
            Window w = Application.Current.MainWindow;
            Application.Current.MainWindow = view;
            view.Show();
            w.Close();
            //this.Close();
            //MyVariableChanged?.Invoke(this, e); // Invoke the event handler*/

        }

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
                string[] users = viewModel.UpdateUsers();
                if(users == null)
                {
                    this.MyVariable = 2;
                    return;
                   /* Manager.GetManager().SetThreading(false);
                    var view = new TakiGameView();
                    Window w = Application.Current.MainWindow;
                    Application.Current.MainWindow = view;
                    view.Show();
                    w.Close();*/
                }
                viewModel.UpdateUsers(users);

                await Task.Delay(5);
            }
        }
    }
}
