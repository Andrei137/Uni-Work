using Laborator_04.Models;
using Microsoft.AspNetCore.Mvc;

namespace Laborator_04.Controllers
{
    public class ArticlesController : Controller
    {
        [NonAction]
        public Article[] GetArticles()
        {
            // Se instantiaza un array de articole
            Article[] articles = new Article[3];
            // Se creeaza articolele
            for (int i = 0; i < 3; i++)
            {
                Article article = new Article();
                article.Id = i;
                article.Title = "Articol " + (i + 1).ToString();
                article.Content = "Continut articol " + (i + 1).ToString();
                article.Date = DateTime.Now;
                // Se adauga articolul in array
                articles[i] = article;
            }
            return articles;

        }

        [ActionName("listare")]
        public IActionResult Index()
        {
            Article[] articles = GetArticles();
            // Se adauga array-ul de articole in View
            ViewBag.Articles = articles;
            return View();
        }

        public IActionResult Show(int? id)
        {
            Article[] articles = GetArticles();
            try
            {
                ViewBag.Article = articles[(int)id];
                return View();
            }
            catch (Exception e)
            {
                ViewBag.ErrorMessage = e.Message;
                return View("Error");
            }
        }

        [HttpGet]
        public IActionResult New()
        {
            return View();
        }

        [HttpPost]
        public IActionResult New(Article article)
        {
            ViewBag.Article = article;
            return View("NewPostMethod");
        }

        [HttpGet]
        public IActionResult Edit(int? id)
        {
            ViewBag.id = id;
            return View();
        }

        [HttpPost]
        public IActionResult Edit(Article article)
        {
            ViewBag.article = article;
            return View("EditMethod");
        }

        public IActionResult Delete(int? id)
        {
            return Content("Articolul a fost sters din baza de date");
        }
    }
}
