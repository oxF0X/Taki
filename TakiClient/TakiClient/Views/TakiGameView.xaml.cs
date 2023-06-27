﻿using System;
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

namespace TakiClient.Views
{
    /// <summary>
    /// Interaction logic for TakiGameView.xaml
    /// </summary>
    public partial class TakiGameView : Window
    {
        private string[][] sideImages;


        private bool isUpdateThreadRunning;
        private Task roomUpdateTask;
        private CancellationTokenSource cancellationTokenSource;
        private TakiGameViewModel viewModel;


        public TakiGameView()
        {
            InitializeComponent();

            this.sideImages = new string[4][];
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

                    int[] cardsCount = gameState.Value.cardsPerPlayer;

                    for (int i = 0; i < sideImages.GetLength(0); i++)
                    {
                        this.sideImages[i] = new string[cardsCount.Length >= i ? cardsCount[i] : 0];

                        for (int j = 0; j < cardsCount[i] && cardsCount.Length >= i; j++)
                        {
                            sideImages[i][j] = "Back";
                        }
                    }
                });
                count++;
                await Task.Delay(1000);
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
            string id = cardId.Substring(10, 2);
            Manager.GetManager().getClient().GetPlaceCard(id);

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
