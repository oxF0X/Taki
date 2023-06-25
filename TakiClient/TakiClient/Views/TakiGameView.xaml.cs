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
    /// <summary>
    /// Interaction logic for TakiGameView.xaml
    /// </summary>
    public partial class TakiGameView : Window
    {
        private string[] side1Images;
        private string[] side2Images;
        private string[] side3Images;
        private string[] side4Images;

        private Thread updateThread;
        private bool isUpdateThreadRunning;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;


        public TakiGameView()
        {
            InitializeComponent();
            //AddImagesToSides();

            GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();

            isUpdateThreadRunning = true;
            cancellationTokenSource = new CancellationTokenSource();
            roomUpdateTask = Task.Run(() => UpdateCardArrays(cancellationTokenSource.Token));
        }

        private void AddImagesToSides()
        {
            // Assuming you have an array of image paths for each side
            side1Images = new string[] { "../Images/back.png", "../Images/back.png", "../Images/back.png" };
            side2Images = new string[] { "../Images/back.png", "../Images/back.png" };
            side3Images = new string[] { "../Images/back.png", "../Images/back.png", "../Images/back.png", "../Images/back.png" };
            side4Images = new string[] { "../Images/back.png" };

            // Add images to each side
            AddImagesToStackPanel(side1, Manager.GetManager().getClient().GetGameState().Value.cards);
            AddImagesToStackPanel(side2, side2Images);
            AddImagesToStackPanel(side3, side3Images);
            AddImagesToStackPanel(side4, side4Images);

            this.SetCenterImage("../Images/back.png");

        }

        private void AddImagesToStackPanel(StackPanel stackPanel, string[] imagePaths)
        {
            foreach (string imagePath in imagePaths)
            {
                Image image = new Image();
                image.Source = new BitmapImage(new Uri("../Images/" + imagePath + ".png", UriKind.RelativeOrAbsolute));//imagePath, UriKind.RelativeOrAbsolute));
                image.Width = 100; // Set the desired width
                image.Height = 100; // Set the desired height
                //RotateTransform rotateTransform = new RotateTransform(90);
                //image.RenderTransform = rotateTransform;
                stackPanel.Children.Add(image);
            }
        }

        private void SetCenterImage(string imagePath)
        {
            centerImage.Source = new BitmapImage(new Uri(imagePath, UriKind.RelativeOrAbsolute));
        }


        private async Task UpdateCardArrays(CancellationToken cancellationToken)
        {
            while (isUpdateThreadRunning && !cancellationToken.IsCancellationRequested)
            {
                GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();
                string[] arr = gameState?.cards;
                Application.Current.Dispatcher.Invoke(() =>
                {
                    ClearStackPanelChildren(side1);
                    ClearStackPanelChildren(side2);
                    ClearStackPanelChildren(side3);
                    ClearStackPanelChildren(side4);

                    GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();
                    int[] cardsCount = gameState.Value.cardsPerPlayer;

                    side1Images = new string[cardsCount[0];
                    AddImagesToStackPanel(side1, side1Images);
                    AddImagesToStackPanel(side2, side2Images);
                    AddImagesToStackPanel(side3, side3Images);
                    AddImagesToStackPanel(side4, Manager.GetManager().getClient().GetGameState().Value.cards);
                });
                await Task.Delay(5);
            }
        }


        private void ClearStackPanelChildren(StackPanel stackPanel)
        {
            stackPanel.Children.Clear();
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            isUpdateThreadRunning = false;
            updateThread.Join();
        }

    }
}
