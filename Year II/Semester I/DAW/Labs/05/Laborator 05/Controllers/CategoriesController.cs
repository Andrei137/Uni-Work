using Laborator_05.Models;
using Microsoft.AspNetCore.Mvc;

namespace Laborator_05.Controllers
{
    public class CategoriesController : Controller
    {
        private readonly AppDbContext db;

        public CategoriesController(AppDbContext context)
        {
            db = context;
        }

        public IActionResult Index()
        {
            var categories = db.Categories;
            ViewBag.Categories = categories;
            return View();
        }

        public IActionResult Show(int id)
        {
            Category category = db.Categories.Find(id);
            ViewBag.Categories = category;
            return View();
        }

        public IActionResult New()
        {
            return View();
        }

        [HttpPost]
        public IActionResult New(Category category)
        {
            try
            {
                db.Categories.Add(category);
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
            Category category = db.Categories.Find(id);
            ViewBag.Categories = category;
            return View();
        }

        [HttpPost]
        public IActionResult Edit(int id, Category requestCategory)
        {
            Category category = db.Categories.Find(id);
            try
            {
                category.CategoryName = requestCategory.CategoryName;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            catch (Exception)
            {
                return RedirectToAction("Edit", category.Id);
            }
        }

        public IActionResult Delete(int id)
        {
            Category category = db.Categories.Find(id);
            db.Categories.Remove(category);
            db.SaveChanges();
            return RedirectToAction("Index");
        }
    }
}
