public class HW1
{
    public static long QueueTime(int[] customers, int n)
    {
        int[] Kass = new int[n];
        for (int i = 0; i < n; i++)
        {
            Kass[i] = 0;
        }
        int ObshVrem = 0;
        int KolLud = customers.Length;
        int OstLudOnKass;
        bool MasTrue = true;
        while (MasTrue)
        {
            for (int i = 0; i < n; i++)
            {
                if (Kass[i] == 0)
                {
                    if (KolLud > 0)
                    {
                        Kass[i] = customers[(customers.Length - KolLud)];
                        KolLud--;
                    }
                }

            }

            for (int i = 0; i < n; i++)
            {
                if (Kass[i] > 0)
                {
                    Kass[i]--;
                }
            }
            ObshVrem++;

            OstLudOnKass = 0;

            for (int i = 0; i < n; i++)
            {
                OstLudOnKass = OstLudOnKass + Kass[i];
            }

            if (OstLudOnKass == 0 && KolLud == 0)
            {
                MasTrue = false;
            }


        }

        return ObshVrem;
    }
}


class Program
{
    static void Main(string[] args)
    {
        long TimeKass;
        TimeKass = HW1.QueueTime(new int[] { 5, 3, 4 }, 1);
        Console.WriteLine("Результат 1 теста: " + TimeKass);
        TimeKass = HW1.QueueTime(new int[] { 10, 2, 3, 3 }, 2);
        Console.WriteLine("Результат 2 теста: " + TimeKass);
        TimeKass = HW1.QueueTime(new int[] { 2, 3, 10 }, 2);
        Console.WriteLine("Результат 3 теста: " + TimeKass);
        Console.Read();
    }
}



