﻿using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using TakiClient.ViewsModels;
using TakiClient.Views;
using TakiClient.Modules;

namespace TakiClient
{
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            var loginView = new LoginView();
            loginView.Show();
        }

    }
}
