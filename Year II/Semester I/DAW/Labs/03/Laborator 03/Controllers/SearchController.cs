using Microsoft.AspNetCore.Mvc;

namespace Laborator_03.Controllers
{
    public class SearchController : Controller
    {
        public string NumarTelefon(string? telef)
        {
            if (telef == null)
            {
                return "Introduceti numarul de telefon";
            }
            if (telef.Length < 10)
            {
                return "Numarul de telefon nu are suficiente cifre";
            }
            return telef;
        }

        public string CNP()
        {
            return "The";
        }
    }
}
