using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows;
using TakiClient.Modules;
using TakiClient.ViewsModels;
using TakiClient.Views;
using System.Threading;
using System.ComponentModel;
using System.Windows.Controls;
using System.Collections.ObjectModel;
using System.Windows.Forms;
using Button = System.Windows.Controls.Button;
using Application = System.Windows.Application;
using System.Windows.Media.Imaging;
using System.Windows.Media;
using System.IO;
using System.Net.Http;

namespace TakiClient.Views
{
    /// <summary>
    /// Interaction logic for TakiGameView.xaml
    /// </summary>
    public partial class TakiGameView : Window
    {
        private string[][] sideImages;

        private Button[] buttons;
        private bool isUpdateThreadRunning;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;
        private TakiGameViewModel viewModel;


        public TakiGameView()
        {
            InitializeComponent();

            this.sideImages = new string[3][];
            viewModel = new TakiGameViewModel();
            DataContext = viewModel;

            WindowState = WindowState.Maximized;

            WindowStyle = WindowStyle.None;
            WindowState = WindowState.Maximized;

            double screenWidth = SystemParameters.PrimaryScreenWidth;
            double screenHeight = SystemParameters.PrimaryScreenHeight;

            Width = screenWidth;
            Height = screenHeight;


            GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();

            isUpdateThreadRunning = true;
            cancellationTokenSource = new CancellationTokenSource();
            roomUpdateTask = Task.Run(() => UpdateCardArrays(cancellationTokenSource.Token));
        }


        private async Task UpdateCardArrays(CancellationToken cancellationToken)
        {
            int count = 0;
            while (isUpdateThreadRunning && !cancellationToken.IsCancellationRequested)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();
                    viewModel.setLocationImages(gameState.Value.cards);
                    viewModel.LastCardPlayed = "../Images/" + gameState.Value.currentCard + ".png";
                    viewModel.SetSide1(gameState.Value.cardsPerPlayer[0]);
                    viewModel.SetSide2(gameState.Value.cardsPerPlayer[1]);
                    viewModel.SetSide3(gameState.Value.cardsPerPlayer[2]);
                });
                count++;
                await Task.Delay(500);
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            isUpdateThreadRunning = false;
            cancellationTokenSource.Cancel();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Button button = (Button)sender;
            string cardId = button.CommandParameter.ToString(); // Access the button content from the command parameter

            string[] colors = { "RC", "BC", "GC", "YC" };
            string id = cardId.Substring(10, 2);
            if (id[1] == 'C')
            {
                buttons = new Button[4];

                for (int i = 0; i < 4; i++)
                {
                    buttons[i] = new Button();
                    buttons[i].Width = 60;
                    buttons[i].Height = 60;
                    buttons[i].Margin = new Thickness(0, 10, 0, 0);
                    buttons[i].Tag = colors[i];
                    buttons[i].Click += ChangeColor_Click;
                    ImageBrush imageBrush = new ImageBrush();
                    imageBrush.ImageSource = new BitmapImage(new Uri(Path.GetFullPath("../../../Images/" + colors[i] + ".png"), UriKind.RelativeOrAbsolute));
                    buttons[i].Background = imageBrush;
                    middleContainer.Children.Add(buttons[i]);
                    System.Windows.Controls.Panel.SetZIndex(buttons[i], 1);
                }
                return;
            }            
            Manager.GetManager().getClient().GetPlaceCard(id);

        }


        private void ChangeColor_Click(object sender, RoutedEventArgs e)
        {
            Button button = (Button)sender;
            string cardId = button.Tag.ToString();
            for (int i = 0; i < this.buttons.Length; i++)
            {
                middleContainer.Children.Remove(buttons[i]);
            }

            Manager.GetManager().getClient().GetPlaceCard(cardId);

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
