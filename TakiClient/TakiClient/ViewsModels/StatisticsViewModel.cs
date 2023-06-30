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

namespace TakiClient.ViewsModels
{
    public class StatisticsViewModel : ViewsModelBase
    {
        private string _winsNum;
        private string _gamesNum;
        private string _bestPlayer;
        private string _maxWins;

        public string WinsNum
        {
            get { return _winsNum; }
            set
            {
                _winsNum = value;
                OnPropertyChanged(nameof(WinsNum));
            }
        }

        public string GamesNum
        {
            get { return _gamesNum; }
            set
            {
                _gamesNum = value;
                OnPropertyChanged(nameof(GamesNum));
            }
        }

        public string MaxWins
        {
            get { return _maxWins; }
            set
            {
                _maxWins = value;
                OnPropertyChanged(nameof(MaxWins));
            }
        }


        public string BestPlayer
        {
            get { return _bestPlayer; }
            set
            {
                _bestPlayer = value;
                OnPropertyChanged(nameof(BestPlayer));
            }
        }


        public StatisticsViewModel()
        {
            string[] info = Manager.GetManager().getClient().GetUsersStats();
            _winsNum = info[2];
            _gamesNum = info[1];

            info = Manager.GetManager().getClient().GetBestPlayer();
            _bestPlayer = info[0];
            _maxWins = info[1];
        }
    }
}
