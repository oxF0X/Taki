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
using System.Windows.Controls.Primitives;
using Label = System.Windows.Controls.Label;

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
        private Popup popup;


        public TakiGameView()
        {
            InitializeComponent();

            var resourceDict = new ResourceDictionary();
            resourceDict.Source = new Uri("Views/Styles.xaml", UriKind.Relative);
            Application.Current.Resources.MergedDictionaries.Add(resourceDict);


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
                    if (gameState.Value.isProgress == false)
                    {
                        this.ShowPopup();
                        return;
                    }
                    viewModel.setLocationImages(gameState.Value.cards);
                    viewModel.LastCardPlayed = "../Images/" + gameState.Value.currentCard + ".png";
                    viewModel.SetSide1(gameState.Value.cardsPerPlayer[0]);
                    viewModel.SetSide2(gameState.Value.cardsPerPlayer[1]);
                    viewModel.SetSide3(gameState.Value.cardsPerPlayer[2]);
                    viewModel.CurrentPlayer = gameState.Value.currentPlayer;
                });
                count++;
                await Task.Delay(500);
            }
        }

        private void EndGame_Click(object sender, RoutedEventArgs e)
        {
            middleContainer.Children.Remove(this.popup);

            Manager.GetManager().SetThreading(false);
            var view = new MenuView();
            Window w = Application.Current.MainWindow;
            Application.Current.MainWindow = view;
            view.Show();
            w.Close();
        }

        private void ShowPopup()
        {
            // Create the Popup control
            this.popup = new Popup();
            this.popup.Style = (Style)Application.Current.Resources["CustomPopupStyle"];


            // Create a Grid to hold the content of the popup
            Grid grid = new Grid();
            grid.Background = Brushes.White;
            grid.Margin = new Thickness(10);


            // Create a Button control
            Button button = new Button();
            button.Style = (Style)Application.Current.Resources["PopupButtonStyle"];
            button.Height = 300;
            button.Width = 200;
            button.Content = Manager.GetManager().getClient().GetGameResult() + "won, \nreturn to menu";
            button.Margin = new Thickness(10);
            button.Click += EndGame_Click;

            // Add the button to the grid
            grid.Children.Add(button);

            // Set the content of the popup to the grid
            this.popup.Child = grid;

            // Set the position and size of the popup
            this.popup.PlacementTarget = this;
            this.popup.Placement = PlacementMode.Center;
            this.popup.Width = 200;
            this.popup.Height = 200;

            // Open the popup
            this.popup.IsOpen = true;
            middleContainer.Children.Add(popup);
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
                if(middleContainer.Children.Count > 0)
                {
                    return;
                }
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
            if(id[1] == 'T')
            {
                if (middleContainer.Children.Count > 0)
                {
                    return;
                }
                
                if (!Manager.GetManager().getClient().GetPlaceCard(id))
                {
                    return;
                }

                buttons = new Button[1];
                buttons[0] = new Button();
                buttons[0].Style = (Style)Application.Current.Resources["LoginButtonStyle"];
                buttons[0].Width = 100;
                buttons[0].Height = 60;                
                buttons[0].Content = "Finish taki";
                buttons[0].Margin = new Thickness(0, 10, 0, 0);
                buttons[0].Click += Taki_Click;
                middleContainer.Children.Add(buttons[0]);
                System.Windows.Controls.Panel.SetZIndex(buttons[0], 1);
                return;
            }
            Manager.GetManager().getClient().GetPlaceCard(id);

        }

        private void Taki_Click(object sender, RoutedEventArgs e)
        {
            Button button = (Button)sender;

                middleContainer.Children.Remove(buttons[0]);


            Manager.GetManager().getClient().GetPlaceCard("01");
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
