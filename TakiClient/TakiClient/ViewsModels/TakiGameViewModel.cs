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
        private string lastCardPlayed;

        public ObservableCollection<string> ButtonItems
        {
            get { return buttonItems; }
            set
            {
                buttonItems = value;
                OnPropertyChanged(nameof(ButtonItems));
            }
        }

        public string LastCardPlayed
        {
            get { return lastCardPlayed; }
            set
            {
                lastCardPlayed = value;
                OnPropertyChanged(nameof(LastCardPlayed));
            }
        }

        public ICommand CloseScreenCommand { get; }
        public ICommand HideScreenCommand { get; }
        public ICommand MaximizeOrMinimizeCommand { get; }

        public TakiGameViewModel()
        {
            //ImageClickedCommand = new RelayCommand<string>(ImageClicked);
            buttonItems = new ObservableCollection<string>();
            lastCardPlayed = "";
            CloseScreenCommand = new ViewModelCommand(ExecutedCloseCommand);
            HideScreenCommand = new ViewModelCommand(ExecutedHideCommand);
            MaximizeOrMinimizeCommand = new ViewModelCommand(ExecutedMaximizeOrMinimizeCommand);
        }

        public void setLocationImages(string[] arr)
        {
            buttonItems.Clear();
            foreach (string item in arr)
            {
                buttonItems.Add("../Images/" + item + ".png");
            }
        }

        private void ExecutedMaximizeOrMinimizeCommand(object obj)
        {
            if (Application.Current.MainWindow.WindowState == WindowState.Maximized)
            {
                Application.Current.MainWindow.WindowState = WindowState.Normal;
                Application.Current.MainWindow.Width = 600;
                Application.Current.MainWindow.Height = 500;
            }
            else
            {
                Application.Current.MainWindow.WindowState = WindowState.Maximized;
            }
        }

        private void ExecutedHideCommand(object obj)
        {
            Application.Current.MainWindow.WindowState = WindowState.Minimized;

        }

        private void ExecutedCloseCommand(object obj)
        {
            Application.Current.Shutdown();
        }

    }
}
