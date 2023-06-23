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


        public TakiGameView()
        {
            InitializeComponent();
            AddImagesToSides();

            GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();


            isUpdateThreadRunning = true;
            updateThread = new Thread(UpdateCardArrays);
            updateThread.Start();
                
        }

        private void AddImagesToSides()
        {
            // Assuming you have an array of image paths for each side
            side1Images = new string[] { "../Images/back.png", "../Images/back.png", "../Images/back.png" };
            side2Images = new string[] { "../Images/back.png", "../Images/back.png" };
            side3Images = new string[] { "../Images/back.png", "../Images/back.png", "../Images/back.png", "../Images/back.png" };
            side4Images = new string[] { "../Images/back.png" };

            // Add images to each side
            AddImagesToStackPanel(side1, side1Images);
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
                image.Source = new BitmapImage(new Uri(imagePath, UriKind.RelativeOrAbsolute));
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


        private void UpdateCardArrays()
        {
            while (isUpdateThreadRunning)
            {
                // Simulating card array updates with random images
                /*side1Images = GetRandomImageArray(3);
                side2Images = GetRandomImageArray(2);
                side3Images = GetRandomImageArray(4);
                side4Images = GetRandomImageArray(1);*/

                // Update the UI on the main UI thread
                GetGameStateResponse? gameState = Manager.GetManager().getClient().GetGameState();
                Application.Current.Dispatcher.Invoke(() =>
                {
                    ClearStackPanelChildren(side1);
                    ClearStackPanelChildren(side2);
                    ClearStackPanelChildren(side3);
                    ClearStackPanelChildren(side4);

                    AddImagesToStackPanel(side1, side1Images);
                    AddImagesToStackPanel(side2, side2Images);
                    AddImagesToStackPanel(side3, side3Images);
                    AddImagesToStackPanel(side4, side4Images);
                });

                Thread.Sleep(3); // Wait for 2 seconds before the next update
            }
        }


        private void ClearStackPanelChildren(StackPanel stackPanel)
        {
            stackPanel.Children.Clear();
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);

            // Stop the update thread when the window is closed
            isUpdateThreadRunning = false;
            updateThread.Join();
        }

    }
}
