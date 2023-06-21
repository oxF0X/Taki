using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace TakiClient.Views
{
    /// <summary>
    /// Interaction logic for TakiGameView.xaml
    /// </summary>
    public partial class TakiGameView : Window
    {
        public TakiGameView()
        {
            InitializeComponent();
            AddImagesToSides();

        }

        private void AddImagesToSides()
        {
            // Assuming you have an array of image paths for each side
            string[] side1Images = { "../Images/back.png", "../Images/back.png", "../Images/back.png" };
            string[] side2Images = { "../Images/back.png", "../Images/back.png" };
            string[] side3Images = { "../Images/back.png", "../Images/back.png", "../Images/back.png", "../Images/back.png" };
            string[] side4Images = { "../Images/back.png" };

            // Add images to each side
            AddImagesToStackPanel(side1, side1Images);
            AddImagesToStackPanel(side2, side2Images);
            AddImagesToStackPanel(side3, side3Images);
            AddImagesToStackPanel(side4, side4Images);
        }

        private void AddImagesToStackPanel(StackPanel stackPanel, string[] imagePaths)
        {
            foreach (string imagePath in imagePaths)
            {
                Image image = new Image();
                image.Source = new BitmapImage(new Uri(imagePath, UriKind.RelativeOrAbsolute));
                stackPanel.Children.Add(image);
            }
        }
    
}
}
