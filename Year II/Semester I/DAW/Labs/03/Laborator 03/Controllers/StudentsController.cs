using Microsoft.AspNetCore.Mvc;

namespace Laborator_03.Controllers
{
    public class StudentsController : Controller
    {
        public string Index()
        {
            return "Afisarea tuturor studentilor";
        }

        public string Show(int? id)
        {
            if (id == null)
            {
                return "Nu avem id-ul studentului";
            }
            return "Afisarea studentului cu id-ul " + id.ToString();
        }

        public string Create()
        {
            return "Crearea unui nou student";
        }

        public string Edit(int? id)
        {
            if (id == null)
            {
                return "Nu avem id-ul studentului";
            }
            return "Modificarea studentului cu id-ul " + id.ToString();
        }

        public string Delete(int? id)
        {
            if (id == null)
            {
                return "Nu avem id-ul studentului";
            }
            return "Stergerea studentului cu id-ul " + id.ToString();
        }
    }
}
