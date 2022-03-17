using System;

public class RomanNumberException : Exception
{
    public RomanNumberException(string txt) : base(txt) { }
    public override string ToString()
    {
        string Resultat = Message;
        return Resultat;
    }
}
