using System;

public class RomanNumber : ICloneable, IComparable
{
    static char[] roman_number = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
    string Roman;

    static string Digit_10_to_Roman(int N, int position)
    {
        string Resultat = "";
        if (N >= 5 && N < 9)
            Resultat += roman_number[position + 1];
        if (N % 5 <= 3)
            Resultat = Resultat + new string(roman_number[position], N % 5);
        else if (N % 5 == 4)
        {
            Resultat = Resultat + roman_number[position];
            Resultat += roman_number[position + (N + 1) / 5];
        }
        return Resultat;
    }

    static ushort Digit_Roman_to_10(char Z)
    {
        if (Z == roman_number[0])
            return 1;
        if (Z == roman_number[1])
            return 5;
        if (Z == roman_number[2])
            return 10;
        if (Z == roman_number[3])
            return 50;
        if (Z == roman_number[4])
            return 100;
        if (Z == roman_number[5])
            return 500;
        if (Z == roman_number[6])
            return 1000;
        return 0;
    }

    static ushort Roman_to_10(RomanNumber? n1)
    {
        ushort Resultat = 0;
        int i = 0;
        for (; i < n1.Roman.Length - 1; i++)
        {
            if (Digit_Roman_to_10(n1.Roman[i]) < Digit_Roman_to_10(n1.Roman[i + 1]))
            {
                Resultat += (ushort)(Digit_Roman_to_10(n1.Roman[i + 1]) -
                Digit_Roman_to_10(n1.Roman[i]));
                i++;
            }
            else
                Resultat += Digit_Roman_to_10(n1.Roman[i]);
        }
        if (i != n1.Roman.Length)
            Resultat += Digit_Roman_to_10(n1.Roman[i]);
        return Resultat;
    }

    public RomanNumber(ushort N)
    {
        if (N <= 0 || N >= 4000)
        {
            throw new RomanNumberException("Ошибка подай число от 1 до 3999");
        }
        Roman = "";
        int deg = 1000;
        for (int i = 0; i < 4; i++)
        {
            Roman += Digit_10_to_Roman((N % (deg * 10)) / deg, 6 - 2 * i);
            deg /= 10;
        }
    }

    public static RomanNumber Add(RomanNumber? n1, RomanNumber? n2)
    {
        if (n1 == null || n2 == null)
        {
            throw new RomanNumberException(
            "Одно из слагаемых суммы римских чисел неопределенно");
        }
        ushort chislo1 = Roman_to_10(n1);
        ushort chislo2 = Roman_to_10(n2);
        if (chislo1 + chislo2 >= 4000)
            throw new RomanNumberException(
            "Полученная сумма превышает диапозон допустимых значений " +
            (chislo1 + chislo2));
        return new RomanNumber((ushort)(chislo1 + chislo2));
    }

    public static RomanNumber Sub(RomanNumber? n1, RomanNumber? n2)
    {
        if (n1 == null || n2 == null)
        {
            throw new RomanNumberException(
            "Одно из чисел разности римских чисел неопределенно");
        }
        ushort chislo1 = Roman_to_10(n1);
        ushort chislo2 = Roman_to_10(n2);
        if (chislo1 - chislo2 <= 0)
            throw new RomanNumberException(
            "Вычитаемое в разности целых чисел больше или равно уменьшаемого");
        return new RomanNumber((ushort)(chislo1 - chislo2));
    }

    public static RomanNumber Mul(RomanNumber? n1, RomanNumber? n2)
    {
        if (n1 == null || n2 == null)
        {
            throw new RomanNumberException(
            "Один из множителей произведения римских чисел неопределенно");
        }
        ushort chislo1 = Roman_to_10(n1);
        ushort chislo2 = Roman_to_10(n2);
        if (chislo1 * chislo2 >= 4000)
            throw new RomanNumberException(
            "Полученное произведение превышает диапозон допустимых значений " +
            (chislo1 * chislo2));
        return new RomanNumber((ushort)(chislo1 * chislo2));
    }

    public static RomanNumber Div(RomanNumber? n1, RomanNumber? n2)
    {
        if (n1 == null || n2 == null)
        {
            throw new RomanNumberException(
            "Одно из чисел частного римских чисел неопределенно");
        }
        ushort chislo1 = Roman_to_10(n1);
        ushort chislo2 = Roman_to_10(n2);
        if (chislo1 / chislo2 == 0)
            throw new RomanNumberException(
            "Делитель частного римских чисел меньше делимого ");
        if (chislo1 % chislo2 > 0)
            throw new RomanNumberException(
            "Делимое не кратно делимому, а дробных чисел в римской системе счисления нет");
        return new RomanNumber((ushort)(chislo1 / chislo2));
    }

    public object Clone() { return new RomanNumber(Roman_to_10(this)); }

    public int CompareTo(object? obj)
    {
        if (obj is RomanNumber roman)
            return Roman_to_10(this).CompareTo(Roman_to_10(roman));
        else
            throw new ArgumentException("Некорректное значение параметра");
    }

    public override string ToString()
    {
        return Roman + " = " + Roman_to_10(this) + "\n";
    }
}