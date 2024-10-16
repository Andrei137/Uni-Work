using Azure.Core.Pipeline;
using Laborator_05.Models;
using Microsoft.AspNetCore.Mvc;

namespace Laborator_05.Controllers
{
    public class ArticlesController : Controller
    {
        private readonly AppDbContext db;

        public ArticlesController(AppDbContext context)
        {
            db = context;
        }

        public IActionResult Index()
        {
            var articles = db.Articles;
            ViewBag.Articles = articles;
            return View();
        }

        public IActionResult Show(int id)
        {
            Article article = db.Articles.Find(id);
            ViewBag.Articles = article;
            return View();
        }

        public IActionResult New()
        {
            return View();
        }

        [HttpPost]
        public IActionResult New(Article article) 
        {
            try
            {
                db.Articles.Add(article);   
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            catch (Exception)
            {
                return View();
            }
        }

        public IActionResult Edit(int id)
        {
            Article article = db.Articles.Find(id);
            ViewBag.Articles = article;
            return View();
        }

        [HttpPost]
        public IActionResult Edit(int id, Article requestArticle)
        {
            Article article = db.Articles.Find(id);
            try
            {
                article.Title = requestArticle.Title;
                article.Content = requestArticle.Content;
                article.Date = requestArticle.Date;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            catch(Exception) 
            {
                return RedirectToAction("Edit", article.Id);
            }
        }

        public IActionResult Delete(int id)
        {
            Article article = db.Articles.Find(id);
            db.Articles.Remove(article);
            db.SaveChanges();
            return RedirectToAction("Index");
        }
    }
}
