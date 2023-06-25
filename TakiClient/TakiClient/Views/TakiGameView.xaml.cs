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
        private string[][] sideImages;


        private Thread updateThread;
        private bool isUpdateThreadRunning;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;


        public TakiGameView()
        {
            InitializeComponent();
            this.sideImages = new string[4][];

            WindowState = WindowState.Maximized;

            WindowStyle = WindowStyle.None;
            WindowState = WindowState.Maximized;

            double screenWidth = SystemParameters.PrimaryScreenWidth;
            double screenHeight = SystemParameters.PrimaryScreenHeight;

            Width = screenWidth;
            Height = screenHeight;
            //AddImagesToSides();

            GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();

            isUpdateThreadRunning = true;
            cancellationTokenSource = new CancellationTokenSource();
            roomUpdateTask = Task.Run(() => UpdateCardArrays(cancellationTokenSource.Token));
        }

        private void AddImagesToStackPanel(StackPanel stackPanel, string[] imagePaths)
        {
            stackPanel.Children.Clear();

            foreach (string imagePath in imagePaths)
            {
                string path = imagePath; 
                Image image = new Image();
                image.Source = new BitmapImage(new Uri("../Images/" + imagePath + ".png", UriKind.RelativeOrAbsolute));
                image.Width = 100;
                image.Height = 150;
                image.Margin = new Thickness(0, 0, 0, 0);

                /*Button imageButton = new Button();
                imageButton.Content = image;
                imageButton.Click += (sender, e) => OnImageClicked(path); */

                stackPanel.Children.Add(image);
            }
           //AttachEventHandlers(stackPanel);
        }

/*        private void AttachEventHandlers(StackPanel stackPanel)
        {
            foreach (Button button in stackPanel.Children.OfType<Button>())
            {
                button.Click += (sender, e) => OnImageClicked(button.Content.ToString());
            }
        }*/

        private void SetCenterImage(string imagePath)
        {
            centerImage.Source = new BitmapImage(new Uri(imagePath, UriKind.RelativeOrAbsolute));
        }


        private async Task UpdateCardArrays(CancellationToken cancellationToken)
        {
            while (isUpdateThreadRunning && !cancellationToken.IsCancellationRequested)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    ClearStackPanelChildren(side1);
                    ClearStackPanelChildren(side2);
                    ClearStackPanelChildren(side3);
                    side3.Children.Clear();
                    ClearStackPanelChildren(side4);

                    GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();
                    int[] cardsCount = gameState.Value.cardsPerPlayer;

                    for (int i = 0; i < sideImages.GetLength(0); i++)
                    {
                        this.sideImages[i] = new string[cardsCount.Length >= i ? cardsCount[i] : 0];          
                        
                        for(int j = 0; j < cardsCount[i] && cardsCount.Length >= i; j++)
                        {
                            sideImages[i][j] = "Back";
                        }
                    }

                    AddImagesToStackPanel(side1, sideImages[0]);
                    AddImagesToStackPanel(side2, sideImages[1]);
                    AddImagesToStackPanel(side3, gameState.Value.cards);
                    AddImagesToStackPanel(side4, sideImages[2]);
                });
                await Task.Delay(3);
            }
        }


        private void ClearStackPanelChildren(StackPanel stackPanel)
        {
            /*foreach (var child in stackPanel.Children)
            {
                stackPanel.Children.Remove(child);
            }*/
            //stackPanel.Children.Clear();
            // Create a copy of the current children collection
            /*            var children = stackPanel.Children.Cast<UIElement>().ToList();

                        // Remove each child element from the stackPanel
                        foreach (var child in children)
                        {
                            stackPanel.Children.Remove(child);
                        }*/
            /*            stackPanel.Dispatcher.Invoke(() =>
                        {
                            stackPanel.Children.Clear();
                        });
            */
            for(int i = stackPanel.Children.Count - 1; i >= 0; i--)
            {
                stackPanel.Children.RemoveAt(i);
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            isUpdateThreadRunning = false;
            updateThread.Join();
        }

        private void OnImageClicked(string imagePath)
        {
            // Do something with the clicked image path
            // For example, pass it as a parameter to another function
            string x = imagePath; 
        }


    }
}
