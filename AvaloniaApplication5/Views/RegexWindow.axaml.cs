using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;

namespace AvaloniaApplication5.Views
{
    public partial class RegexWindow : Window
    {
        public delegate void OkHandler(string message);
        public event OkHandler? OkNotify;
        public RegexWindow()
        {

            InitializeComponent();
#if DEBUG
            this.AttachDevTools();
#endif

            this.FindControl<Button>("ok").Click += async delegate
            {
                OkNotify(this.Find<TextBox>("inputRegex").Text);
                Close();

            };
            this.FindControl<Button>("cancel").Click += delegate
            {
                Close();
            };
        }

        private void InitializeComponent()
        {
            AvaloniaXamlLoader.Load(this);
        }
    }
}
