using System;

namespace Laborator02
{
    class Program
    {
        void Palindrom(int n)
        {
            int m = 0, aux = n;
            while (aux != 0)
            {
                m = m * 10 + aux % 10;
                aux /= 10;
            }
            if (n == m)
            {
                Console.WriteLine("Numarul " + n + " este palindrom");
            }
            else
            {
                Console.WriteLine("Numarul " + n + " nu este palindrom");
            }
        }

        void Verif(int n, int[] a)
        {
            bool ok = true;
            for (int i = 0; i < n - 1 && ok; ++i)
            {
                if (a[i] % 2 == a[i + 1] % 2)
                {
                    Console.WriteLine("Nu");
                    ok = false;
                }
            }
            if (ok)
            {
                Console.WriteLine("Da");
            }
        }

        static void Main()
        {
            Program p = new Program();
            int x = Convert.ToInt32(Console.ReadLine());
            p.Palindrom(x);
            int n = Convert.ToInt32(Console.ReadLine());
            int[] a = new int[100];
            for (int i = 0; i < n; ++i)
            {
                a[i] = Convert.ToInt32(Console.ReadLine());
            }
            p.Verif(n, a);
        }
    }
}