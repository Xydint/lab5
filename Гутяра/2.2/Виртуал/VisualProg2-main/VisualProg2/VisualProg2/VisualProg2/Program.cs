using System;

class Program
{
    public static void Main(string[]
    args)
    {
        RomanNumber r = new RomanNumber((ushort)3528), r1;
        Console.WriteLine(r);
        r = new RomanNumber((ushort)35);
        r1 = new RomanNumber((ushort)14);
        try
        {
            Console.WriteLine(RomanNumber.Add(r, r1));
            Console.WriteLine(RomanNumber.Sub(r, r1));
            Console.WriteLine(RomanNumber.Mul(r, r1));
            Console.WriteLine(RomanNumber.Div(r, r1));
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
        Random rnd = new Random(DateTime.Now.Millisecond);
        RomanNumber[] R = new RomanNumber[10];
        for (int i = 0; i < 10; i++)
        {
            R[i] = new RomanNumber((ushort)(2 + 2 * rnd.Next(20)));
        }
        Array.Sort(R);
        for (int i = 0; i < 10; i++)
        {
            Console.WriteLine(R[i]);
        }
        Console.ReadLine();
    }
}