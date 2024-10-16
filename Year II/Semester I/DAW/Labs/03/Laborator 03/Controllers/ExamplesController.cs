using Microsoft.AspNetCore.Mvc;

namespace Laborator_03.Controllers
{
    public class ExamplesController : Controller
    {
        public string Concatenare(string str1, string str2)
        {
            return str1 + ' ' + str2;
        }

        public string Produs(int nr1, int? nr2)
        {
            if (nr2 == null)
            {
                return "Introduceti ambele valori";
            }
            return (nr1 * nr2).ToString();
        }

        public string Operatie(int? nr1, int? nr2, string? str)
        {
            if (nr1 == null)
            {
                return "Introduceti parametrul 1";
            }
            if (nr2 == null)
            {
                return "Introduceti parametrul 2";
            }
            if (str == null)
            {
                return "Introduceti parametrul 3";
            }
            int? nr3;
            if (str == "plus")
            {
                nr3 = nr1 + nr2;
            }
            else if (str == "minus")
            {
                nr3 = nr1 - nr2;
            }
            else if (str == "ori")
            {
                nr3 = nr1 * nr2;
            }
            else if (str == "div")
            {
                nr3 = nr1 / nr2;
            }
            else
            {
                return "Introduceti un operator valid";
            }
            return nr3.ToString();
        }
    }
}
