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
using TakiClient.Modules;

namespace TakiClient.ViewsModels
{
    public class TakiGameViewModel : ViewsModelBase
    {
        private ObservableCollection<string> buttonItems = new ObservableCollection<string>();
        private string lastCardPlayed;
        private string currentPlayer;
        private ObservableCollection<string> side1Images = new ObservableCollection<string>();
        private ObservableCollection<string> side2Images = new ObservableCollection<string>();
        private ObservableCollection<string> side3Images = new ObservableCollection<string>();



        public ObservableCollection<string> ButtonItems
        {
            get { return buttonItems; }
            set
            {
                buttonItems = value;
                OnPropertyChanged(nameof(ButtonItems));
            }
        }


        public ObservableCollection<string> Side1Images
        {
            get { return side1Images; }
            set
            {
                side1Images = value;
                OnPropertyChanged(nameof(side1Images));
            }
        }

        public string CurrentPlayer
        {
            get { return currentPlayer; }
            set
            {
                currentPlayer = value;
                OnPropertyChanged(nameof(CurrentPlayer));
            }
        }


        public ObservableCollection<string> Side2Images
        {
            get { return side2Images; }
            set
            {
                side2Images = value;
                OnPropertyChanged(nameof(side2Images));
            }
        }

        public ObservableCollection<string> Side3Images
        {
            get { return side3Images; }
            set
            {
                side3Images = value;
                OnPropertyChanged(nameof(side3Images));
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
        public ICommand DrawCardCommand { get; }


        public TakiGameViewModel()
        {
            //ImageClickedCommand = new RelayCommand<string>(ImageClicked);
            buttonItems = new ObservableCollection<string>();
            lastCardPlayed = "";
            CloseScreenCommand = new ViewModelCommand(ExecutedCloseCommand);
            HideScreenCommand = new ViewModelCommand(ExecutedHideCommand);
            MaximizeOrMinimizeCommand = new ViewModelCommand(ExecutedMaximizeOrMinimizeCommand);
            DrawCardCommand = new ViewModelCommand(ExecuteDrawCardCommand);

        }

        private void ExecuteDrawCardCommand(object obj)
        {
            Manager.GetManager().getClient().GetDrawCard();
        }


        public void setLocationImages(string[] arr)
        {
            buttonItems.Clear();
            foreach (string item in arr)
            {
                buttonItems.Add("../Images/" + item + ".png");
            }
        }

        public void SetSide1(int num)
        {
            side1Images.Clear();
            for (int i = 0; i < num; i++)
            {
                side1Images.Add("../Images/Back.png");
            }
        }


        public void SetSide2(int num)
        {
            side2Images.Clear();
            for(int i = 0; i < num; i++)
            {
                side2Images.Add("../Images/Back.png");
            }
        }

        public void SetSide3(int num)
        {
            side3Images.Clear();
            for (int i = 0; i < num; i++)
            {
                side3Images.Add("../Images/Back.png");
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
