using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows;
using TakiClient.ViewsModels;
using Microsoft.VisualBasic.ApplicationServices;
using System.ComponentModel;

namespace TakiClient.ViewsModels
{
    public class TakiGameViewModel : ViewsModelBase
    {
        private ObservableCollection<string> buttonItems = new ObservableCollection<string>();

        public ObservableCollection<string> ButtonItems
        {
            get { return buttonItems; }
            set
            {
                buttonItems = value;
                OnPropertyChanged(nameof(ButtonItems));
            }
        }


        public TakiGameViewModel()
        {
            //ImageClickedCommand = new RelayCommand<string>(ImageClicked);
            buttonItems = new ObservableCollection<string>();
        }

        public void setLocationImages(string[] arr)
        {
            buttonItems.Clear();
            foreach (string item in arr)
            {
                buttonItems.Add("../Images/" + item + ".png");
            }
        }

        private void ImageClicked(string location)
        {
            // Handle the image clicked event here
            MessageBox.Show($"Image clicked: {location}");
        }

    }
}
