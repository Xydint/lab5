using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Avalonia.Interactivity;
using AvaloniaApplication5.ViewModels;
using System.IO;

namespace AvaloniaApplication5.Views
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
#if DEBUG
            this.AttachDevTools();
#endif

            this.FindControl<Button>("openFile").Click += async delegate
            {
                var taskGetPath = new OpenFileDialog()
                {
                    Title = "Open File",
                    Filters = null
                }.ShowAsync((Window)this.VisualRoot);

                string[]? pathToFile = await taskGetPath;
                var contex = this.DataContext as MainWindowViewModel;
                if (pathToFile != null)
                {
                    StreamReader reader = new StreamReader(string.Join(@"\", pathToFile));
                    contex.Text = reader.ReadToEnd();
                }
            };
            this.FindControl<Button>("saveFile").Click += async delegate
            {
                var taskGetPath = new OpenFileDialog()
                {
                    Title = "Save File",
                    Filters = null
                }.ShowAsync((Window)this.VisualRoot);

                string[]? pathToFile = await taskGetPath;
                var contex = this.DataContext as MainWindowViewModel;
                if (pathToFile != null)
                {
                    using (StreamWriter writer = new StreamWriter(string.Join(@"\", pathToFile), false))
                    {
                        await writer.WriteLineAsync(contex.RegularResult);
                    }

                }
            };
        }

        private void InitializeComponent()
        {
            AvaloniaXamlLoader.Load(this);
        }

        private void MyClickEventHandler(object sender, RoutedEventArgs e)
        {
            var v = new RegexWindow();
            v.OkNotify += delegate (string str)
            {
                var contex = this.DataContext as MainWindowViewModel;
                contex.Pattern = str;
                contex.RegularResult = contex.FindRegular();

            };
            v.Show((Window)this.VisualRoot);
        }

    }
}